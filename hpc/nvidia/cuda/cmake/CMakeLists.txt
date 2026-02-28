cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cuda-samples LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

set(SRCDIR "../")

# see /usr/share/cmake/Modules/FindCUDA/
include(FindCUDA)
include(FindCUDA/select_compute_arch)

message(STATUS CUDA_NVCC_EXECUTABLE=${CUDA_NVCC_EXECUTABLE})

add_library(cuda_helpers STATIC ${SRCDIR}/cuda_helpers.cu)

include_directories(${SRCDIR})
link_libraries(cusparse cufft curand cuda_helpers)

add_executable(hello ${SRCDIR}/samples/hello.cu)
