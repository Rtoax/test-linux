#include <cuda.h>
#include <cuda_runtime.h>
#include <sys/types.h>

#include "debug.h"


void **__cudaRegisterFatBinary(void *fatCubin)
{
	LOG_DEBUG("\n");
	return NULL;
}

void __cudaRegisterFatBinaryEnd(void **fatCubinHandle)
{
	LOG_DEBUG("\n");
}

void __cudaUnregisterFatBinary(void **fatCubinHandle)
{
	LOG_DEBUG("\n");
}

void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
			    char *deviceFun, const char *deviceName,
			    int thread_limit, uint3 *tid, uint3 *bid,
			    dim3 *bDim, dim3 *gDim, int *wSize)
{
	LOG_DEBUG("\n");
}

unsigned __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim,
				     size_t sharedMem,
				     struct CUstream_st *stream)
{
	LOG_DEBUG("\n");
	return 0;
}

cudaError_t __cudaGetKernel(cudaKernel_t *kernel, const void *v)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}

cudaError_t __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim,
				       size_t *sharedMem, void *stream)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}

cudaError_t __cudaLaunchKernel(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim,
			       void **args, size_t sharedMem,
			       cudaStream_t stream)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}
