add_library(Croping croping.cpp croping.hpp)

target_include_directories(Croping INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Croping PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
