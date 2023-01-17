add_library(PocoExternalLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Poco REQUIRED COMPONENTS Foundation Net NetSSL Data Util MongoDB Redis)

include_directories(
    ${POCO_INCLUDE_DIRS}
)


message(STATUS "Poco library status:")
message(STATUS "    config: ${Poco_DIRS_PATH}")
message(STATUS "    version: ${Poco_VERSION}")
message(STATUS "    libraries: ${Poco_LIBRARIES}")
message(STATUS "    include path: ${POCO_INCLUDE_DIRS}")
message(STATUS "    install path: ${POCO_INSTALL_PATH}")

target_link_libraries(PocoExternalLibrary INTERFACE ${POCO_LIBRARY_DIRS} INTERFACE ${Poco_LIBRARIES})

target_include_directories(PocoExternalLibrary INTERFACE ${POCO_INCLUDE_DIRS})
