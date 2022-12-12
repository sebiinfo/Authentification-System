add_library(Classification classification.cpp)

target_include_directories(Classification PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Classification PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT} PRIVATE Interfaces)
