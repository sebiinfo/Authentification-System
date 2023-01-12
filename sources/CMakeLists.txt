add_library(sources INTERFACE)
add_subdirectory(Cropimage)
add_subdirectory(Detect)
add_subdirectory(Vectorization)
add_subdirectory(Classification)
add_subdirectory(Password)
add_subdirectory(Localization)
add_subdirectory(Interfaces)
add_subdirectory(Rescale)
add_subdirectory(Model)

target_link_libraries(sources
     INTERFACE Cropimage
     INTERFACE Detect
     INTERFACE Vectorization
     INTERFACE Classification
     INTERFACE Password
     INTERFACE Localization
     INTERFACE Interfaces
     INTERFACE Rescale
     INTERFACE Model
 )

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
