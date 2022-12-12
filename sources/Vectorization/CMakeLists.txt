add_library(Vectorization fisher.cpp)

target_include_directories(Vectorization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Vectorization PRIVATE OpenCVExternalLibrary PRIVATE QtExternalLibrary)
