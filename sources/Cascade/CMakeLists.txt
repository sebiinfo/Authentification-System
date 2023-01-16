add_library(Cascade cascade_Base.cpp cascade_Base.hpp cascade_detect_cv.cpp cascade_detect_cv.hpp conformity.hpp conformity.cpp )

target_include_directories(Cascade INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Cascade PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})