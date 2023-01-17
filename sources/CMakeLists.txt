add_library(sources INTERFACE)

add_subdirectory(Database)
add_subdirectory(Password)


target_link_libraries(sources INTERFACE Database INTERFACE Password)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
