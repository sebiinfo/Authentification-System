add_library(Database database.cpp database.hpp)

target_include_directories(Database INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Database PUBLIC OpenCVExternalLibrary PUBLIC ${INCLUDE_QT} PUBLIC PocoExternalLibrary)
