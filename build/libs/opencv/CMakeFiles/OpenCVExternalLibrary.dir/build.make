# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/fcomoreira/bachelor/current/CSE201/Authentification-System

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build

# Utility rule file for OpenCVExternalLibrary.

# Include any custom commands dependencies for this target.
include libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/progress.make

OpenCVExternalLibrary: libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/build.make
.PHONY : OpenCVExternalLibrary

# Rule to build all files generated by this target.
libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/build: OpenCVExternalLibrary
.PHONY : libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/build

libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/clean:
	cd /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build/libs/opencv && $(CMAKE_COMMAND) -P CMakeFiles/OpenCVExternalLibrary.dir/cmake_clean.cmake
.PHONY : libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/clean

libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/depend:
	cd /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fcomoreira/bachelor/current/CSE201/Authentification-System /home/fcomoreira/bachelor/current/CSE201/Authentification-System/libs/opencv /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build/libs/opencv /home/fcomoreira/bachelor/current/CSE201/Authentification-System/build/libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/opencv/CMakeFiles/OpenCVExternalLibrary.dir/depend

