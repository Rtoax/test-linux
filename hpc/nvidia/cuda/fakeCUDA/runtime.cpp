// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "runtime.hpp"


struct limits {
	size_t cudaLimitStackSize;
	size_t cudaLimitPrintfFifoSize;
	size_t cudaLimitMallocHeapSize;
	#ifndef __USE_HIP__
	size_t cudaLimitDevRuntimeSyncDepth;
	size_t cudaLimitDevRuntimePendingLaunchCount;
	size_t cudaLimitMaxL2FetchGranularity;
	size_t cudaLimitPersistingL2CacheSize;
	#endif
};


static struct limits limits = {
	.cudaLimitStackSize = 1024,
	.cudaLimitPrintfFifoSize = 1024,
	.cudaLimitMallocHeapSize = 1024,
	#ifndef __USE_HIP__
	.cudaLimitDevRuntimeSyncDepth = 1024,
	.cudaLimitDevRuntimePendingLaunchCount = 1024,
	.cudaLimitMaxL2FetchGranularity = 1024,
	.cudaLimitPersistingL2CacheSize = 1024,
	#endif
};


cudaError_t cudaSetDevice(int device)
{
	DEBUG_DBG("set dev to %d\n", device);
	return (cudaError_t)devSetCurrent(device);
}

cudaError_t cudaGetDevice(int *device)
{
	return (cudaError_t)devGetCurrent(device);
}

cudaError_t cudaGetLastError()
{
	DEBUG_DBG("\n");
	return cudaSuccess;
}

const char *cudaGetErrorString(cudaError_t error)
{
	return "Success";
}

cudaError_t cudaGetDeviceCount(int *count)
{
	*count = devCount();
	return cudaSuccess;
}

cudaError_t cudaDeviceSetLimit(cudaLimit limit, size_t value)
{
	switch (limit) {
#define CASE(v)	case v: limits. v = value; break
	CASE(cudaLimitStackSize);
	CASE(cudaLimitPrintfFifoSize);
	CASE(cudaLimitMallocHeapSize);
	#ifndef __USE_HIP__
	CASE(cudaLimitDevRuntimeSyncDepth);
	CASE(cudaLimitDevRuntimePendingLaunchCount);
	CASE(cudaLimitMaxL2FetchGranularity);
	CASE(cudaLimitPersistingL2CacheSize);
	#endif
#undef CASE
	default:
		return cudaErrorInvalidValue;
	}

	return cudaSuccess;
}

cudaError_t cudaGetDeviceProperties(cudaDeviceProp *prop, int device)
{
	devGetName(device, prop->name, sizeof(prop->name));
	prop->totalGlobalMem = devTotalGlobalMem(device);
	prop->totalConstMem = devTotalConstMem(device);
	prop->l2CacheSize = devL2CacheSize(device);
	#ifndef __USE_HIP__ /* HIP version: 5.7.31921-0 */
	prop->globalL1CacheSupported = devGlobalL1CacheSupported(device);
	prop->localL1CacheSupported = devLocalL1CacheSupported(device);
	#endif
	prop->managedMemory = devManagedMemory(device);
	prop->memoryBusWidth = devMemoryBusWidth(device);
	prop->ECCEnabled = devECCEnabled(device);
	prop->multiProcessorCount = devMultiProcessorCount(device);
	prop->maxThreadsPerMultiProcessor = devMaxThreadsPerMultiProcessor(device);
	prop->maxThreadsPerBlock = devMaxThreadsPerBlock(device);
	prop->maxThreadsDim[0] = devMaxThreadsDimx(device);
	prop->maxThreadsDim[1] = devMaxThreadsDimy(device);
	prop->maxThreadsDim[2] = devMaxThreadsDimz(device);
	prop->maxGridSize[0] = devMaxGridSizex(device);
	prop->maxGridSize[1] = devMaxGridSizey(device);
	prop->maxGridSize[2] = devMaxGridSizez(device);
	prop->major = devMajor(device);
	prop->minor = devMinor(device);
	//prop->clockRate = devClockRate(device);
	prop->warpSize = devWarpSize(device);

	return cudaSuccess;
}

cudaError_t cudaDeviceGetAttribute(int *value, cudaDeviceAttr attr, int device)
{
	switch (attr) {
	case cudaDevAttrEccEnabled:
		*value = devECCEnabled(device);
		break;
	case cudaDevAttrManagedMemory:
		*value = devManagedMemory(device);
		break;
	case cudaDevAttrL2CacheSize:
		*value = devL2CacheSize(device);
		break;
	case cudaDevAttrClockRate:
		*value = devClockRate(device);
		break;
	case cudaDevAttrMaxThreadsPerBlock:
		*value = devMaxThreadsPerBlock(device);
		break;
	case cudaDevAttrMaxThreadsPerMultiProcessor:
		*value = devMaxThreadsPerMultiProcessor(device);
		break;
	#ifndef __USE_HIP__
	case cudaDevAttrHostNumaId:
		*value = 0;	/* TODO */
		break;
	#endif
	case cudaDevAttrWarpSize:
		*value = devWarpSize(device);
		break;
	default:
		return cudaErrorInvalidValue;
	}
	return cudaSuccess;
}

cudaError_t cudaDeviceDisablePeerAccess(int peerDevice)
{
	return cudaSuccess;
}

cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice)
{
	return cudaSuccess;
}

cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr,
				      int srcDevice, int dstDevice)
{
	return cudaSuccess;
}

cudaError_t cudaDeviceSynchronize()
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

cudaError_t cudaStreamIsCapturing(cudaStream_t stream,
				  enum cudaStreamCaptureStatus *pCaptureStatus)
{
	return cudaSuccess;
}

cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim,
			     void **args, size_t sharedMem, cudaStream_t stream)
{
	DEBUG_DBG("\n");
	return __cudaLaunchKernel((cudaKernel_t)func, gridDim, blockDim, args,
			   sharedMem, stream);
}

cudaError_t cudaLaunchCooperativeKernel(const void *func,
					dim3 gridDim, dim3 blockDim,
					void **args,
					#if defined(__USE_HPCC__) || defined(__USE_HIP__)
					unsigned int sharedMem,
					#else
					size_t sharedMem,
					#endif
					cudaStream_t stream)
{
	DEBUG_DBG("\n");
	return cudaSuccess;
}

nvrtcResult nvrtcDestroyProgram(nvrtcProgram *prog)
{
	return NVRTC_SUCCESS;
}

nvrtcResult nvrtcCompileProgram(nvrtcProgram prog,
				int numOptions,
				#if defined(__USE_HIP__)
				const char **options
				#else
				const char * const *options
				#endif
			       )
{
	return NVRTC_SUCCESS;
}

nvrtcResult nvrtcGetProgramLog(nvrtcProgram prog, char *log)
{
	return NVRTC_SUCCESS;
}
