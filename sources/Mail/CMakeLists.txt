add_library(Mail mail.cpp main.cpp mail.hpp)

target_include_directories(Mail INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Mail PRIVATE PocoExternalLibrary PRIVATE ${INCLUDE_QT})
