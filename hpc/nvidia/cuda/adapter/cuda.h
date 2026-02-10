// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_H
#define __CUDA_ADAPTER_CUDA_H 1

/**
 * CUDA: typedef __device_builtin__ struct CUstream_st *cudaStream_t;
 */
#define CUstream_st __CU(stream_st)

/**
 * typedef struct CUstream_st *CUstream;
 */
#define CUstream __CU(stream)

/**
 * CUDA:
 * driver_types.h: typedef struct CUevent_st *cudaEvent_t;
 * cuda.h: typedef struct CUevent_st *CUevent;
 *
 * HPCC: typedef struct HCevent_st *hcEvent_t;
 * HIP: typedef struct ihipEvent_t* hipEvent_t;
 */
#ifdef __USE_HIP__
#define CUevent_st ihipEvent_t
#else
#define CUevent_st __CU(event_st)
#endif

/**
 * CUDA 13:
 * CUresult cuGetErrorName(CUresult error, const char **pStr);
 *
 * LUCA:
 * const char *lcGetErrorName(lcError_t lc_error);
 */
#if defined(__USE_LUCA__) || defined(__USE_HPCC__) || defined(__USE_HIP__)
#define cuGetErrorName(error, pStr)                  \
	do {                                         \
		const char **__pstr = pStr;          \
		*__pstr = __cu(GetErrorName(error)); \
	} while (0)
#else
#define cuGetErrorName __cu(GetErrorName)
#endif

/**
 * CUDA 13
 * CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX,
 *                         unsigned int gridDimY, unsigned int gridDimZ,
 *                         unsigned int blockDimX, unsigned int blockDimY,
 *                         unsigned int blockDimZ, unsigned int sharedMemBytes,
 *                         CUstream hStream, void **kernelParams, void **extra);
 *
 * LUCA:
 * lcError_t lcLaunchKernel(const void *function_address, dim3 numBlocks,
 *                          dim3 dimBlocks, void **args,
 */
#define cuLaunchKernel __cu(LaunchKernel)

#endif
