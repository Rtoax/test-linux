#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>
#include "device.h"


typedef struct cudaDeviceProp cudaDeviceProp;

cudaError_t cudaSetDevice(int device)
{
	return cudaSuccess;
}

cudaError_t cudaGetLastError(void)
{
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

cudaError_t cudaGetDeviceProperties(cudaDeviceProp* prop, int device)
{
	return cudaSuccess;
}
