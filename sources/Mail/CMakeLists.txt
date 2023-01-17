add_library(Mail mail.cpp)

target_include_directories(Mail INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Mail PRIVATE ${INCLUDE_QT})
