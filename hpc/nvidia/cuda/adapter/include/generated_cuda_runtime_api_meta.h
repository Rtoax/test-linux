// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include "wrapper_defs.h"

#define cudaMemcpy_v3020_params cudaX(Memcpy_params)

/**
 * CUDA 13.0
 * typedef struct cudaLaunchKernel_v7000_params_st {
 *   const void *func;
 *   dim3 gridDim;
 *   dim3 blockDim;
 *   void **args;
 *   size_t sharedMem;
 *   cudaStream_t stream;
 * } cudaLaunchKernel_v7000_params;
 *
 * LUCA 3.2.1
 * typedef struct lcLaunchKernel_params_st {
 *   const void* function_address;
 *   dim3 numBlocks;
 *   dim3 dimBlocks;
 *   void** args;
 *   void* args__val;
 *   size_t sharedMemBytes;
 *   lcStream_t stream;
 * } lcLaunchKernel_params;
 */
#define cudaLaunchKernel_v7000_params cudaX(LaunchKernel_params)

/**
 * CUDA 13:
 * typedef struct cudaMalloc_v3020_params_st {
 *   void **devPtr;
 *   size_t size;
 * } cudaMalloc_v3020_params;
 *
 * LUCA:
 * typedef struct lcMalloc_params_st {
 *   void** ptr;
 *   void* ptr__val;
 *   size_t bytesize;
 * } lcMalloc_params;
 */
#define cudaMalloc_v3020_params cudaX(Malloc_params)
