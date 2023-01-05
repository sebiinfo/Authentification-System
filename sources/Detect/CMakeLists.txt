add_library(Detect detect.cpp detect.hpp)

target_include_directories(Detect INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Detect PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})