add_library(Liveness liveness.cpp)

target_include_directories(Liveness INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Liveness PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT} PRIVATE Interfaces)
