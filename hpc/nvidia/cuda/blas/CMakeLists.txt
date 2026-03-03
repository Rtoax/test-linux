message(STATUS "cuBlas")

link_libraries(cuda_helpers cublas cublasLt)

add_cuda_sample(blas blas)
add_cuda_sample(blas blasLtMatmul)
