// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
/* Metax has CUDA-compatible APIs */
#define cudaMalloc	hcMalloc
#define cudaFree	hcFree
#define cudaMemset	hcMemset
#define cudaMemcpy	hcMemcpy
#define cudaMemcpyHostToDevice	hcMemcpyHostToDevice
#define cudaMemcpyDeviceToHost	hcMemcpyDeviceToHost
#define cudaEvent_t	hcEvent_t
#define cudaEventCreate	hcEventCreate
#define cudaEventDestroy	hcEventDestroy
#define cudaEventRecord	hcEventRecord
#define cudaEventElapsedTime	hcEventElapsedTime
#define cudaEventSynchronize	hcEventSynchronize
#define cudaGetDeviceProperties(prop, devid)	hcGetDeviceProperties(prop, devid)
#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	hcDeviceGetP2PAttribute(v, attr, src, dst)
#define cudaDevP2PAttrPerformanceRank	hcDevP2PAttrPerformanceRank
#define cudaDevP2PAttrAccessSupported	hcDevP2PAttrAccessSupported
#define cudaDevP2PAttrNativeAtomicSupported	hcDevP2PAttrNativeAtomicSupported
#define cudaDeviceSynchronize()	hcDeviceSynchronize()
