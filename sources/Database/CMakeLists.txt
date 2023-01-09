#cmake_minimum_required(VERSION 3.14)
#project(Authentication-System)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(${PROJECT_NAME} main.cpp)

#add_subdirectory(libs/qt)
#add_subdirectory(libs/opencv)

#find_package(OpenCV REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Core)

#include_directories(${OpenCV_INCLUDE_DIRS})
#qt_standard_project_setup()

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core
#        INTERFACE QtExternalLibrary
#        INTERFACE OpenCVExternalLibrary)

cmake_minimum_required(VERSION 3.14)

project(Authentication-System LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set_target_properties(main_executable PROPERTIES FOLDER "qtc_runnable")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Authentication-System
  main.cpp csv_file.cpp csv.hpp
)
target_link_libraries(Authentication-System Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS Authentication-System
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

