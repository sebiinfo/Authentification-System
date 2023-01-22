add_library(images INTERFACE)

add_subdirectory(Groups)
add_subdirectory(Storing)
add_subdirectory(Team)
add_subdirectory(Testing)

target_link_libraries(images INTERFACE Team INTERFACE Testing INTERFACE Groups INTERFACE Storing)

target_include_directories(images INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
