add_library(QtExternalLibrary INTERFACE)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

target_link_libraries(QtExternalLibrary INTERFACE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )