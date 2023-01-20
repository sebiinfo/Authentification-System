add_library(sources INTERFACE)

add_subdirectory(Database)
add_subdirectory(Password)
add_subdirectory(Mail)


target_link_libraries(sources
    INTERFACE OpenCVExternalLibrary
    INTERFACE PocoExternalLibrary
    INTERFACE OpensslExternalLibrary
    INTERFACE sources
    INTERFACE Database INTERFACE Password INTERFACE Mail)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
