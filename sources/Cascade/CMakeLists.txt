add_library(Cascade Cascade_Object_Detector.cpp Cascade_Object_Detector.hpp)

target_include_directories(Cascade INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Cascade PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})