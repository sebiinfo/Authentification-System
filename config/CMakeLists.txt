add_library(Config INTERFACE)

set(PATH_TO_RESOURCES ${CMAKE_BINARY_DIR})
configure_file(config.h.in config.h @ONLY)

target_include_directories(Config INTERFACE "${CMAKE_BINARY_DIR}/config")
