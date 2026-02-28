message(STATUS "Samples")
link_libraries(cuda_helpers)

add_executable(hello hello.cu)
add_executable(dim3 dim3.cu)
