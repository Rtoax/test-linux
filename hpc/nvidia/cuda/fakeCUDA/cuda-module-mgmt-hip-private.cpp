#define __USE_HIP__
#define __HIP_PLATFORM_AMD__
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include <hip/hiprtc.h>

extern "C" {

hipError_t hipModuleLaunchKernel(hipFunction_t f,
				 unsigned int gridDimX, unsigned int gridDimY,
				 unsigned int gridDimZ, unsigned int blockDimX,
				 unsigned int blockDimY, unsigned int blockDimZ,
				 unsigned int sharedMemBytes, hipStream_t stream,
				 void** kernelParams, void** extra)
{
	return hipSuccess;
}

hipError_t hipExtModuleLaunchKernel(hipFunction_t f, uint32_t globalWorkSizeX,
				    uint32_t globalWorkSizeY, uint32_t globalWorkSizeZ,
				    uint32_t localWorkSizeX, uint32_t localWorkSizeY,
				    uint32_t localWorkSizeZ, size_t sharedMemBytes,
				    hipStream_t hStream, void** kernelParams, void** extra,
				    hipEvent_t startEvent,
				    hipEvent_t stopEvent,
				    uint32_t flags)
{
	return hipSuccess;
}
}
