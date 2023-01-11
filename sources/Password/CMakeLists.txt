add_library(Password password.cpp password.hpp main.cpp)

target_include_directories(Password INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Password PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
