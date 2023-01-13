add_library(Mail mail.cpp mail.hpp questions.cpp)

target_include_directories(Mail INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Mail PRIVATE PocoExternalLibrary PRIVATE ${INCLUDE_QT})
