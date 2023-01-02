add_library(Localization INTERFACE localizer.hpp)

target_include_directories(Localization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(Localization PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT} PRIVATE Interfaces)
