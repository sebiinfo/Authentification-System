add_library(Classification classifier.cpp knn.cpp)

target_link_libraries(Classification PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
target_include_directories(Classification INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
