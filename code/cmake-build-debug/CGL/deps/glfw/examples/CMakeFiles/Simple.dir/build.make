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
include CGL/deps/glfw/examples/CMakeFiles/Simple.dir/depend.make

# Include the progress variables for this target.
include CGL/deps/glfw/examples/CMakeFiles/Simple.dir/progress.make

# Include the compile flags for this target's objects.
include CGL/deps/glfw/examples/CMakeFiles/Simple.dir/flags.make

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/flags.make
CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o: ../CGL/deps/glfw/examples/simple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Simple.dir/simple.c.o   -c /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/examples/simple.c

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Simple.dir/simple.c.i"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/examples/simple.c > CMakeFiles/Simple.dir/simple.c.i

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Simple.dir/simple.c.s"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/examples/simple.c -o CMakeFiles/Simple.dir/simple.c.s

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.requires:

.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.requires

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.provides: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.requires
	$(MAKE) -f CGL/deps/glfw/examples/CMakeFiles/Simple.dir/build.make CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.provides.build
.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.provides

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.provides.build: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o


# Object files for target Simple
Simple_OBJECTS = \
"CMakeFiles/Simple.dir/simple.c.o"

# External object files for target Simple
Simple_EXTERNAL_OBJECTS =

CGL/deps/glfw/examples/Simple.app/Contents/MacOS/Simple: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o
CGL/deps/glfw/examples/Simple.app/Contents/MacOS/Simple: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/build.make
CGL/deps/glfw/examples/Simple.app/Contents/MacOS/Simple: CGL/deps/glfw/src/libglfw3.a
CGL/deps/glfw/examples/Simple.app/Contents/MacOS/Simple: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Simple.app/Contents/MacOS/Simple"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CGL/deps/glfw/examples/CMakeFiles/Simple.dir/build: CGL/deps/glfw/examples/Simple.app/Contents/MacOS/Simple

.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/build

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/requires: CGL/deps/glfw/examples/CMakeFiles/Simple.dir/simple.c.o.requires

.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/requires

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/clean:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/Simple.dir/cmake_clean.cmake
.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/clean

CGL/deps/glfw/examples/CMakeFiles/Simple.dir/depend:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/CGL/deps/glfw/examples /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CGL/deps/glfw/examples/CMakeFiles/Simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CGL/deps/glfw/examples/CMakeFiles/Simple.dir/depend

