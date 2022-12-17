
add_library(sources INTERFACE)
add_subdirectory(Croping)
add_subdirectory(Vectorization)
add_subdirectory(Classification)
add_subdirectory(Interfaces)
target_link_libraries(sources INTERFACE Classification INTERFACE Croping INTERFACE Vectorization INTERFACE Interfaces)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

