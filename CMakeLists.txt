cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( ${PROJECT_NAME} main.cpp )


add_subdirectory(libs/opencv)
add_subdirectory(libs/Poco)
add_subdirectory(libs/openssl)
add_subdirectory(sources)


target_link_libraries(${PROJECT_NAME}
    PUBLIC OpenCVExternalLibrary
    PUBLIC PocoExternalLibrary
    PUBLIC OpensslExternalLibrary
    PUBLIC sources
)
