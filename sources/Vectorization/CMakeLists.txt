add_library(Vectorization fisher.cpp vectorizer.cpp lda1.cpp LinearDiscriminantAnalysis.h)

target_link_libraries(Vectorization PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
target_include_directories(Vectorization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

