
add_library(sources INTERFACE)
add_subdirectory(Cropping)
add_subdirectory(Vectorization)
add_subdirectory(Classification)
add_subdirectory(Interfaces)
add_subdirectory(Rescale)
target_link_libraries(sources INTERFACE Classification INTERFACE Cropping INTERFACE Vectorization INTERFACE Interfaces INTERFACE Rescale)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
