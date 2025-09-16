#include <cuda.h>
#include <cuda_runtime.h>
#include <sys/types.h>

#include "debug.h"


/**
 * /usr/local/cuda-13.0/targets/x86_64-linux/include/driver_types.h
 * typedef __device_builtin__ struct CUkern_st *cudaKernel_t;
 */
struct CUkern_st {
};


void **__cudaRegisterFatBinary(void *fatCubin)
{
	LOG_DEBUG("fatCubin %p\n", fatCubin);
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
	LOG_DEBUG("hostFun %p, deviceFun %p, deviceName %s, thread_limit %d\n",
		  hostFun, deviceFun, deviceName, thread_limit);
}

unsigned __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim,
				     size_t sharedMem,
				     struct CUstream_st *stream)
{
	LOG_DEBUG("grid(%d,%d,%d), block(%d,%d,%d), sharedMem %ld\n",
		  gridDim.x, gridDim.y, gridDim.z,
		  blockDim.x, blockDim.y, blockDim.z,
		  sharedMem);
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
	LOG_DEBUG("kernel %p\n", kernel);
	return cudaSuccess;
}
