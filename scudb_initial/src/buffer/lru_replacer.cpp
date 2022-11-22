/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace scudb {

    template <typename T> LRUReplacer<T>::LRUReplacer() {
        head = make_shared<Node>();
        tail = make_shared<Node>();
        head->next = tail;
        tail->prev = head;
    }

    template <typename T> LRUReplacer<T>::~LRUReplacer() {}

/*
 * Insert value into LRU
 */
    template <typename T> void LRUReplacer<T>::Insert(const T &value) {
        lock_guard<mutex> lck(latch);
        shared_ptr<Node> tmp;
        if (map.find(value) != map.end()) {
            tmp = map[value];
            shared_ptr<Node> prev = tmp->prev;
            shared_ptr<Node> succ = tmp->next;
            prev->next = succ;
            succ->prev = prev;
        } else {
            tmp = make_shared<Node>(value);
        }
        shared_ptr<Node> fir = head->next;
        tmp->next = fir;
        fir->prev = tmp;
        tmp->prev = head;
        head->next = tmp;
        map[value] = tmp;
        return;
    }

/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
    template <typename T> bool LRUReplacer<T>::Victim(T &value) {
        lock_guard<mutex> lck(latch);
        if (map.empty()) {
            return false;
        }
        shared_ptr<Node> last = tail->prev;
        tail->prev = last->prev;
        last->prev->next = tail;
        value = last->val;
        map.erase(last->val);
        return true;
    }

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
    template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
        lock_guard<mutex> lck(latch);
        if (map.find(value) != map.end()) {
            shared_ptr<Node> cur = map[value];
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        return map.erase(value);
    }

    template <typename T> size_t LRUReplacer<T>::Size() {
        lock_guard<mutex> lck(latch);
        return map.size();
    }

    template class LRUReplacer<Page *>;
// test only
    template class LRUReplacer<int>;

} // namespace cmudb
