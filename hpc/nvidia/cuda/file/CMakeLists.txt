message(STATUS "cuFile")
link_libraries(cuda_helpers cufile)

add_executable(gdsio gdsio.cu)
