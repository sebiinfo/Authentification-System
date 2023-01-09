add_library(Rescale rescale.cpp rescale.hpp)

target_include_directories(Rescale INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rescale PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
