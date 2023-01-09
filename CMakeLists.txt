cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#find_package( OpenCV REQUIRED )
#list(APPEND MY_INCLUDES  ${OpenCV_INCLUDE_DIRS} "/usr/local/share/opencv4/haarcascades")
include_directories(MY_INCLUDES)

#add_library(sources INTERFACE)


add_executable( ${PROJECT_NAME} main.cpp )


#add_subdirectory(libs/qt)
#add_subdirectory(libs/opencv)
add_subdirectory(sources)

#find_package(OpenCV REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Core)

#include_directories(${OpenCV_INCLUDE_DIRS})
#qt_standard_project_setup()

target_link_libraries(${PROJECT_NAME}
#      PRIVATE Qt6::Core
#      INTERFACE QtExternalLibrary
PUBLIC sources)
#       INTERFACE OpenCVExternalLibrary)
