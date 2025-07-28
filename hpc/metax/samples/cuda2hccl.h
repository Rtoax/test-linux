// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Metax has CUDA-compatible APIs */
#pragma once

#define cudaError_t	hcError_t

#define cudaMalloc(pp, sz)	hcMalloc(pp, sz)
#define cudaFree(ptr)	hcFree(ptr)
#define cudaMemset(ptr, v, size)	hcMemset(ptr, v, size)
#define cudaMemcpy(dev, host, size, flag)	hcMemcpy(dev, host, size, flag)
#define cudaMemcpyHostToDevice	hcMemcpyHostToDevice
#define cudaMemcpyDeviceToHost	hcMemcpyDeviceToHost

#define cudaEvent_t	hcEvent_t
#define cudaEventCreate(pe)	hcEventCreate(pe)
#define cudaEventDestroy(ev)	hcEventDestroy(ev)
#define cudaEventRecord(ev)	hcEventRecord(ev)
#define cudaEventElapsedTime(pt, start, stop)	hcEventElapsedTime(pt, start, stop)
#define cudaEventSynchronize(ev)	hcEventSynchronize(ev)

#define cudaGetDeviceProperties(prop, devid)	hcGetDeviceProperties(prop, devid)

#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	hcDeviceGetP2PAttribute(v, attr, src, dst)
#define cudaDevP2PAttrPerformanceRank	hcDevP2PAttrPerformanceRank
#define cudaDevP2PAttrAccessSupported	hcDevP2PAttrAccessSupported
#define cudaDevP2PAttrNativeAtomicSupported	hcDevP2PAttrNativeAtomicSupported

#define cudaDeviceSynchronize()	hcDeviceSynchronize()

#define cublasStatus_t	hcblasStatus_t
#define CUBLAS_STATUS_SUCCESS	HCBLAS_STATUS_SUCCESS
#define CUBLAS_STATUS_NOT_INITIALIZED	HCBLAS_STATUS_NOT_INITIALIZED
#define CUBLAS_STATUS_ALLOC_FAILED	HCBLAS_STATUS_ALLOC_FAILED
#define CUBLAS_STATUS_INVALID_VALUE	HCBLAS_STATUS_INVALID_VALUE
#define CUBLAS_STATUS_ARCH_MISMATCH	HCBLAS_STATUS_ARCH_MISMATCH
#define CUBLAS_STATUS_MAPPING_ERROR	HCBLAS_STATUS_MAPPING_ERROR
#define CUBLAS_STATUS_EXECUTION_FAILED	HCBLAS_STATUS_EXECUTION_FAILED
#define CUBLAS_STATUS_INTERNAL_ERROR	HCBLAS_STATUS_INTERNAL_ERROR
#define CUBLAS_STATUS_NOT_SUPPORTED	HCBLAS_STATUS_NOT_SUPPORTED
#define cublasHandle_t	hcblasHandle_t
#define cublasCreate(handle)	hcblasCreate(handle)
#define cublasDestroy(handle)	hcblasDestroy(handle)
