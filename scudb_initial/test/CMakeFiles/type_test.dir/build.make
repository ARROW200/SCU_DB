# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arrow/Desktop/SCU_DB/scudb_initial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arrow/Desktop/SCU_DB/scudb_initial

# Include any dependencies generated for this target.
include test/CMakeFiles/type_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/type_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/type_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/type_test.dir/flags.make

test/CMakeFiles/type_test.dir/type/type_test.cpp.o: test/CMakeFiles/type_test.dir/flags.make
test/CMakeFiles/type_test.dir/type/type_test.cpp.o: test/type/type_test.cpp
test/CMakeFiles/type_test.dir/type/type_test.cpp.o: test/CMakeFiles/type_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arrow/Desktop/SCU_DB/scudb_initial/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/type_test.dir/type/type_test.cpp.o"
	cd /home/arrow/Desktop/SCU_DB/scudb_initial/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/type_test.dir/type/type_test.cpp.o -MF CMakeFiles/type_test.dir/type/type_test.cpp.o.d -o CMakeFiles/type_test.dir/type/type_test.cpp.o -c /home/arrow/Desktop/SCU_DB/scudb_initial/test/type/type_test.cpp

test/CMakeFiles/type_test.dir/type/type_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/type_test.dir/type/type_test.cpp.i"
	cd /home/arrow/Desktop/SCU_DB/scudb_initial/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arrow/Desktop/SCU_DB/scudb_initial/test/type/type_test.cpp > CMakeFiles/type_test.dir/type/type_test.cpp.i

test/CMakeFiles/type_test.dir/type/type_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/type_test.dir/type/type_test.cpp.s"
	cd /home/arrow/Desktop/SCU_DB/scudb_initial/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arrow/Desktop/SCU_DB/scudb_initial/test/type/type_test.cpp -o CMakeFiles/type_test.dir/type/type_test.cpp.s

# Object files for target type_test
type_test_OBJECTS = \
"CMakeFiles/type_test.dir/type/type_test.cpp.o"

# External object files for target type_test
type_test_EXTERNAL_OBJECTS =

test/type_test: test/CMakeFiles/type_test.dir/type/type_test.cpp.o
test/type_test: test/CMakeFiles/type_test.dir/build.make
test/type_test: lib/libvtable.so
test/type_test: lib/libsqlite3.so
test/type_test: lib/libgtest.so
test/type_test: test/CMakeFiles/type_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arrow/Desktop/SCU_DB/scudb_initial/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable type_test"
	cd /home/arrow/Desktop/SCU_DB/scudb_initial/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/type_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/type_test.dir/build: test/type_test
.PHONY : test/CMakeFiles/type_test.dir/build

test/CMakeFiles/type_test.dir/clean:
	cd /home/arrow/Desktop/SCU_DB/scudb_initial/test && $(CMAKE_COMMAND) -P CMakeFiles/type_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/type_test.dir/clean

test/CMakeFiles/type_test.dir/depend:
	cd /home/arrow/Desktop/SCU_DB/scudb_initial && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arrow/Desktop/SCU_DB/scudb_initial /home/arrow/Desktop/SCU_DB/scudb_initial/test /home/arrow/Desktop/SCU_DB/scudb_initial /home/arrow/Desktop/SCU_DB/scudb_initial/test /home/arrow/Desktop/SCU_DB/scudb_initial/test/CMakeFiles/type_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/type_test.dir/depend

