# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug

# Include any dependencies generated for this target.
include CGL/deps/glfw/tests/CMakeFiles/peter.dir/depend.make

# Include the progress variables for this target.
include CGL/deps/glfw/tests/CMakeFiles/peter.dir/progress.make

# Include the compile flags for this target's objects.
include CGL/deps/glfw/tests/CMakeFiles/peter.dir/flags.make

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o: CGL/deps/glfw/tests/CMakeFiles/peter.dir/flags.make
CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o: ../CGL/deps/glfw/tests/peter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/peter.dir/peter.c.o   -c /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/tests/peter.c

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/peter.dir/peter.c.i"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/tests/peter.c > CMakeFiles/peter.dir/peter.c.i

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/peter.dir/peter.c.s"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/tests/peter.c -o CMakeFiles/peter.dir/peter.c.s

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.requires:

.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.requires

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.provides: CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.requires
	$(MAKE) -f CGL/deps/glfw/tests/CMakeFiles/peter.dir/build.make CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.provides.build
.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.provides

CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.provides.build: CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o


# Object files for target peter
peter_OBJECTS = \
"CMakeFiles/peter.dir/peter.c.o"

# External object files for target peter
peter_EXTERNAL_OBJECTS =

CGL/deps/glfw/tests/peter: CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o
CGL/deps/glfw/tests/peter: CGL/deps/glfw/tests/CMakeFiles/peter.dir/build.make
CGL/deps/glfw/tests/peter: CGL/deps/glfw/src/libglfw3.a
CGL/deps/glfw/tests/peter: CGL/deps/glfw/tests/CMakeFiles/peter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable peter"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/peter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CGL/deps/glfw/tests/CMakeFiles/peter.dir/build: CGL/deps/glfw/tests/peter

.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/build

CGL/deps/glfw/tests/CMakeFiles/peter.dir/requires: CGL/deps/glfw/tests/CMakeFiles/peter.dir/peter.c.o.requires

.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/requires

CGL/deps/glfw/tests/CMakeFiles/peter.dir/clean:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/peter.dir/cmake_clean.cmake
.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/clean

CGL/deps/glfw/tests/CMakeFiles/peter.dir/depend:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/tests /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/tests/CMakeFiles/peter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CGL/deps/glfw/tests/CMakeFiles/peter.dir/depend

