add_library(sources INTERFACE)
add_subdirectory(Cropimage)
add_subdirectory(Detect)
add_subdirectory(Password)
add_subdirectory(Rescale)

target_link_libraries(sources INTERFACE Cropimage INTERFACE Detect INTERFACE Password INTERFACE Rescale)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
