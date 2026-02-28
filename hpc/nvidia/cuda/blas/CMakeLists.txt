message(STATUS "Blas")
link_libraries(cuda_helpers cublas cublasLt)

add_executable(blas blas.cu)
add_executable(blasLtMatmul blasLtMatmul.cu)
