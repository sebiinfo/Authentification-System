
add_library(sources INTERFACE)
add_subdirectory(Cropimage)
add_subdirectory(Cascade)
add_subdirectory(Detect)
add_subdirectory(Vectorization)
add_subdirectory(Classification)
add_subdirectory(Password)
add_subdirectory(Localization)
add_subdirectory(Interfaces)
add_subdirectory(Rescale)
add_subdirectory(Model)
add_subdirectory(Database)
add_subdirectory(camera)
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
     INTERFACE Cascade
 )



#add_subdirectory(Mail)
# target_link_libraries(sources INTERFACE Mail)

target_link_libraries(sources INTERFACE Database INTERFACE Password INTERFACE camera)

#target_link_libraries(sources INTERFACE Database INTERFACE Password INTERFACE camera)

target_link_libraries(sources
    INTERFACE OpenCVExternalLibrary
    # INTERFACE PocoExternalLibrary
    # INTERFACE OpensslExternalLibrary
    INTERFACE sources
    INTERFACE Database
    INTERFACE Password
    # INTERFACE Mail
    INTERFACE camera)
target_include_directories(sources INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
