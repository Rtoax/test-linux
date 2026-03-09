cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cuda-samples LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../../tools/cmake/Modules/")

# test-linux cmake modules
include(LinuxDistro)
# system cmake modules, see /usr/share/cmake/Modules/FindCUDA/
include(FindCUDA)
include(FindCUDA/select_compute_arch)

add_definitions(${LINUX_DISTRO_CFLAGS})

# If use cu-bridge, USE_CU_BRIDGE be defined and added to cflags
message(STATUS CUDA_NVCC_EXECUTABLE=${CUDA_NVCC_EXECUTABLE})
string(FIND "${CUDA_NVCC_EXECUTABLE}" "cu-bridge" CU_BRIDGE_POSITION)
if(CU_BRIDGE_POSITION GREATER_EQUAL 0)
  set(USE_CU_BRIDGE ON CACHE BOOL "Enable cu-bridge feature" FORCE)
  message(STATUS "Use 'cu-bridge' instead of origin CUDA nvcc")
  add_definitions("-DUSE_CU_BRIDGE=1")
endif()

add_library(cuda_helpers STATIC cuda_helpers.cu)
target_link_libraries(cuda_helpers PRIVATE cuda cusparse cufft curand nvrtc)

include_directories(".")

function(add_cuda_sample class name)
  add_executable(${class}_${name} ${name}.cu)
  set_target_properties(${class}_${name} PROPERTIES
    OUTPUT_NAME ${name}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${class}/
  )
endfunction()

add_subdirectory(blas)
add_subdirectory(dnn)
add_subdirectory(fft)
add_subdirectory(file)
add_subdirectory(intrinsics)
add_subdirectory(pti)
add_subdirectory(rand)
add_subdirectory(samples)
add_subdirectory(solver)
add_subdirectory(sparse)
