add_library(OpenCVExternalLibrary INTERFACE)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

target_link_libraries(OpenCVExternalLibrary INTERFACE
        ${OpenCV_LIBS}
        )
