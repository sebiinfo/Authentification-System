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
CMAKE_SOURCE_DIR = /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build

# Utility rule file for OpenCVExternalLibrary.

# Include any custom commands dependencies for this target.
include build/CMakeFiles/OpenCVExternalLibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include build/CMakeFiles/OpenCVExternalLibrary.dir/progress.make

OpenCVExternalLibrary: build/CMakeFiles/OpenCVExternalLibrary.dir/build.make
.PHONY : OpenCVExternalLibrary

# Rule to build all files generated by this target.
build/CMakeFiles/OpenCVExternalLibrary.dir/build: OpenCVExternalLibrary
.PHONY : build/CMakeFiles/OpenCVExternalLibrary.dir/build

build/CMakeFiles/OpenCVExternalLibrary.dir/clean:
	cd /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build/build && $(CMAKE_COMMAND) -P CMakeFiles/OpenCVExternalLibrary.dir/cmake_clean.cmake
.PHONY : build/CMakeFiles/OpenCVExternalLibrary.dir/clean

build/CMakeFiles/OpenCVExternalLibrary.dir/depend:
	cd /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan /home/johnnyventuras/Desktop/Authentification-System/libs/opencv /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build/build /home/johnnyventuras/Desktop/Authentification-System/sources/TestCameraCapture/bogdan/build/build/CMakeFiles/OpenCVExternalLibrary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/CMakeFiles/OpenCVExternalLibrary.dir/depend
