add_library(Model model.cpp model.hpp)

target_include_directories(Model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Model PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT} PRIVATE Interfaces PRIVATE Classification PRIVATE Vectorization PRIVATE Localization PRIVATE Config)
