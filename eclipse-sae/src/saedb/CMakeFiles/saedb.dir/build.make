# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/neo/Project/saedb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neo/Project/saedb/eclipse-sae

# Include any dependencies generated for this target.
include src/saedb/CMakeFiles/saedb.dir/depend.make

# Include the progress variables for this target.
include src/saedb/CMakeFiles/saedb.dir/progress.make

# Include the compile flags for this target's objects.
include src/saedb/CMakeFiles/saedb.dir/flags.make

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o: src/saedb/CMakeFiles/saedb.dir/flags.make
src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o: ../src/saedb/dumb.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/neo/Project/saedb/eclipse-sae/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o"
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/saedb.dir/dumb.cpp.o -c /home/neo/Project/saedb/src/saedb/dumb.cpp

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saedb.dir/dumb.cpp.i"
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/neo/Project/saedb/src/saedb/dumb.cpp > CMakeFiles/saedb.dir/dumb.cpp.i

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saedb.dir/dumb.cpp.s"
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/neo/Project/saedb/src/saedb/dumb.cpp -o CMakeFiles/saedb.dir/dumb.cpp.s

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.requires:
.PHONY : src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.requires

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.provides: src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.requires
	$(MAKE) -f src/saedb/CMakeFiles/saedb.dir/build.make src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.provides.build
.PHONY : src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.provides

src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.provides.build: src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o

# Object files for target saedb
saedb_OBJECTS = \
"CMakeFiles/saedb.dir/dumb.cpp.o"

# External object files for target saedb
saedb_EXTERNAL_OBJECTS =

src/saedb/libsaedb.a: src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o
src/saedb/libsaedb.a: src/saedb/CMakeFiles/saedb.dir/build.make
src/saedb/libsaedb.a: src/saedb/CMakeFiles/saedb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libsaedb.a"
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && $(CMAKE_COMMAND) -P CMakeFiles/saedb.dir/cmake_clean_target.cmake
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saedb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/saedb/CMakeFiles/saedb.dir/build: src/saedb/libsaedb.a
.PHONY : src/saedb/CMakeFiles/saedb.dir/build

src/saedb/CMakeFiles/saedb.dir/requires: src/saedb/CMakeFiles/saedb.dir/dumb.cpp.o.requires
.PHONY : src/saedb/CMakeFiles/saedb.dir/requires

src/saedb/CMakeFiles/saedb.dir/clean:
	cd /home/neo/Project/saedb/eclipse-sae/src/saedb && $(CMAKE_COMMAND) -P CMakeFiles/saedb.dir/cmake_clean.cmake
.PHONY : src/saedb/CMakeFiles/saedb.dir/clean

src/saedb/CMakeFiles/saedb.dir/depend:
	cd /home/neo/Project/saedb/eclipse-sae && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neo/Project/saedb /home/neo/Project/saedb/src/saedb /home/neo/Project/saedb/eclipse-sae /home/neo/Project/saedb/eclipse-sae/src/saedb /home/neo/Project/saedb/eclipse-sae/src/saedb/CMakeFiles/saedb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/saedb/CMakeFiles/saedb.dir/depend

