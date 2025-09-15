#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include "device.h"
#include "debug.h"
#include "types.h"


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
