# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(camera LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia MultimediaWidgets Widgets)

set(camera_form "")
set(videosettings_form "")
if(ANDROID OR IOS)
    set(camera_form camera_mobile.ui)
    set(videosettings_form videosettings_mobile.ui)
else()
    set(camera_form camera.ui)
    set(videosettings_form videosettings.ui)
endif()

qt_add_library(camera
    MANUAL_FINALIZATION
    camera.cpp camera.h ${camera_form}
    imagesettings.cpp imagesettings.h imagesettings.ui
    # videosettings.cpp videosettings.h ${videosettings_form}
    # metadatadialog.cpp metadatadialog.h
)

set_target_properties(camera PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(APPLE AND NOT IOS)
    set_target_properties(camera PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/macos/Info.plist.in"
    )
elseif(IOS)
    set_target_properties(camera PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/ios/Info.plist.in"
    )
endif()

set(PATH_TO_RESOURCES ${CMAKE_BINARY_DIR})
set_property(TARGET camera APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
             ${CMAKE_CURRENT_SOURCE_DIR}/android)

target_link_libraries(camera PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Multimedia
    Qt::MultimediaWidgets
    Qt::Widgets
)

# Resources:
set(camera_resource_files
    "images/shutter.svg"
)

qt_add_resources(camera "camera"
    PREFIX
        "/"
    FILES
        ${camera_resource_files}
)
target_include_directories(camera INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if(WIN32)
target_link_libraries(camera PUBLIC Database)
else()
target_link_libraries(camera INTERFACE Database)
endif()
target_link_libraries(camera PRIVATE OpenCVExternalLibrary PRIVATE ${INCLUDE_QT})
configure_file(config.h.in config.h @ONLY)
target_include_directories(camera PUBLIC "${CMAKE_BINARY_DIR}/sources/camera")
add_compile_options(-fPIC)
qt_finalize_executable(camera)
