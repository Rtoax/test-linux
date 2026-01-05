#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	int value, dev_id;

	dev_id = 0;

	gpu_init(dev_id);

#define Attr(attr) do {	\
		cudaDeviceGetAttribute(&value, attr, dev_id);	\
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
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrAsicRevision);
#endif
	Attr(cudaDevAttrAsyncEngineCount);
	Attr(cudaDevAttrCanFlushRemoteWrites);
	Attr(cudaDevAttrCanMapHostMemory);
	Attr(cudaDevAttrCanUseHostPointerForRegisteredMem);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrCanUseStreamMemOps);
	Attr(cudaDevAttrCanUseStreamWaitValue);
	Attr(cudaDevAttrCanUseStreamWaitWaitValueNor);
#endif
	Attr(cudaDevAttrClusterLaunch);
	Attr(cudaDevAttrComputeCapabilityMajor);
	Attr(cudaDevAttrComputeCapabilityMinor);
	Attr(cudaDevAttrComputeMode);
	Attr(cudaDevAttrComputePreemptionSupported);
	Attr(cudaDevAttrConcurrentKernels);
	Attr(cudaDevAttrConcurrentManagedAccess);
	Attr(cudaDevAttrCooperativeLaunch);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrCooperativeMultiDeviceLaunch);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedFunc);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem);
#endif
	Attr(cudaDevAttrDeferredMappingCudaArraySupported);
	Attr(cudaDevAttrDirectManagedMemAccessFromHost);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrGenericCompressionSupported);
#endif
	Attr(cudaDevAttrGlobalL1CacheSupported);
	Attr(cudaDevAttrGPUDirectRDMAFlushWritesOptions);
	Attr(cudaDevAttrGPUDirectRDMASupported);
	Attr(cudaDevAttrGPUDirectRDMAWritesOrdering);
	Attr(cudaDevAttrGpuOverlap);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrHandleTypePosixFileDescriptorSupported);
	Attr(cudaDevAttrHandleTypeWin32HandleSupported);
	Attr(cudaDevAttrHdpMemFlushCntl);
	Attr(cudaDevAttrHdpRegFlushCntl);
#endif
	Attr(cudaDevAttrHostNativeAtomicSupported);
	Attr(cudaDevAttrHostRegisterReadOnlySupported);
	Attr(cudaDevAttrHostRegisterSupported);
	Attr(cudaDevAttrIntegrated);
	Attr(cudaDevAttrIpcEventSupport);
	Attr(cudaDevAttrIsMultiGpuBoard);
	Attr(cudaDevAttrKernelExecTimeout);
	Attr(cudaDevAttrLocalL1CacheSupported);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrLocalSocketId);
#endif
	Attr(cudaDevAttrMaxAccessPolicyWindowSize);
	Attr(cudaDevAttrMaxBlockDimX);
	Attr(cudaDevAttrMaxBlockDimY);
	Attr(cudaDevAttrMaxBlockDimZ);
	Attr(cudaDevAttrMaxGridDimX);
	Attr(cudaDevAttrMaxGridDimY);
	Attr(cudaDevAttrMaxGridDimZ);
	Attr(cudaDevAttrMaxPersistingL2CacheSize);
	Attr(cudaDevAttrMaxPitch);
	Attr(cudaDevAttrMaxRegistersPerBlock);
	Attr(cudaDevAttrMaxRegistersPerMultiprocessor);
	Attr(cudaDevAttrMaxSharedMemoryPerBlock);
	Attr(cudaDevAttrMaxSharedMemoryPerBlockOptin);
	Attr(cudaDevAttrMaxSharedMemoryPerMultiprocessor);
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
	Attr(cudaDevAttrMaxTexture1DWidth);
	Attr(cudaDevAttrMaxTexture2DGatherHeight);
	Attr(cudaDevAttrMaxTexture2DGatherWidth);
	Attr(cudaDevAttrMaxTexture2DHeight);
	Attr(cudaDevAttrMaxTexture2DLayeredHeight);
	Attr(cudaDevAttrMaxTexture2DLayeredLayers);
	Attr(cudaDevAttrMaxTexture2DLayeredWidth);
	Attr(cudaDevAttrMaxTexture2DMipmappedHeight);
	Attr(cudaDevAttrMaxTexture2DMipmappedWidth);
	Attr(cudaDevAttrMaxTexture2DWidth);
	Attr(cudaDevAttrMaxTexture3DDepth);
	Attr(cudaDevAttrMaxTexture3DDepthAlt);
	Attr(cudaDevAttrMaxTexture3DHeight);
	Attr(cudaDevAttrMaxTexture3DHeightAlt);
	Attr(cudaDevAttrMaxTexture3DWidth);
	Attr(cudaDevAttrMaxTexture3DWidthAlt);
	Attr(cudaDevAttrMaxTextureCubemapLayeredLayers);
	Attr(cudaDevAttrMaxTextureCubemapLayeredWidth);
	Attr(cudaDevAttrMaxTextureCubemapWidth);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrMemoryBusWidth);
#endif
	Attr(cudaDevAttrMemoryClockRate);
	Attr(cudaDevAttrMemoryPoolsSupported);
	Attr(cudaDevAttrMemoryPoolSupportedHandleTypes);
	Attr(cudaDevAttrMemSyncDomainCount);
	Attr(cudaDevAttrMpsEnabled);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrMulticastSupported);
#endif
	Attr(cudaDevAttrMultiGpuBoardGroupID);
	Attr(cudaDevAttrMultiProcessorCount);
	Attr(cudaDevAttrNumaConfig);
	Attr(cudaDevAttrNumaId);
	Attr(cudaDevAttrPageableMemoryAccess);
	Attr(cudaDevAttrPageableMemoryAccessUsesHostPageTables);
	Attr(cudaDevAttrPciBusId);
	Attr(cudaDevAttrPciDeviceId);
	Attr(cudaDevAttrPciDomainId);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrPeerSocketId);
#endif
	Attr(cudaDevAttrReservedSharedMemoryPerBlock);
	Attr(cudaDevAttrSingleToDoublePrecisionPerfRatio);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrSocketId);
#endif
	Attr(cudaDevAttrSparseCudaArraySupported);
	Attr(cudaDevAttrStreamPrioritiesSupported);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrSurfaceAligement);
#endif
	Attr(cudaDevAttrTccDriver);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrTexture1DLinearWidth);
	Attr(cudaDevAttrTexture2DLinearHeight);
	Attr(cudaDevAttrTexture2DLinearPitch);
	Attr(cudaDevAttrTexture2DLinearWidth);
#endif
	Attr(cudaDevAttrTextureAlignment);
	Attr(cudaDevAttrTexturePitchAlignment);
	Attr(cudaDevAttrTimelineSemaphoreInteropSupported);
	Attr(cudaDevAttrTotalConstantMemory);
	Attr(cudaDevAttrUnifiedAddressing);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrVirtualMemoryManagementSupported);
#endif
	Attr(cudaDevAttrWarpSize);
#if !defined(__NVCC__) || (CUDA_VERSION != 13000)
	Attr(cudaDevAttrWaveSize);
#endif

	return 0;
}
