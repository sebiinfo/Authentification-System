# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build

# Include any dependencies generated for this target.
include CMakeFiles/Authentication-System.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Authentication-System.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Authentication-System.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Authentication-System.dir/flags.make

CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj: CMakeFiles/Authentication-System.dir/flags.make
CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj: CMakeFiles/Authentication-System.dir/includes_CXX.rsp
CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj: C:/Users/paula/OneDrive/Desktop/Paris/c++/github/Authentification-System/TestInterface/camera/main.cpp
CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj: CMakeFiles/Authentication-System.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj -MF CMakeFiles\Authentication-System.dir\TestInterface\camera\main.cpp.obj.d -o CMakeFiles\Authentication-System.dir\TestInterface\camera\main.cpp.obj -c C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\TestInterface\camera\main.cpp

CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\TestInterface\camera\main.cpp > CMakeFiles\Authentication-System.dir\TestInterface\camera\main.cpp.i

CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\TestInterface\camera\main.cpp -o CMakeFiles\Authentication-System.dir\TestInterface\camera\main.cpp.s

# Object files for target Authentication-System
Authentication__System_OBJECTS = \
"CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj"

# External object files for target Authentication-System
Authentication__System_EXTERNAL_OBJECTS =

Authentication-System.exe: CMakeFiles/Authentication-System.dir/TestInterface/camera/main.cpp.obj
Authentication-System.exe: CMakeFiles/Authentication-System.dir/build.make
Authentication-System.exe: C:/opencv-build/lib/libopencv_gapi460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_highgui460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_ml460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_objdetect460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_photo460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_stitching460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_video460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_calib3d460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_dnn460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_features2d460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_flann460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_videoio460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_imgcodecs460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_imgproc460.dll.a
Authentication-System.exe: C:/opencv-build/lib/libopencv_core460.dll.a
Authentication-System.exe: sources/Mail/libMail.a
Authentication-System.exe: CMakeFiles/Authentication-System.dir/linkLibs.rsp
Authentication-System.exe: CMakeFiles/Authentication-System.dir/objects1
Authentication-System.exe: CMakeFiles/Authentication-System.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Authentication-System.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Authentication-System.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Authentication-System.dir/build: Authentication-System.exe
.PHONY : CMakeFiles/Authentication-System.dir/build

CMakeFiles/Authentication-System.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Authentication-System.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Authentication-System.dir/clean

CMakeFiles/Authentication-System.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build C:\Users\paula\OneDrive\Desktop\Paris\c++\github\Authentification-System\build\CMakeFiles\Authentication-System.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Authentication-System.dir/depend

