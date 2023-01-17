cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( ${PROJECT_NAME} main.cpp )

find_package(Poco REQUIRED Net)


add_subdirectory(libs/opencv)
add_subdirectory(libs/Poco)
add_subdirectory(libs/openssl)
add_subdirectory(sources)

#find_package(OpenCV REQUIRED)

#find_package(Qt6 REQUIRED COMPONENTS Core)

#dd_subdirectory(libs/qt)
#qt_standard_project_setup()

#include_directories(${OpenCV_INCLUDE_DIRS})


target_link_libraries(${PROJECT_NAME}
       PUBLIC PocoExternalLibrary
       PUBLIC sources
)
