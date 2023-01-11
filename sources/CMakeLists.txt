
add_library(sources INTERFACE Liveness/liveness.cpp)
add_subdirectory(Cropping)
add_subdirectory(Vectorization)
add_subdirectory(Classification)
add_subdirectory(Localization)
add_subdirectory(Interfaces)
add_subdirectory(Rescale)
add_subdirectory(Model)
target_link_libraries(sources INTERFACE Model INTERFACE Classification INTERFACE Cropping INTERFACE Vectorization INTERFACE Interfaces INTERFACE Rescale INTERFACE Localization)

target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
