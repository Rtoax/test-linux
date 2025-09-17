// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>
#include <sys/types.h>
#include "device.h"
#include "debug.h"
#include "types.h"


struct limits {
	size_t cudaLimitStackSize;
	size_t cudaLimitPrintfFifoSize;
	size_t cudaLimitMallocHeapSize;
	size_t cudaLimitDevRuntimeSyncDepth;
	size_t cudaLimitDevRuntimePendingLaunchCount;
	size_t cudaLimitMaxL2FetchGranularity;
	size_t cudaLimitPersistingL2CacheSize;
};


static struct limits limits = {
	.cudaLimitStackSize = 1024,
	.cudaLimitPrintfFifoSize = 1024,
	.cudaLimitMallocHeapSize = 1024,
	.cudaLimitDevRuntimeSyncDepth = 1024,
	.cudaLimitDevRuntimePendingLaunchCount = 1024,
	.cudaLimitMaxL2FetchGranularity = 1024,
	.cudaLimitPersistingL2CacheSize = 1024,
};


#ifdef __cplusplus
extern "C" {
#endif
cudaError_t cudaSetDevice(int device)
{
	LOG_DEBUG("set dev to %d\n", device);
	return (cudaError_t)dev_set_current(device);
}

cudaError_t cudaGetDevice(int *device)
{
	return (cudaError_t)dev_get_current(device);
}

cudaError_t cudaGetLastError(void)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}

const char *cudaGetErrorString(cudaError_t error)
{
	return "Success";
}

cudaError_t cudaGetDeviceCount(int *count)
{
	*count = dev_count();
	return cudaSuccess;
}

cudaError_t cudaDeviceSetLimit(enum cudaLimit limit, size_t value)
{
	switch (limit) {
#define CASE(v)	case v: limits. v = value; break
	CASE(cudaLimitStackSize);
	CASE(cudaLimitPrintfFifoSize);
	CASE(cudaLimitMallocHeapSize);
	CASE(cudaLimitDevRuntimeSyncDepth);
	CASE(cudaLimitDevRuntimePendingLaunchCount);
	CASE(cudaLimitMaxL2FetchGranularity);
	CASE(cudaLimitPersistingL2CacheSize);
#undef CASE
	default:
		return cudaErrorInvalidValue;
	}

	return cudaSuccess;
}

cudaError_t cudaGetDeviceProperties(cudaDeviceProp *prop, int device)
{
	return (cudaError_t)dev_get_prop(device, prop);
}

cudaError_t cudaDeviceGetAttribute(int *value, cudaDeviceAttr attr, int device)
{
	return (cudaError_t)dev_get_attr(device, attr, value);
}

cudaError_t cudaDeviceSynchronize(void)
{
	return cudaSuccess;
}

cudaError_t cudaStreamCreate(cudaStream_t *pStream)
{
	return cudaSuccess;
}

cudaError_t cudaStreamDestroy(cudaStream_t stream)
{
	return cudaSuccess;
}

cudaError_t cudaStreamSynchronize(cudaStream_t stream)
{
	return cudaSuccess;
}

cudaError_t cudaLaunchCooperativeKernel(const void *func,
					dim3 gridDim, dim3 blockDim,
					void **args,
					size_t sharedMem,
					cudaStream_t stream)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}
#ifdef __cplusplus
}
#endif
