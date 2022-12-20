add_library(Password password.cpp password.hpp)

target_include_directories(Rescale INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rescale PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})