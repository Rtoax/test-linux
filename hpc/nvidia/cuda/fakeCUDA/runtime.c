#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>
#include "device.h"
#include "debug.h"


typedef struct cudaDeviceProp cudaDeviceProp;

cudaError_t cudaSetDevice(int device)
{
	LOG_DEBUG("set dev to %d\n", device);
	return dev_set_current(device);
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

cudaError_t cudaGetDeviceProperties(cudaDeviceProp* prop, int device)
{
	return cudaSuccess;
}
