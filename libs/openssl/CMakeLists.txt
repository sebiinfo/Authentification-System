add_library(OpensslExternalLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#find_package(OpenSSL REQUIRED)

include(FindOpenSSL)
#find_package(FindOpenSSL)

find_package(OpenSSL REQUIRED)

target_link_libraries(OpensslExternalLibrary INTERFACE OpenSSL)

#include_directories(
#    ${OPENSSL_INCLUDE_DIRS}
#)

#target_link_libraries(OpensslExternalLibrary INTERFACE ${OPENSSL_LIBRARIES})

message(STATUS "OpenSSL library status:")
message(STATUS "    config: ${OPENSSL_DIRS_PATH}")
message(STATUS "    version: ${OPENSSL_VERSION}")
message(STATUS "    libraries: ${OPENSSL_LIBRARIES}")
message(STATUS "    include path: ${OPENSSL_INCLUDE_DIRS}")
#message(STATUS "    install path: ${POCO_INSTALL_PATH}")

#target_link_libraries(OpensslExternalLibrary INTERFACE OpenSSL::SSL)
target_include_directories(OpensslExternalLibrary INTERFACE ${OPENSSL_INCLUDE_DIRS})

