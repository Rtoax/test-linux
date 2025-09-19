// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <malloc.h>
#include <string.h>
#include <sys/types.h>

#include "runtime.hpp"


cudaError_t cudaMalloc(void **devPtr, size_t size)
{
	void *mem;

	if (!devPtr || size <= 0)
		return cudaErrorInvalidValue;

	/* TODO: Limit to total memory of device */

	mem = malloc(size);
	if (!mem)
		return cudaErrorMemoryAllocation;

	*devPtr = mem;

	return cudaSuccess;
}

cudaError_t cudaMallocManaged(void **devPtr, size_t size, unsigned int flags)
{
	/* Note: just ignore flags */
	return cudaMalloc(devPtr, size);
}

cudaError_t cudaFree(void *devPtr)
{
	if (!devPtr)
		return cudaErrorInvalidValue;

	free(devPtr);
	return cudaSuccess;
}

cudaError_t cudaMemAdvise(const void *devPtr, size_t count,
			  cudaMemoryAdvise advice,
			  #if defined(__USE_HPCC__)
			  int device
			  #else
			  cudaMemLocation location
			  #endif
			  )
{
	return cudaSuccess;
}

cudaError_t cudaMemset(void *devPtr, int value, size_t count)
{
	if (!devPtr || count <= 0)
		return cudaErrorInvalidValue;

	memset(devPtr, value, count);

	return cudaSuccess;
}

cudaError_t cudaMemcpy(void *dst, const void *src, size_t count,
		       cudaMemcpyKind kind)
{
	if (!dst || !src)
		return cudaErrorInvalidValue;

	memcpy(dst, src, count);

	return cudaSuccess;
}
