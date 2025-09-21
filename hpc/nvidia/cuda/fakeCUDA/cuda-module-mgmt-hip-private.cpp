#define __USE_HIP__
#define __HIP_PLATFORM_AMD__
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include <hip/hiprtc.h>


hipError_t hipModuleLaunchKernel(hipFunction_t f,
				 unsigned int gridDimX, unsigned int gridDimY,
				 unsigned int gridDimZ, unsigned int blockDimX,
				 unsigned int blockDimY, unsigned int blockDimZ,
				 unsigned int sharedMemBytes, hipStream_t stream,
				 void** kernelParams, void** extra)
{
	return hipSuccess;
}
