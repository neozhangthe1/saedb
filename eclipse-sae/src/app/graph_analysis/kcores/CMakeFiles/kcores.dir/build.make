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
CMAKE_SOURCE_DIR = /home/neo/Projects/saedb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neo/Projects/saedb/eclipse-sae

# Include any dependencies generated for this target.
include src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/depend.make

# Include the progress variables for this target.
include src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/progress.make

# Include the compile flags for this target's objects.
include src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/flags.make

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/flags.make
src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o: ../src/app/graph_analysis/kcores/kcore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/neo/Projects/saedb/eclipse-sae/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o"
	cd /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kcores.dir/kcore.cpp.o -c /home/neo/Projects/saedb/src/app/graph_analysis/kcores/kcore.cpp

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kcores.dir/kcore.cpp.i"
	cd /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/neo/Projects/saedb/src/app/graph_analysis/kcores/kcore.cpp > CMakeFiles/kcores.dir/kcore.cpp.i

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kcores.dir/kcore.cpp.s"
	cd /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/neo/Projects/saedb/src/app/graph_analysis/kcores/kcore.cpp -o CMakeFiles/kcores.dir/kcore.cpp.s

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.requires:
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.requires

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.provides: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.requires
	$(MAKE) -f src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/build.make src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.provides.build
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.provides

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.provides.build: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o

# Object files for target kcores
kcores_OBJECTS = \
"CMakeFiles/kcores.dir/kcore.cpp.o"

# External object files for target kcores
kcores_EXTERNAL_OBJECTS =

kcores: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o
kcores: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/build.make
kcores: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../kcores"
	cd /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kcores.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/build: kcores
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/build

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/requires: src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/kcore.cpp.o.requires
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/requires

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/clean:
	cd /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores && $(CMAKE_COMMAND) -P CMakeFiles/kcores.dir/cmake_clean.cmake
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/clean

src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/depend:
	cd /home/neo/Projects/saedb/eclipse-sae && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neo/Projects/saedb /home/neo/Projects/saedb/src/app/graph_analysis/kcores /home/neo/Projects/saedb/eclipse-sae /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores /home/neo/Projects/saedb/eclipse-sae/src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/app/graph_analysis/kcores/CMakeFiles/kcores.dir/depend

