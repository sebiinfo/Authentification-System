cmake_minimum_required(VERSION 3.22)
project(Authentification_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Authentification_System main.cpp)

find_package(OpenCV REQUIRED)
