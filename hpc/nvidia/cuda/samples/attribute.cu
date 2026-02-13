#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

int main(int argc, char *argv[])
{
	int i, value, dev;

	dev = 0;

	fprintf(stderr, "Usage: %s [dev=<N>]\n", argv[0]);

	for (i = 1; i < argc; i++) {
#define arg_eq(v) if (!strncmp(#v"=", argv[i], strlen(#v) + 1)) \
			v = atoi(argv[i] + strlen(#v) + 1);
		arg_eq(dev);
#undef arg_eq
	}

	gpu_init(dev);

#define Attr(attr) do {	\
		cudaDeviceGetAttribute(&value, attr, dev);	\
		printf("%-64s %d(0x%x)\n", #attr, value, value);	\
	} while (0)

	Attr(cudaDevAttrEccEnabled);
	Attr(cudaDevAttrManagedMemory);
	Attr(cudaDevAttrL2CacheSize);
	Attr(cudaDevAttrClockRate);
	Attr(cudaDevAttrMaxThreadsPerBlock);
	Attr(cudaDevAttrMaxThreadsPerMultiProcessor);
#if !defined(__HIPCC__) && (CUDA_VERSION >= 12000)
	Attr(cudaDevAttrHostNumaId);
#endif
#if !defined(__NVCC__)
	Attr(cudaDevAttrAsicRevision);
#endif
	Attr(cudaDevAttrAsyncEngineCount);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrCanFlushRemoteWrites);
#endif
	Attr(cudaDevAttrCanMapHostMemory);
	Attr(cudaDevAttrCanUseHostPointerForRegisteredMem);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrCanUseStreamMemOps);
#endif
#if !defined(__NVCC__)
	Attr(cudaDevAttrCanUseStreamWaitValue);
#endif
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrCanUseStreamWaitWaitValueNor);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrClusterLaunch);
#endif
	Attr(cudaDevAttrComputeCapabilityMajor);
	Attr(cudaDevAttrComputeCapabilityMinor);
	Attr(cudaDevAttrComputeMode);
	Attr(cudaDevAttrComputePreemptionSupported);
	Attr(cudaDevAttrConcurrentKernels);
	Attr(cudaDevAttrConcurrentManagedAccess);
	Attr(cudaDevAttrCooperativeLaunch);
#if !defined(__NVCC__)
	Attr(cudaDevAttrCooperativeMultiDeviceLaunch);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedFunc);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrDeferredMappingCudaArraySupported);
#endif
	Attr(cudaDevAttrDirectManagedMemAccessFromHost);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrGenericCompressionSupported);
#endif
	Attr(cudaDevAttrGlobalL1CacheSupported);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrGPUDirectRDMAFlushWritesOptions);
	Attr(cudaDevAttrGPUDirectRDMASupported);
	Attr(cudaDevAttrGPUDirectRDMAWritesOrdering);
	Attr(cudaDevAttrGpuOverlap);
#endif
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrHandleTypePosixFileDescriptorSupported);
	Attr(cudaDevAttrHandleTypeWin32HandleSupported);
#endif
#if !defined(__NVCC__)
	Attr(cudaDevAttrHdpMemFlushCntl);
	Attr(cudaDevAttrHdpRegFlushCntl);
#endif
	Attr(cudaDevAttrHostNativeAtomicSupported);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrHostRegisterReadOnlySupported);
#endif
	Attr(cudaDevAttrHostRegisterSupported);
	Attr(cudaDevAttrIntegrated);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrIpcEventSupport);
#endif
	Attr(cudaDevAttrIsMultiGpuBoard);
	Attr(cudaDevAttrKernelExecTimeout);
	Attr(cudaDevAttrLocalL1CacheSupported);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrLocalSocketId);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxAccessPolicyWindowSize);
#endif
	Attr(cudaDevAttrMaxBlockDimX);
	Attr(cudaDevAttrMaxBlockDimY);
	Attr(cudaDevAttrMaxBlockDimZ);
	Attr(cudaDevAttrMaxGridDimX);
	Attr(cudaDevAttrMaxGridDimY);
	Attr(cudaDevAttrMaxGridDimZ);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxPersistingL2CacheSize);
#endif
	Attr(cudaDevAttrMaxPitch);
	Attr(cudaDevAttrMaxRegistersPerBlock);
	Attr(cudaDevAttrMaxRegistersPerMultiprocessor);
	Attr(cudaDevAttrMaxSharedMemoryPerBlock);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxSharedMemoryPerBlockOptin);
