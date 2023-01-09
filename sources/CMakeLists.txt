add_library(sources INTERFACE)
add_subdirectory(Mail)


target_link_libraries(sources INTERFACE Mail)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
