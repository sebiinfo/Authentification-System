add_library(Database database.cpp database.hpp main.cpp)

target_include_directories(Database INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(Database PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
