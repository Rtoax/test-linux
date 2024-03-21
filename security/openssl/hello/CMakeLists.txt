cmake_minimum_required(VERSION 3.1)
project(openssl-hello LANGUAGES C)

add_executable(client client.c)
add_executable(server server.c)

set_property(TARGET client PROPERTY C_STANDARD 11)
set_property(TARGET server PROPERTY C_STANDARD 11)

find_package(OpenSSL REQUIRED)

target_include_directories(client PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(server PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(client PRIVATE ${OPENSSL_LIBRARIES})
target_link_libraries(server PRIVATE ${OPENSSL_LIBRARIES})
