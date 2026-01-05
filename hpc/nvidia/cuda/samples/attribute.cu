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
	Attr(cudaDevAttrAsicRevision);
	Attr(cudaDevAttrAsyncEngineCount);
	Attr(cudaDevAttrCanFlushRemoteWrites);
	Attr(cudaDevAttrCanMapHostMemory);
	Attr(cudaDevAttrCanUseHostPointerForRegisteredMem);
	Attr(cudaDevAttrCanUseStreamMemOps);
	Attr(cudaDevAttrCanUseStreamWaitValue);
	Attr(cudaDevAttrCanUseStreamWaitWaitValueNor);
	Attr(cudaDevAttrClusterLaunch);
	Attr(cudaDevAttrComputeCapabilityMajor);
	Attr(cudaDevAttrComputeCapabilityMinor);
	Attr(cudaDevAttrComputeMode);
	Attr(cudaDevAttrComputePreemptionSupported);
	Attr(cudaDevAttrConcurrentKernels);
	Attr(cudaDevAttrConcurrentManagedAccess);
	Attr(cudaDevAttrCooperativeLaunch);
	Attr(cudaDevAttrCooperativeMultiDeviceLaunch);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedFunc);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim);
	Attr(cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem);
#if !defined(__LUCA__)
	Attr(cudaDevAttrDeferredMappingHpccArraySupported);
#endif
	Attr(cudaDevAttrDirectManagedMemAccessFromHost);
	Attr(cudaDevAttrGenericCompressionSupported);
	Attr(cudaDevAttrGlobalL1CacheSupported);
	Attr(cudaDevAttrGPUDirectRDMAFlushWritesOptions);
	Attr(cudaDevAttrGPUDirectRDMASupported);
	Attr(cudaDevAttrGPUDirectRDMAWritesOrdering);
	Attr(cudaDevAttrGpuOverlap);
	Attr(cudaDevAttrHandleTypePosixFileDescriptorSupported);
	Attr(cudaDevAttrHandleTypeWin32HandleSupported);
	Attr(cudaDevAttrHdpMemFlushCntl);
	Attr(cudaDevAttrHdpRegFlushCntl);
	Attr(cudaDevAttrHostNativeAtomicSupported);
	Attr(cudaDevAttrHostRegisterReadOnlySupported);
	Attr(cudaDevAttrHostRegisterSupported);
	Attr(cudaDevAttrIntegrated);
	Attr(cudaDevAttrIpcEventSupport);
	Attr(cudaDevAttrIsMultiGpuBoard);
	Attr(cudaDevAttrKernelExecTimeout);
	Attr(cudaDevAttrLocalL1CacheSupported);
	Attr(cudaDevAttrLocalSocketId);
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
	Attr(cudaDevAttrMemoryBusWidth);
	Attr(cudaDevAttrMemoryClockRate);
	Attr(cudaDevAttrMemoryPoolsSupported);
	Attr(cudaDevAttrMemoryPoolSupportedHandleTypes);
	Attr(cudaDevAttrMemSyncDomainCount);
	Attr(cudaDevAttrMpsEnabled);
	Attr(cudaDevAttrMulticastSupported);
	Attr(cudaDevAttrMultiGpuBoardGroupID);
	Attr(cudaDevAttrMultiProcessorCount);
	Attr(cudaDevAttrNumaConfig);
	Attr(cudaDevAttrNumaId);
	Attr(cudaDevAttrPageableMemoryAccess);
	Attr(cudaDevAttrPageableMemoryAccessUsesHostPageTables);
	Attr(cudaDevAttrPciBusId);
	Attr(cudaDevAttrPciDeviceId);
	Attr(cudaDevAttrPciDomainId);
	Attr(cudaDevAttrPeerSocketId);
	Attr(cudaDevAttrReserved102);
	Attr(cudaDevAttrReserved103);
	Attr(cudaDevAttrReserved104);
	Attr(cudaDevAttrReserved105);
	Attr(cudaDevAttrReserved107);
	Attr(cudaDevAttrReserved110);
	Attr(cudaDevAttrReserved122);
	Attr(cudaDevAttrReserved123);
	Attr(cudaDevAttrReserved124);
	Attr(cudaDevAttrReserved127);
	Attr(cudaDevAttrReserved128);
	Attr(cudaDevAttrReserved129);
	Attr(cudaDevAttrReserved132);
	Attr(cudaDevAttrReserved92);
	Attr(cudaDevAttrReserved93);
	Attr(cudaDevAttrReserved94);
	Attr(cudaDevAttrReservedSharedMemoryPerBlock);
	Attr(cudaDevAttrResvered44);
	Attr(cudaDevAttrSingleToDoublePrecisionPerfRatio);
	Attr(cudaDevAttrSocketId);
#if !defined(__LUCA__)
	Attr(cudaDevAttrSparseHpccArraySupported);
#endif
	Attr(cudaDevAttrStreamPrioritiesSupported);
	Attr(cudaDevAttrSurfaceAligement);
	Attr(cudaDevAttrTccDriver);
	Attr(cudaDevAttrTexture1DLinearWidth);
	Attr(cudaDevAttrTexture2DLinearHeight);
	Attr(cudaDevAttrTexture2DLinearPitch);
	Attr(cudaDevAttrTexture2DLinearWidth);
	Attr(cudaDevAttrTextureAlignment);
	Attr(cudaDevAttrTexturePitchAlignment);
	Attr(cudaDevAttrTimelineSemaphoreInteropSupported);
	Attr(cudaDevAttrTotalConstantMemory);
	Attr(cudaDevAttrUnifiedAddressing);
	Attr(cudaDevAttrVirtualMemoryManagementSupported);
	Attr(cudaDevAttrWarpSize);
	Attr(cudaDevAttrWaveSize);

	return 0;
}
