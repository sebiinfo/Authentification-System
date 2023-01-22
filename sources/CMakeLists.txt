add_library(sources INTERFACE)
# add_subdirectory(Mail)
add_subdirectory(Database)
add_subdirectory(Password)
add_subdirectory(camera)
# target_link_libraries(sources INTERFACE Mail)

target_link_libraries(sources INTERFACE Database INTERFACE Password INTERFACE camera)
add_subdirectory(Mail)


target_link_libraries(sources
    INTERFACE OpenCVExternalLibrary
    INTERFACE PocoExternalLibrary
    INTERFACE OpensslExternalLibrary
    INTERFACE sources
    INTERFACE Database INTERFACE Password INTERFACE Mail)
target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
