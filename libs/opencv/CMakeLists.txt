add_library(OpenCVExternalLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    install path: ${OpenCV_INSTALL_PATH}")

target_link_libraries(OpenCVExternalLibrary INTERFACE
        ${OpenCV_LIBS}
        )
target_include_directories(OpenCVExternalLibrary INTERFACE ${OpenCV_INCLUDE_DIRS})