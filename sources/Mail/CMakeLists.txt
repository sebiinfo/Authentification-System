add_library(Mail mail.cpp mail.hpp)

target_include_directories(Mail INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Mail PUBLIC OpenCVExternalLibrary PUBLIC ${INCLUDE_QT} PUBLIC Poco)
