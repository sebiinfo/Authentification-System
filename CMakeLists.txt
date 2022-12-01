cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)


find_package(OpenCV REQUIRED)
find_package(Qt6 OPTIONAL_COMPONENTS Core)


add_subdirectory(libs/opencv)

if(${Qt6_FOUND})
  add_subdirectory(libs/qt)
  qt_standard_project_setup()
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
        PRIVATE "$<$<BOOL:${Qt6_FOUND}>:Qt6::Core>"
        INTERFACE "$<$<${Qt6_FOUND}:libs/qt>:QtExternalLibrary>" 
        INTERFACE OpenCVExternalLibrary)
