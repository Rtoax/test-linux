// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Metax has CUDA-compatible APIs */
#pragma once

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
