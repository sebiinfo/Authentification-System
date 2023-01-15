add_library(sources INTERFACE)
# add_subdirectory(Mail)
#add_subdirectory(camera)

target_link_libraries(sources INTERFACE camera)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
