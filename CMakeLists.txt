cmake_minimum_required(VERSION 3.20)
project(Authentication-System)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
)

find_package(OpenCV REQUIRED)
find_package(Poco REQUIRED Net NetSSL)
find_package(OpenSSL REQUIRED)
find_package(Qt6 OPTIONAL_COMPONENTS Core)

add_subdirectory(sources)
include_directories(${OpenSSL_INCLUDE_DIRS})

if(${Qt6_FOUND})
  add_subdirectory(libs/qt)
  qt_standard_project_setup()
endif()

if(${OpenCV_FOUND})
    add_subdirectory(libs/opencv)
endif()

add_subdirectory(libs/Poco)
add_subdirectory(libs/openssl)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory 
                   resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/resources/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

target_link_libraries(${PROJECT_NAME} 
        PUBLIC ${INCLUDE_QT}
        PUBLIC ${OpenSSL_LIBRARY_DIRS}
        PUBLIC PocoExternalLibrary
        PUBLIC OpenCVExternalLibrary
        PUBLIC sources)
