cmake_minimum_required(VERSION 3.20)
project(Authentication-System)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp
#         tests.cpp
         )

find_package(OpenCV REQUIRED)
#find_package(Qt6 OPTIONAL_COMPONENTS Core)

add_subdirectory(sources)
add_subdirectory(config)
#add_subdirectory(images)

add_subdirectory(libs/opencv)
if(${Qt6_FOUND})
  add_subdirectory(libs/qt)
  qt_standard_project_setup()
endif()

set(USING_QT "$<BOOL:${Qt6_FOUND}>" CACHE INTERNAL "")
set(INCLUDE_QT "$<${USING_QT}:QtExternalLibrary>" CACHE INTERNAL "")

message(STATUS "MY_VARIABLE=${USING_QT}")
message(STATUS "MY_INCLUDE_QT=${INCLUDE_QT}")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory 
                   resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/resources/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

target_link_libraries(${PROJECT_NAME} 
        PUBLIC ${INCLUDE_QT}
        PUBLIC OpenCVExternalLibrary
        PUBLIC sources
        PUBLIC Config
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR})

