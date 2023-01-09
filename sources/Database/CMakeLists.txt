add_library(Database csv_file.cpp csv_file.hpp)

target_include_directories(Database INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Database PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
