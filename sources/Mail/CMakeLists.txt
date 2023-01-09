add_library(Mail mail.cpp mail.hpp mail1.cpp)

target_include_directories(Mail INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Mail PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})