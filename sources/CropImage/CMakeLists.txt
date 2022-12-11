add_library(CropImage cropimage.cpp class.cpp)

target_include_directories(CropImage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CropImage OpenCVExternalLibrary)
