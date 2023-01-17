add_library(OpensslExternalLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenSSL REQUIRED COMPONENTS SSL Crypto)


#set(CMAKE_PREFIX_PATH "/usr/local/opt/openssl")
#target_include_directories( OpensslExternalLibrary INTERFACE "/usr/local/opt/openssl/include")
#target_link_directories(OpensslExternalLibrary INTERFACE "/usr/local/opt/openssl/lib")



message(STATUS "OpenSSL library status:")
message(STATUS "    config: ${OPENSSL_DIRS_PATH}")
message(STATUS "    version: ${OPENSSL_VERSION}")
message(STATUS "    libraries: ${OPENSSL_LIBRARIES}")
message(STATUS "    include path: ${OPENSSL_INCLUDE_DIRS}")

#target_link_libraries(OpensslExternalLibrary PUBLIC ${OPENSSL_LIBRARIES})
target_link_libraries(OpensslExternalLibrary INTERFACE ${OPENSSL_LIBRARIES})
target_include_directories(OpensslExternalLibrary INTERFACE ${OPENSSL_INCLUDE_DIRS})
