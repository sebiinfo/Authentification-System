add_library(Vectorization fisher.cpp fisher.hpp vectorizer.cpp vectorizer.hpp)

target_link_libraries(Vectorization PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
target_include_directories(Vectorization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

