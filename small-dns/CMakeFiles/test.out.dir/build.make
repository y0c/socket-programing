# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/parallels/Documents/network/practice1/small-dns

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parallels/Documents/network/practice1/small-dns

# Include any dependencies generated for this target.
include CMakeFiles/test.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.out.dir/flags.make

CMakeFiles/test.out.dir/test/hashtable_test.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/test/hashtable_test.o: test/hashtable_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test.out.dir/test/hashtable_test.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/test/hashtable_test.o   -c /home/parallels/Documents/network/practice1/small-dns/test/hashtable_test.c

CMakeFiles/test.out.dir/test/hashtable_test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/test/hashtable_test.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallels/Documents/network/practice1/small-dns/test/hashtable_test.c > CMakeFiles/test.out.dir/test/hashtable_test.i

CMakeFiles/test.out.dir/test/hashtable_test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/test/hashtable_test.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallels/Documents/network/practice1/small-dns/test/hashtable_test.c -o CMakeFiles/test.out.dir/test/hashtable_test.s

CMakeFiles/test.out.dir/test/hashtable_test.o.requires:

.PHONY : CMakeFiles/test.out.dir/test/hashtable_test.o.requires

CMakeFiles/test.out.dir/test/hashtable_test.o.provides: CMakeFiles/test.out.dir/test/hashtable_test.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/test/hashtable_test.o.provides.build
.PHONY : CMakeFiles/test.out.dir/test/hashtable_test.o.provides

CMakeFiles/test.out.dir/test/hashtable_test.o.provides.build: CMakeFiles/test.out.dir/test/hashtable_test.o


CMakeFiles/test.out.dir/include/str.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/include/str.o: include/str.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test.out.dir/include/str.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/include/str.o   -c /home/parallels/Documents/network/practice1/small-dns/include/str.c

CMakeFiles/test.out.dir/include/str.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/include/str.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallels/Documents/network/practice1/small-dns/include/str.c > CMakeFiles/test.out.dir/include/str.i

CMakeFiles/test.out.dir/include/str.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/include/str.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallels/Documents/network/practice1/small-dns/include/str.c -o CMakeFiles/test.out.dir/include/str.s

CMakeFiles/test.out.dir/include/str.o.requires:

.PHONY : CMakeFiles/test.out.dir/include/str.o.requires

CMakeFiles/test.out.dir/include/str.o.provides: CMakeFiles/test.out.dir/include/str.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/include/str.o.provides.build
.PHONY : CMakeFiles/test.out.dir/include/str.o.provides

CMakeFiles/test.out.dir/include/str.o.provides.build: CMakeFiles/test.out.dir/include/str.o


CMakeFiles/test.out.dir/include/hashtable.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/include/hashtable.o: include/hashtable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/test.out.dir/include/hashtable.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/include/hashtable.o   -c /home/parallels/Documents/network/practice1/small-dns/include/hashtable.c

CMakeFiles/test.out.dir/include/hashtable.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/include/hashtable.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallels/Documents/network/practice1/small-dns/include/hashtable.c > CMakeFiles/test.out.dir/include/hashtable.i

CMakeFiles/test.out.dir/include/hashtable.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/include/hashtable.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallels/Documents/network/practice1/small-dns/include/hashtable.c -o CMakeFiles/test.out.dir/include/hashtable.s

CMakeFiles/test.out.dir/include/hashtable.o.requires:

.PHONY : CMakeFiles/test.out.dir/include/hashtable.o.requires

CMakeFiles/test.out.dir/include/hashtable.o.provides: CMakeFiles/test.out.dir/include/hashtable.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/include/hashtable.o.provides.build
.PHONY : CMakeFiles/test.out.dir/include/hashtable.o.provides

CMakeFiles/test.out.dir/include/hashtable.o.provides.build: CMakeFiles/test.out.dir/include/hashtable.o


CMakeFiles/test.out.dir/include/common.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/include/common.o: include/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/test.out.dir/include/common.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/include/common.o   -c /home/parallels/Documents/network/practice1/small-dns/include/common.c

CMakeFiles/test.out.dir/include/common.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/include/common.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallels/Documents/network/practice1/small-dns/include/common.c > CMakeFiles/test.out.dir/include/common.i

CMakeFiles/test.out.dir/include/common.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/include/common.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallels/Documents/network/practice1/small-dns/include/common.c -o CMakeFiles/test.out.dir/include/common.s

CMakeFiles/test.out.dir/include/common.o.requires:

.PHONY : CMakeFiles/test.out.dir/include/common.o.requires

CMakeFiles/test.out.dir/include/common.o.provides: CMakeFiles/test.out.dir/include/common.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/include/common.o.provides.build
.PHONY : CMakeFiles/test.out.dir/include/common.o.provides

CMakeFiles/test.out.dir/include/common.o.provides.build: CMakeFiles/test.out.dir/include/common.o


CMakeFiles/test.out.dir/include/db.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/include/db.o: include/db.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/test.out.dir/include/db.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/include/db.o   -c /home/parallels/Documents/network/practice1/small-dns/include/db.c

CMakeFiles/test.out.dir/include/db.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/include/db.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallels/Documents/network/practice1/small-dns/include/db.c > CMakeFiles/test.out.dir/include/db.i

CMakeFiles/test.out.dir/include/db.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/include/db.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallels/Documents/network/practice1/small-dns/include/db.c -o CMakeFiles/test.out.dir/include/db.s

CMakeFiles/test.out.dir/include/db.o.requires:

.PHONY : CMakeFiles/test.out.dir/include/db.o.requires

CMakeFiles/test.out.dir/include/db.o.provides: CMakeFiles/test.out.dir/include/db.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/include/db.o.provides.build
.PHONY : CMakeFiles/test.out.dir/include/db.o.provides

CMakeFiles/test.out.dir/include/db.o.provides.build: CMakeFiles/test.out.dir/include/db.o


# Object files for target test.out
test_out_OBJECTS = \
"CMakeFiles/test.out.dir/test/hashtable_test.o" \
"CMakeFiles/test.out.dir/include/str.o" \
"CMakeFiles/test.out.dir/include/hashtable.o" \
"CMakeFiles/test.out.dir/include/common.o" \
"CMakeFiles/test.out.dir/include/db.o"

# External object files for target test.out
test_out_EXTERNAL_OBJECTS =

bin/test.out: CMakeFiles/test.out.dir/test/hashtable_test.o
bin/test.out: CMakeFiles/test.out.dir/include/str.o
bin/test.out: CMakeFiles/test.out.dir/include/hashtable.o
bin/test.out: CMakeFiles/test.out.dir/include/common.o
bin/test.out: CMakeFiles/test.out.dir/include/db.o
bin/test.out: CMakeFiles/test.out.dir/build.make
bin/test.out: CMakeFiles/test.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/parallels/Documents/network/practice1/small-dns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable bin/test.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.out.dir/build: bin/test.out

.PHONY : CMakeFiles/test.out.dir/build

CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/test/hashtable_test.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/include/str.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/include/hashtable.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/include/common.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/include/db.o.requires

.PHONY : CMakeFiles/test.out.dir/requires

CMakeFiles/test.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.out.dir/clean

CMakeFiles/test.out.dir/depend:
	cd /home/parallels/Documents/network/practice1/small-dns && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parallels/Documents/network/practice1/small-dns /home/parallels/Documents/network/practice1/small-dns /home/parallels/Documents/network/practice1/small-dns /home/parallels/Documents/network/practice1/small-dns /home/parallels/Documents/network/practice1/small-dns/CMakeFiles/test.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.out.dir/depend

