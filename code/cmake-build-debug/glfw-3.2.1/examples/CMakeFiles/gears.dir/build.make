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
include glfw-3.2.1/examples/CMakeFiles/gears.dir/depend.make

# Include the progress variables for this target.
include glfw-3.2.1/examples/CMakeFiles/gears.dir/progress.make

# Include the compile flags for this target's objects.
include glfw-3.2.1/examples/CMakeFiles/gears.dir/flags.make

glfw-3.2.1/examples/gears.app/Contents/Resources/glfw.icns: ../glfw-3.2.1/examples/glfw.icns
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content glfw-3.2.1/examples/gears.app/Contents/Resources/glfw.icns"
	$(CMAKE_COMMAND) -E copy /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/examples/glfw.icns glfw-3.2.1/examples/gears.app/Contents/Resources/glfw.icns

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o: glfw-3.2.1/examples/CMakeFiles/gears.dir/flags.make
glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o: ../glfw-3.2.1/examples/gears.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gears.dir/gears.c.o   -c /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/examples/gears.c

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/gears.c.i"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/examples/gears.c > CMakeFiles/gears.dir/gears.c.i

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/gears.c.s"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/examples/gears.c -o CMakeFiles/gears.dir/gears.c.s

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.requires:

.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.requires

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.provides: glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.requires
	$(MAKE) -f glfw-3.2.1/examples/CMakeFiles/gears.dir/build.make glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.provides.build
.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.provides

glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.provides.build: glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o


glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o: glfw-3.2.1/examples/CMakeFiles/gears.dir/flags.make
glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o: ../glfw-3.2.1/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gears.dir/__/deps/glad.c.o   -c /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/deps/glad.c

glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/__/deps/glad.c.i"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/deps/glad.c > CMakeFiles/gears.dir/__/deps/glad.c.i

glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/__/deps/glad.c.s"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/deps/glad.c -o CMakeFiles/gears.dir/__/deps/glad.c.s

glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.requires:

.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.requires

glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.provides: glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.requires
	$(MAKE) -f glfw-3.2.1/examples/CMakeFiles/gears.dir/build.make glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.provides.build
.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.provides

glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.provides.build: glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o


# Object files for target gears
gears_OBJECTS = \
"CMakeFiles/gears.dir/gears.c.o" \
"CMakeFiles/gears.dir/__/deps/glad.c.o"

# External object files for target gears
gears_EXTERNAL_OBJECTS =

glfw-3.2.1/examples/gears.app/Contents/MacOS/gears: glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o
glfw-3.2.1/examples/gears.app/Contents/MacOS/gears: glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o
glfw-3.2.1/examples/gears.app/Contents/MacOS/gears: glfw-3.2.1/examples/CMakeFiles/gears.dir/build.make
glfw-3.2.1/examples/gears.app/Contents/MacOS/gears: glfw-3.2.1/src/libglfw3.a
glfw-3.2.1/examples/gears.app/Contents/MacOS/gears: glfw-3.2.1/examples/CMakeFiles/gears.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gears.app/Contents/MacOS/gears"
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gears.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw-3.2.1/examples/CMakeFiles/gears.dir/build: glfw-3.2.1/examples/gears.app/Contents/MacOS/gears
glfw-3.2.1/examples/CMakeFiles/gears.dir/build: glfw-3.2.1/examples/gears.app/Contents/Resources/glfw.icns

.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/build

glfw-3.2.1/examples/CMakeFiles/gears.dir/requires: glfw-3.2.1/examples/CMakeFiles/gears.dir/gears.c.o.requires
glfw-3.2.1/examples/CMakeFiles/gears.dir/requires: glfw-3.2.1/examples/CMakeFiles/gears.dir/__/deps/glad.c.o.requires

.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/requires

glfw-3.2.1/examples/CMakeFiles/gears.dir/clean:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples && $(CMAKE_COMMAND) -P CMakeFiles/gears.dir/cmake_clean.cmake
.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/clean

glfw-3.2.1/examples/CMakeFiles/gears.dir/depend:
	cd /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/glfw-3.2.1/examples /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples /Users/Yimin/Dropbox/2017spring/cs184/final_proj/fluid-simulation/code/cmake-build-debug/glfw-3.2.1/examples/CMakeFiles/gears.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw-3.2.1/examples/CMakeFiles/gears.dir/depend

