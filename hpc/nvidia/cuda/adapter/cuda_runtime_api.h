// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_RUNTIME_API_H
#define __CUDA_ADAPTER_CUDA_RUNTIME_API_H 1

/**
 * CUDA 13
 * cudaError_t cudaPeekAtLastError(void);
 *
 * HIP 6.3.42133-0
 * hipError_t hipPeekAtLastError(void);
 */
#define cudaPeekAtLastError() __cuda(PeekAtLastError())

#define cudaGetLastError() __cuda(GetLastError())
#define cudaGetErrorString(err) __cuda(GetErrorString(err))

/**
 * CUDA 13:
 * const char* cudaGetErrorName(cudaError_t error);
 *
 * HIP 6.3.42133-0
 * const char* hipGetErrorName(hipError_t hip_error);
 */
#define cudaGetErrorName(error) __cuda(GetErrorName(error))

#define cudaDeviceSetLimit(limit, value) __cuda(DeviceSetLimit(limit, value))
#define cudaDeviceGetLimit(limit, value) __cuda(DeviceGetLimit(limit, value))

#endif
