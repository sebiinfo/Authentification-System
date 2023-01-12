add_library(Localization
    localizer.hpp
    localizer.cpp)

target_include_directories(Localization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Localization PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT} PRIVATE Interfaces)

#add_library(Cropimage cropimage.cpp cropimage.hpp)

#target_include_directories(Cropimage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(Cropimage PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