#endif
	Attr(cudaDevAttrMaxSharedMemoryPerMultiprocessor);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxSurface1DLayeredLayers);
	Attr(cudaDevAttrMaxSurface1DLayeredWidth);
	Attr(cudaDevAttrMaxSurface1DWidth);
	Attr(cudaDevAttrMaxSurface2DHeight);
	Attr(cudaDevAttrMaxSurface2DLayeredHeight);
	Attr(cudaDevAttrMaxSurface2DLayeredLayers);
	Attr(cudaDevAttrMaxSurface2DLayeredWidth);
	Attr(cudaDevAttrMaxSurface2DWidth);
	Attr(cudaDevAttrMaxSurface3DDepth);
	Attr(cudaDevAttrMaxSurface3DHeight);
	Attr(cudaDevAttrMaxSurface3DWidth);
	Attr(cudaDevAttrMaxSurfaceCubemapLayeredLayers);
	Attr(cudaDevAttrMaxSurfaceCubemapLayeredWidth);
	Attr(cudaDevAttrMaxSurfaceCubemapWidth);
	Attr(cudaDevAttrMaxTexture1DLayeredLayers);
	Attr(cudaDevAttrMaxTexture1DLayeredWidth);
#endif
	Attr(cudaDevAttrMaxTexture1DWidth);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture2DGatherHeight);
	Attr(cudaDevAttrMaxTexture2DGatherWidth);
#endif
	Attr(cudaDevAttrMaxTexture2DHeight);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture2DLayeredHeight);
	Attr(cudaDevAttrMaxTexture2DLayeredLayers);
	Attr(cudaDevAttrMaxTexture2DLayeredWidth);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture2DMipmappedHeight);
	Attr(cudaDevAttrMaxTexture2DMipmappedWidth);
#endif
	Attr(cudaDevAttrMaxTexture2DWidth);
	Attr(cudaDevAttrMaxTexture3DDepth);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture3DDepthAlt);
#endif
	Attr(cudaDevAttrMaxTexture3DHeight);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture3DHeightAlt);
#endif
	Attr(cudaDevAttrMaxTexture3DWidth);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMaxTexture3DWidthAlt);
	Attr(cudaDevAttrMaxTextureCubemapLayeredLayers);
	Attr(cudaDevAttrMaxTextureCubemapLayeredWidth);
	Attr(cudaDevAttrMaxTextureCubemapWidth);
#endif
#if !defined(__NVCC__)
	Attr(cudaDevAttrMemoryBusWidth);
#endif
	Attr(cudaDevAttrMemoryClockRate);
	Attr(cudaDevAttrMemoryPoolsSupported);
	Attr(cudaDevAttrMemoryPoolSupportedHandleTypes);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMemSyncDomainCount);
#endif
#if !defined(__HIPCC__) && (defined(__NVCC__) && CUDA_VERSION > 12020)
	Attr(cudaDevAttrMpsEnabled);
#endif
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrMulticastSupported);
#endif
	Attr(cudaDevAttrMultiGpuBoardGroupID);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrMultiProcessorCount);
	Attr(cudaDevAttrNumaConfig);
	Attr(cudaDevAttrNumaId);
#endif
	Attr(cudaDevAttrPageableMemoryAccess);
	Attr(cudaDevAttrPageableMemoryAccessUsesHostPageTables);
	Attr(cudaDevAttrPciBusId);
	Attr(cudaDevAttrPciDeviceId);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrPciDomainId);
#endif
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrPeerSocketId);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrReservedSharedMemoryPerBlock);
#endif
	Attr(cudaDevAttrSingleToDoublePrecisionPerfRatio);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrSocketId);
#endif
#if !defined(__HIPCC__)
	Attr(cudaDevAttrSparseCudaArraySupported);
#endif
	Attr(cudaDevAttrStreamPrioritiesSupported);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrSurfaceAligement);
#endif
	Attr(cudaDevAttrTccDriver);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrTexture1DLinearWidth);
	Attr(cudaDevAttrTexture2DLinearHeight);
	Attr(cudaDevAttrTexture2DLinearPitch);
	Attr(cudaDevAttrTexture2DLinearWidth);
#endif
	Attr(cudaDevAttrTextureAlignment);
	Attr(cudaDevAttrTexturePitchAlignment);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrTimelineSemaphoreInteropSupported);
#endif
	Attr(cudaDevAttrTotalConstantMemory);
	Attr(cudaDevAttrUnifiedAddressing);
#if !defined(__NVCC__)
	Attr(cudaDevAttrVirtualMemoryManagementSupported);
#endif
	Attr(cudaDevAttrWarpSize);
#if !defined(__NVCC__) && !defined(__HIPCC__)
	Attr(cudaDevAttrWaveSize);
#endif

	return 0;
}
