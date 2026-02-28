message(STATUS "cuSparse")
link_libraries(cuda_helpers cusparse)
add_executable(sparse sparse.cu)
