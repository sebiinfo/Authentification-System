add_library(Password profile.cpp profile.hpp)

target_include_directories(Password INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Password PUBLIC OpenCVExternalLibrary PUBLIC ${INCLUDE_QT} PUBLIC PocoExternalLibrary)
