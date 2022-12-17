add_library(Cropping cropimage.cpp cropimage.hpp)

target_include_directories(Cropping INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Cropping PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
