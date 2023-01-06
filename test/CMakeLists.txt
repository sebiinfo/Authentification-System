knn_current_object(test test.cpp)
add_subdirectory(images)

#target_include_directories(Cropping INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test PRIVATE
    OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
