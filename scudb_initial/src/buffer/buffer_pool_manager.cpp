#include "buffer/buffer_pool_manager.h"

namespace scudb {

/*
 * BufferPoolManager Constructor
 * When log_manager is nullptr, logging is disabled (for test purpose)
 * WARNING: Do Not Edit This Function
 */
    BufferPoolManager::BufferPoolManager(size_t pool_size,
                                         DiskManager *disk_manager,
                                         LogManager *log_manager)
            : pool_size_(pool_size), disk_manager_(disk_manager),
              log_manager_(log_manager) {
        // a consecutive memory space for buffer pool
        pages_ = new Page[pool_size_];
        page_table_ = new ExtendibleHash<page_id_t, Page *>(BUCKET_SIZE);
        replacer_ = new LRUReplacer<Page *>;
        free_list_ = new std::list<Page *>;

        // put all the pages into free list
        for (size_t i = 0; i < pool_size_; ++i) {
            free_list_->push_back(&pages_[i]);
        }
    }

/*
 * BufferPoolManager Deconstructor
 * WARNING: Do Not Edit This Function
 */
    BufferPoolManager::~BufferPoolManager() {
        delete[] pages_;
        delete page_table_;
        delete replacer_;
        delete free_list_;
    }

/**
 * 1. search hash table.
 *  1.1 if exist, pin the page and return immediately
 *  1.2 if no exist, find a replacement entry from either free list or lru
 *      replacer. (NOTE: always find from free list first)
 * 2. If the entry chosen for replacement is dirty, write it back to disk.
 * 3. Delete the entry for the old page from the hash table and insert an
 * entry for the new page.
 * 4. Update page metadata, read page content from disk file and return page
 * pointer
 *
 * This function must mark the Page as pinned and remove its entry from LRUReplacer before it is returned to the caller.
 */
    Page *BufferPoolManager::FetchPage(page_id_t page_id) {
        lock_guard<mutex> lck(latch_);
        Page *tmp = nullptr;
        if (page_table_->Find(page_id,tmp)) { //1.1
            tmp->pin_count_++;
            replacer_->Erase(tmp);
            return tmp;
        }
        //1.2
        tmp = GetVictimPage();
        if (tmp == nullptr) return tmp;
        //2
        if (tmp->is_dirty_) {
            disk_manager_->WritePage(tmp->GetPageId(),tmp->data_);
        }
        //3
        page_table_->Remove(tmp->GetPageId());
        page_table_->Insert(page_id,tmp);
        //4
        disk_manager_->ReadPage(page_id,tmp->data_);
        tmp->pin_count_ = 1;
        tmp->is_dirty_ = false;
        tmp->page_id_= page_id;

        return tmp;
    }
//Page *BufferPoolManager::find

/*
 * Implementation of unpin page
 * if pin_count>0, decrement it and if it becomes zero, put it back to
 * replacer if pin_count<=0 before this call, return false. is_dirty: set the
 * dirty flag of this page
 */
    bool BufferPoolManager::UnpinPage(page_id_t page_id, bool is_dirty) {
        lock_guard<mutex> lck(latch_);
        Page *tmp = nullptr;
        page_table_->Find(page_id, tmp);
        if (tmp == nullptr) {
            return false;
        }
        tmp->is_dirty_ = is_dirty;
        if (tmp->GetPinCount() <= 0) {
            return false;
        }
        ;
        if (--tmp->pin_count_ == 0) {
            replacer_->Insert(tmp);
        }
        return true;
    }

/*
 * Used to flush a particular page of the buffer pool to disk. Should call the
 * write_page method of the disk manager
 * if page is not found in page table, return false
 * NOTE: make sure page_id != INVALID_PAGE_ID
 */
    bool BufferPoolManager::FlushPage(page_id_t page_id) {
        lock_guard<mutex> lck(latch_);
        Page *tmp = nullptr;
        page_table_->Find(page_id,tmp);
        if (tmp == nullptr || tmp->page_id_ == INVALID_PAGE_ID) {
            return false;
        }
        if (tmp->is_dirty_) {
            disk_manager_->WritePage(page_id,tmp->GetData());
            tmp->is_dirty_ = false;
        }

        return true;
    }

/**
 * User should call this method for deleting a page. This routine will call
 * disk manager to deallocate the page. First, if page is found within page
 * table, buffer pool manager should be reponsible for removing this entry out
 * of page table, reseting page metadata and adding back to free list. Second,
 * call disk manager's DeallocatePage() method to delete from disk file. If
 * the page is found within page table, but pin_count != 0, return false
 */
    bool BufferPoolManager::DeletePage(page_id_t page_id) {
        lock_guard<mutex> lck(latch_);
        Page *tmp = nullptr;
        page_table_->Find(page_id,tmp);
        if (tmp != nullptr) {
            if (tmp->GetPinCount() > 0) {
                return false;
            }
            replacer_->Erase(tmp);
            page_table_->Remove(page_id);
            tmp->is_dirty_= false;
            tmp->ResetMemory();
            free_list_->push_back(tmp);
        }
        disk_manager_->DeallocatePage(page_id);
        return true;
    }

/**
 * User should call this method if needs to create a new page. This routine
 * will call disk manager to allocate a page.
 * Buffer pool manager should be responsible to choose a victim page either
 * from free list or lru replacer(NOTE: always choose from free list first),
 * update new page's metadata, zero out memory and add corresponding entry
 * into page table. return nullptr if all the pages in pool are pinned
 */
    Page *BufferPoolManager::NewPage(page_id_t &page_id) {
        lock_guard<mutex> lck(latch_);
        Page *tmp = nullptr;
        tmp = GetVictimPage();
        if (tmp == nullptr) return tmp;

        page_id = disk_manager_->AllocatePage();
        //2
        if (tmp->is_dirty_) {
            disk_manager_->WritePage(tmp->GetPageId(),tmp->data_);
        }
        //3
        page_table_->Remove(tmp->GetPageId());
        page_table_->Insert(page_id,tmp);

        //4
        tmp->page_id_ = page_id;
        tmp->ResetMemory();
        tmp->is_dirty_ = false;
        tmp->pin_count_ = 1;

        return tmp;
    }

    Page *BufferPoolManager::GetVictimPage() {
        Page *tmp = nullptr;
        if (free_list_->empty()) {
            if (replacer_->Size() == 0) {
                return nullptr;
            }
            replacer_->Victim(tmp);
        } else {
            tmp = free_list_->front();
            free_list_->pop_front();
            assert(tmp->GetPageId() == INVALID_PAGE_ID);
        }
        assert(tmp->GetPinCount() == 0);
        return tmp;
    }

} // namespace scudb
