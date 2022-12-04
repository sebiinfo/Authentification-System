cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_CXX_STANDARD 11)
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

set(USING_QT "$<BOOL:${Qt6_FOUND}>")

message(STATUS "MY_VARIABLE=${USING_QT}")


target_link_libraries(${PROJECT_NAME} 
        PRIVATE "$<${USING_QT}:Qt6::Core>"
        PUBLIC "$<${USING_QT}:QtExternalLibrary>" 
        PUBLIC OpenCVExternalLibrary)
