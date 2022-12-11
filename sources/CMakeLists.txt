
add_library(sources INTERFACE)
add_subdirectory(CropImage)
add_subdirectory(Vectorization)
add_subdirectory(Classification)

target_link_libraries(sources INTERFACE Classification INTERFACE CropImage INTERFACE Vectorization)
target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

