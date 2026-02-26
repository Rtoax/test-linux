// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_DRIVER_TYPES_H
#define __CUDA_ADAPTER_DRIVER_TYPES_H 1

#include "wrapper_defs.h"

/**
 * typedef __device_builtin__ enum cudaError cudaError_t
 */
#define cudaError_t cudaX(Error_t)
#define cudaSuccess cudaX(Success)
#define cudaErrorInvalidValue cudaX(ErrorInvalidValue)
#define cudaErrorMemoryAllocation cudaX(ErrorMemoryAllocation)
#define cudaErrorInitializationError cudaX(ErrorInitializationError)
#define cudaErrorCudartUnloading cudaX(ErrorCudartUnloading)
#define cudaErrorProfilerDisabled cudaX(ErrorProfilerDisabled)
#define cudaErrorProfilerNotInitialized cudaX(ErrorProfilerNotInitialized)
#define cudaErrorProfilerAlreadyStarted cudaX(ErrorProfilerAlreadyStarted)
#define cudaErrorProfilerAlreadyStopped cudaX(ErrorProfilerAlreadyStopped)
#define cudaErrorInvalidConfiguration cudaX(ErrorInvalidConfiguration)
#define cudaErrorInvalidPitchValue cudaX(ErrorInvalidPitchValue)
#define cudaErrorInvalidSymbol cudaX(ErrorInvalidSymbol)
#define cudaErrorInvalidHostPointer cudaX(ErrorInvalidHostPointer)
#define cudaErrorInvalidDevicePointer cudaX(ErrorInvalidDevicePointer)
#define cudaErrorInvalidTexture cudaX(ErrorInvalidTexture)
#define cudaErrorInvalidTextureBinding cudaX(ErrorInvalidTextureBinding)
#define cudaErrorInvalidChannelDescriptor cudaX(ErrorInvalidChannelDescriptor)
#define cudaErrorInvalidMemcpyDirection cudaX(ErrorInvalidMemcpyDirection)
#define cudaErrorAddressOfConstant cudaX(ErrorAddressOfConstant)
#define cudaErrorTextureFetchFailed cudaX(ErrorTextureFetchFailed)
#define cudaErrorTextureNotBound cudaX(ErrorTextureNotBound)
#define cudaErrorSynchronizationError cudaX(ErrorSynchronizationError)
#define cudaErrorInvalidFilterSetting cudaX(ErrorInvalidFilterSetting)
#define cudaErrorInvalidNormSetting cudaX(ErrorInvalidNormSetting)
#define cudaErrorMixedDeviceExecution cudaX(ErrorMixedDeviceExecution)
#define cudaErrorNotYetImplemented cudaX(ErrorNotYetImplemented)
#define cudaErrorMemoryValueTooLarge cudaX(ErrorMemoryValueTooLarge)
#define cudaErrorStubLibrary cudaX(ErrorStubLibrary)
#define cudaErrorInsufficientDriver cudaX(ErrorInsufficientDriver)
#define cudaErrorCallRequiresNewerDriver cudaX(ErrorCallRequiresNewerDriver)
#define cudaErrorInvalidSurface cudaX(ErrorInvalidSurface)
#define cudaErrorDuplicateVariableName cudaX(ErrorDuplicateVariableName)
#define cudaErrorDuplicateTextureName cudaX(ErrorDuplicateTextureName)
#define cudaErrorDuplicateSurfaceName cudaX(ErrorDuplicateSurfaceName)
#define cudaErrorDevicesUnavailable cudaX(ErrorDevicesUnavailable)
#define cudaErrorIncompatibleDriverContext \
	cudaX(ErrorIncompatibleDriverContext)
#define cudaErrorMissingConfiguration cudaX(ErrorMissingConfiguration)
#define cudaErrorPriorLaunchFailure cudaX(ErrorPriorLaunchFailure)
#define cudaErrorLaunchMaxDepthExceeded cudaX(ErrorLaunchMaxDepthExceeded)
#define cudaErrorLaunchFileScopedTex cudaX(ErrorLaunchFileScopedTex)
#define cudaErrorLaunchFileScopedSurf cudaX(ErrorLaunchFileScopedSurf)
#define cudaErrorSyncDepthExceeded cudaX(ErrorSyncDepthExceeded)
#define cudaErrorLaunchPendingCountExceeded \
	cudaX(ErrorLaunchPendingCountExceeded)
#define cudaErrorInvalidDeviceFunction cudaX(ErrorInvalidDeviceFunction)
#define cudaErrorNoDevice cudaX(ErrorNoDevice)
#define cudaErrorInvalidDevice cudaX(ErrorInvalidDevice)
#define cudaErrorDeviceNotLicensed cudaX(ErrorDeviceNotLicensed)
#define cudaErrorSoftwareValidityNotEstablished \
	cudaX(ErrorSoftwareValidityNotEstablished)
#define cudaErrorStartupFailure cudaX(ErrorStartupFailure)
#define cudaErrorInvalidKernelImage cudaX(ErrorInvalidKernelImage)
#define cudaErrorDeviceUninitialized cudaX(ErrorDeviceUninitialized)
#define cudaErrorMapBufferObjectFailed cudaX(ErrorMapBufferObjectFailed)
#define cudaErrorUnmapBufferObjectFailed cudaX(ErrorUnmapBufferObjectFailed)
#define cudaErrorArrayIsMapped cudaX(ErrorArrayIsMapped)
#define cudaErrorAlreadyMapped cudaX(ErrorAlreadyMapped)
#define cudaErrorNoKernelImageForDevice cudaX(ErrorNoKernelImageForDevice)
#define cudaErrorAlreadyAcquired cudaX(ErrorAlreadyAcquired)
#define cudaErrorNotMapped cudaX(ErrorNotMapped)
#define cudaErrorNotMappedAsArray cudaX(ErrorNotMappedAsArray)
#define cudaErrorNotMappedAsPointer cudaX(ErrorNotMappedAsPointer)
#define cudaErrorECCUncorrectable cudaX(ErrorECCUncorrectable)
#define cudaErrorUnsupportedLimit cudaX(ErrorUnsupportedLimit)
#define cudaErrorDeviceAlreadyInUse cudaX(ErrorDeviceAlreadyInUse)
#define cudaErrorPeerAccessUnsupported cudaX(ErrorPeerAccessUnsupported)
#define cudaErrorInvalidPtx cudaX(ErrorInvalidPtx)
#define cudaErrorInvalidGraphicsContext cudaX(ErrorInvalidGraphicsContext)
#define cudaErrorNvlinkUncorrectable cudaX(ErrorNvlinkUncorrectable)
#define cudaErrorJitCompilerNotFound cudaX(ErrorJitCompilerNotFound)
#define cudaErrorUnsupportedPtxVersion cudaX(ErrorUnsupportedPtxVersion)
#define cudaErrorJitCompilationDisabled cudaX(ErrorJitCompilationDisabled)
#define cudaErrorUnsupportedExecAffinity cudaX(ErrorUnsupportedExecAffinity)
#define cudaErrorUnsupportedDevSideSync cudaX(ErrorUnsupportedDevSideSync)
#define cudaErrorContained cudaX(ErrorContained)
#define cudaErrorInvalidSource cudaX(ErrorInvalidSource)
#define cudaErrorFileNotFound cudaX(ErrorFileNotFound)
#define cudaErrorSharedObjectSymbolNotFound \
	cudaX(ErrorSharedObjectSymbolNotFound)
#define cudaErrorSharedObjectInitFailed cudaX(ErrorSharedObjectInitFailed)
#define cudaErrorOperatingSystem cudaX(ErrorOperatingSystem)
#define cudaErrorInvalidResourceHandle cudaX(ErrorInvalidResourceHandle)
#define cudaErrorIllegalState cudaX(ErrorIllegalState)
#define cudaErrorLossyQuery cudaX(ErrorLossyQuery)
#define cudaErrorSymbolNotFound cudaX(ErrorSymbolNotFound)
#define cudaErrorNotReady cudaX(ErrorNotReady)
#define cudaErrorIllegalAddress cudaX(ErrorIllegalAddress)
#define cudaErrorLaunchOutOfResources cudaX(ErrorLaunchOutOfResources)
#define cudaErrorLaunchTimeout cudaX(ErrorLaunchTimeout)
#define cudaErrorLaunchIncompatibleTexturing \
	cudaX(ErrorLaunchIncompatibleTexturing)
#define cudaErrorPeerAccessAlreadyEnabled cudaX(ErrorPeerAccessAlreadyEnabled)
#define cudaErrorPeerAccessNotEnabled cudaX(ErrorPeerAccessNotEnabled)
#define cudaErrorSetOnActiveProcess cudaX(ErrorSetOnActiveProcess)
#define cudaErrorContextIsDestroyed cudaX(ErrorContextIsDestroyed)
#define cudaErrorAssert cudaX(ErrorAssert)
#define cudaErrorTooManyPeers cudaX(ErrorTooManyPeers)
#define cudaErrorHostMemoryAlreadyRegistered \
	cudaX(ErrorHostMemoryAlreadyRegistered)
#define cudaErrorHostMemoryNotRegistered cudaX(ErrorHostMemoryNotRegistered)
#define cudaErrorHardwareStackError cudaX(ErrorHardwareStackError)
#define cudaErrorIllegalInstruction cudaX(ErrorIllegalInstruction)
#define cudaErrorMisalignedAddress cudaX(ErrorMisalignedAddress)
#define cudaErrorInvalidAddressSpace cudaX(ErrorInvalidAddressSpace)
#define cudaErrorInvalidPc cudaX(ErrorInvalidPc)
#define cudaErrorLaunchFailure cudaX(ErrorLaunchFailure)
#define cudaErrorCooperativeLaunchTooLarge \
	cudaX(ErrorCooperativeLaunchTooLarge)
#define cudaErrorTensorMemoryLeak cudaX(ErrorTensorMemoryLeak)
#define cudaErrorNotPermitted cudaX(ErrorNotPermitted)
#define cudaErrorNotSupported cudaX(ErrorNotSupported)
#define cudaErrorSystemNotReady cudaX(ErrorSystemNotReady)
#define cudaErrorSystemDriverMismatch cudaX(ErrorSystemDriverMismatch)
#define cudaErrorCompatNotSupportedOnDevice \
	cudaX(ErrorCompatNotSupportedOnDevice)
#define cudaErrorMpsConnectionFailed cudaX(ErrorMpsConnectionFailed)
#define cudaErrorMpsRpcFailure cudaX(ErrorMpsRpcFailure)
#define cudaErrorMpsServerNotReady cudaX(ErrorMpsServerNotReady)
#define cudaErrorMpsMaxClientsReached cudaX(ErrorMpsMaxClientsReached)
#define cudaErrorMpsMaxConnectionsReached cudaX(ErrorMpsMaxConnectionsReached)
#define cudaErrorMpsClientTerminated cudaX(ErrorMpsClientTerminated)
#define cudaErrorCdpNotSupported cudaX(ErrorCdpNotSupported)
#define cudaErrorCdpVersionMismatch cudaX(ErrorCdpVersionMismatch)
#define cudaErrorStreamCaptureUnsupported cudaX(ErrorStreamCaptureUnsupported)
#define cudaErrorStreamCaptureInvalidated cudaX(ErrorStreamCaptureInvalidated)
#define cudaErrorStreamCaptureMerge cudaX(ErrorStreamCaptureMerge)
#define cudaErrorStreamCaptureUnmatched cudaX(ErrorStreamCaptureUnmatched)
#define cudaErrorStreamCaptureUnjoined cudaX(ErrorStreamCaptureUnjoined)
#define cudaErrorStreamCaptureIsolation cudaX(ErrorStreamCaptureIsolation)
#define cudaErrorStreamCaptureImplicit cudaX(ErrorStreamCaptureImplicit)
#define cudaErrorCapturedEvent cudaX(ErrorCapturedEvent)
#define cudaErrorStreamCaptureWrongThread cudaX(ErrorStreamCaptureWrongThread)
#define cudaErrorTimeout cudaX(ErrorTimeout)
#define cudaErrorGraphExecUpdateFailure cudaX(ErrorGraphExecUpdateFailure)
#define cudaErrorExternalDevice cudaX(ErrorExternalDevice)
#define cudaErrorInvalidClusterSize cudaX(ErrorInvalidClusterSize)
#define cudaErrorFunctionNotLoaded cudaX(ErrorFunctionNotLoaded)
#define cudaErrorInvalidResourceType cudaX(ErrorInvalidResourceType)
#define cudaErrorInvalidResourceConfiguration \
	cudaX(ErrorInvalidResourceConfiguration)
#define cudaErrorUnknown cudaX(ErrorUnknown)
#define cudaErrorApiFailureBase cudaX(ErrorApiFailureBase)

/**
 * CUDA: struct __device_builtin__ cudaDeviceProp {...};
 * HIP: typedef struct hipDeviceProp_t {...} hipDeviceProp_t;
 * LUCA: typedef struct _lcDeviceProp_t {...} lcDeviceProp_t;
 */
#define cudaDeviceProp cudaX(DeviceProp_t)

#define cudaMemcpyKind cudaX(MemcpyKind) /* enum */
#define cudaMemcpyHostToHost cudaX(MemcpyHostToHost) /* 0 */
#define cudaMemcpyHostToDevice cudaX(MemcpyHostToDevice) /* 1 */
#define cudaMemcpyDeviceToHost cudaX(MemcpyDeviceToHost) /* 2 */
#define cudaMemcpyDeviceToDevice cudaX(MemcpyDeviceToDevice) /* 3 */
#define cudaMemcpyDefault cudaX(MemcpyDefault) /* 4 */

/* cudaMallocManaged::flags */
#define cudaMemAttachGlobal cudaX(MemAttachGlobal)
#define cudaMemAttachHost cudaX(MemAttachHost)
#define cudaMemAttachSingle cudaX(MemAttachSingle)

#define cudaLimit cudaX(Limit_t)
#define cudaLimitStackSize cudaX(LimitStackSize)
#define cudaLimitPrintfFifoSize cudaX(LimitPrintfFifoSize)
#define cudaLimitMallocHeapSize cudaX(LimitMallocHeapSize)
#define cudaLimitDevRuntimeSyncDepth cudaX(LimitDevRuntimeSyncDepth)
#define cudaLimitDevRuntimePendingLaunchCount \
	cudaX(LimitDevRuntimePendingLaunchCount)
#define cudaLimitMaxL2FetchGranularity cudaX(LimitMaxL2FetchGranularity)
#define cudaLimitPersistingL2CacheSize cudaX(LimitPersistingL2CacheSize)

/**
 * CUDA: typedef const struct cudaArray *cudaArray_const_t;
 * HIP: typedef const struct hipArray* hipArray_const_t;
 */
#define cudaArray_const_t cudaX(Array_const_t)

#if defined(__USE_HIP__)
#define cudaMemoryAdvise cudaX(MemoryAdvise) /* enum */
#elif defined(__USE_LUCA__) || defined(__USE_HPCC__)
#define cudaMemoryAdvise cudaX(MemoryAdvise_t) /* enum */
#endif
#define cudaMemAdviseSetReadMostly cudaX(MemAdviseSetReadMostly)
#define cudaMemAdviseUnsetReadMostly cudaX(MemAdviseUnsetReadMostly)
#define cudaMemAdviseSetPreferredLocation cudaX(MemAdviseSetPreferredLocation)
#define cudaMemAdviseUnsetPreferredLocation \
	cudaX(MemAdviseUnsetPreferredLocation)
#define cudaMemAdviseSetAccessedBy cudaX(MemAdviseSetAccessedBy)
#define cudaMemAdviseUnsetAccessedBy cudaX(MemAdviseUnsetAccessedBy)

#define cudaMemLocation cudaX(MemLocation) /* struct */
#define cudaMemLocationType cudaX(MemLocationType) /* enum */
#define cudaMemLocationTypeInvalid cudaX(MemLocationTypeInvalid)
#define cudaMemLocationTypeNone cudaX(MemLocationTypeNone)
#define cudaMemLocationTypeDevice cudaX(MemLocationTypeDevice)
#define cudaMemLocationTypeHost cudaX(MemLocationTypeHost)
#define cudaMemLocationTypeHostNuma cudaX(MemLocationTypeHostNuma)
#define cudaMemLocationTypeHostNumaCurrent \
	cudaX(MemLocationTypeHostNumaCurrent)

/**
 * CUDA: typedef __device_builtin__ struct CUmemPoolHandle_st *cudaMemPool_t;
 */
#define cudaMemPool_t cudaX(MemPool_t)

#define cudaMemPoolProps cudaX(MemPoolProps) /* struct */

#if defined(__USE_HIP__) || defined(__USE_LUCA__) || defined(__USE_HPCC__)
#define cudaPointerAttributes cudaX(PointerAttribute_t)
#else
#define cudaPointerAttributes cudaX(PointerAttributes)
#endif

/**
 * CUDA:
 * driver_types.h: typedef __device_builtin__ struct CUevent_st *cudaEvent_t;
 *
 * ROCm HIP:
 * hip/hip_runtime_api.h: typedef struct ihipEvent_t* hipEvent_t;
 * Orochi/nvidia_hip_runtime_api_oro.h: typedef cudaEvent_t hipEvent_t;
 * Orochi/hipew.h: typedef struct ihipEvent_t * hipEvent_t;
 */
#define cudaEvent_t cudaX(Event_t)

/**
 * CUDA: typedef __device_builtin__ struct CUgraph_st *cudaGraph_t;
 */
#define cudaGraph_t cudaX(Graph_t)

/**
 * CUDA: typedef __device_builtin__ struct CUgraphNode_st *cudaGraphNode_t;
 */
#define cudaGraphNode_t cudaX(GraphNode_t)

/**
 * CUDA: typedef struct CUgraphExec_st* cudaGraphExec_t;
 */
#define cudaGraphExec_t cudaX(GraphExec_t)

/**
 * CUDA: typedef struct cudaGraphEdgeData_st { ... } cudaGraphEdgeData;
 */
#define cudaGraphEdgeData cudaX(GraphEdgeData)

/**
 * CUDA: struct __device_builtin__ cudaFuncAttributes { ... };
 */
#define cudaFuncAttributes cudaX(FuncAttributes)

/**
 * CUDA: enum __device_builtin__ cudaFuncAttribute { ... };
 */
#define cudaFuncAttribute cudaX(FuncAttribute)
#define cudaFuncAttributeMaxDynamicSharedMemorySize \
	cudaX(FuncAttributeMaxDynamicSharedMemorySize)
#define cudaFuncAttributePreferredSharedMemoryCarveout \
	cudaX(FuncAttributePreferredSharedMemoryCarveout)
#define cudaFuncAttributeClusterDimMustBeSet \
	cudaX(FuncAttributeClusterDimMustBeSet)
#define cudaFuncAttributeRequiredClusterWidth \
	cudaX(FuncAttributeRequiredClusterWidth)
#define cudaFuncAttributeRequiredClusterHeight \
	cudaX(FuncAttributeRequiredClusterHeight)
#define cudaFuncAttributeRequiredClusterDepth \
	cudaX(FuncAttributeRequiredClusterDepth)
#define cudaFuncAttributeNonPortableClusterSizeAllowed \
	cudaX(FuncAttributeNonPortableClusterSizeAllowed)
#define cudaFuncAttributeClusterSchedulingPolicyPreference \
	cudaX(FuncAttributeClusterSchedulingPolicyPreference)
#define cudaFuncAttributeMax cudaX(FuncAttributeMax)

/**
 * cudaStreamCreateWithFlags()::flags
 */
#define cudaStreamDefault cudaX(StreamDefault) /* 0x00 */
#define cudaStreamNonBlocking cudaX(StreamNonBlocking) /* 0x01 */

/**
 * #define cudaStreamAttrID cudaLaunchAttributeID
 */
#define cudaStreamAttrID cudaX(StreamAttrID)
#define cudaStreamAttributeAccessPolicyWindow \
	cudaX(StreamAttributeAccessPolicyWindow)
#define cudaStreamAttributeSynchronizationPolicy \
	cudaX(StreamAttributeSynchronizationPolicy)
#define cudaStreamAttributeMemSyncDomainMap \
	cudaX(StreamAttributeMemSyncDomainMap)
#define cudaStreamAttributeMemSyncDomain cudaX(StreamAttributeMemSyncDomain)
#define cudaStreamAttributePriority cudaX(StreamAttributePriority)

/**
 * enum cudaStreamCaptureStatus {...};
 */
#define cudaStreamCaptureStatus cudaX(StreamCaptureStatus)
#define cudaStreamCaptureStatusNone cudaX(StreamCaptureStatusNone)
#define cudaStreamCaptureStatusActive cudaX(StreamCaptureStatusActive)
#define cudaStreamCaptureStatusInvalidated \
	cudaX(StreamCaptureStatusInvalidated)

/**
 * enum cudaStreamCaptureMode {...};
 */
#define cudaStreamCaptureMode cudaX(StreamCaptureMode)
#define cudaStreamCaptureModeGlobal cudaX(StreamCaptureModeGlobal) /* 0 */
#define cudaStreamCaptureModeThreadLocal cudaX(StreamCaptureModeThreadLocal)
#define cudaStreamCaptureModeRelaxed cudaX(StreamCaptureModeRelaxed)

/**
 * struct cudaMemAllocNodeParams {...};
 */
#define cudaMemAllocNodeParams cudaX(MemAllocNodeParams)

/**
 * struct cudaMemAllocNodeParamsV2 {...};
 */
#define cudaMemAllocNodeParamsV2 cudaX(MemAllocNodeParamsV2)

#define cudaMemAllocationType cudaX(MemAllocationType) /* enum */
#define cudaMemAllocationTypeInvalid cudaX(MemAllocationTypeInvalid) /* 0 */
#define cudaMemAllocationTypePinned cudaX(MemAllocationTypePinned) /* 1 */
#define cudaMemAllocationTypeManaged cudaX(MemAllocationTypeManaged) /* 2 */
#define cudaMemAllocationTypeMax cudaX(MemAllocationTypeMax) /* 0x7FFFFFFF */

/**
 * typedef __device_builtin__ struct CUuserObject_st *cudaUserObject_t;
 */
#define cudaUserObject_t cudaX(UserObject_t)
#define cudaUserObjectFlags cudaX(UserObjectFlags) /* enum */
#define cudaUserObjectNoDestructorSync cudaX(UserObjectNoDestructorSync)

/* typedef void (*cudaHostFn_t)(void *userData); */
#define cudaHostFn_t cudaX(HostFn_t)

#define cudaHostNodeParams cudaX(HostNodeParams) /* struct */

#define cudaKernelNodeParams cudaX(KernelNodeParams) /* struct */

#define cudaDeviceP2PAttr cudaX(DeviceP2PAttr) /* enum */
#define cudaDevP2PAttrPerformanceRank cudaX(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported cudaX(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported \
	cudaX(DevP2PAttrNativeAtomicSupported)
#ifdef __USE_HPCC__
#define cudaDevP2PAttrCudaArrayAccessSupported \
	hcDevP2PAttrHcArrayAccessSupported
#elif defined(__USE_LUCA__)
#define cudaDevP2PAttrCudaArrayAccessSupported \
	lcDevP2PAttrLcArrayAccessSupported
#elif defined(__USE_HIP__)
#define cudaDevP2PAttrCudaArrayAccessSupported \
	hipDevP2PAttrHipArrayAccessSupported
#endif
#define cudaDevP2PAttrOnlyPartialNativeAtomicSupported \
	cudaX(DevP2PAttrOnlyPartialNativeAtomicSupported)

/**
 * CUDA: typedef struct cudaIpcMemHandle_st {} cudaIpcEventHandle_t;
 */
#define cudaIpcMemHandle_t cudaX(IpcMemHandle_t)

/**
 * CUDA 13.0.0: enum __device_builtin__ cudaDeviceAttr {};
 * HIP: typedef enum hipDeviceAttribute_t {} hipDeviceAttribute_t;
 * LUCA: enum lcDeviceAttribute_t {};
 */
#define cudaDeviceAttr cudaX(DeviceAttribute_t)
#define cudaDevAttrMaxThreadsPerBlock cudaX(DeviceAttributeMaxThreadsPerBlock)
#define cudaDevAttrMaxBlockDimX cudaX(DeviceAttributeMaxBlockDimX)
#define cudaDevAttrMaxBlockDimY cudaX(DeviceAttributeMaxBlockDimY)
#define cudaDevAttrMaxBlockDimZ cudaX(DeviceAttributeMaxBlockDimZ)
#define cudaDevAttrMaxGridDimX cudaX(DeviceAttributeMaxGridDimX)
#define cudaDevAttrMaxGridDimY cudaX(DeviceAttributeMaxGridDimY)
#define cudaDevAttrMaxGridDimZ cudaX(DeviceAttributeMaxGridDimZ)
#define cudaDevAttrMaxSharedMemoryPerBlock \
	cudaX(DeviceAttributeMaxSharedMemoryPerBlock)
#define cudaDevAttrTotalConstantMemory \
	cudaX(DeviceAttributeTotalConstantMemory)
#define cudaDevAttrWarpSize cudaX(DeviceAttributeWarpSize)
#define cudaDevAttrMaxPitch cudaX(DeviceAttributeMaxPitch)
#define cudaDevAttrMaxRegistersPerBlock \
	cudaX(DeviceAttributeMaxRegistersPerBlock)
#define cudaDevAttrClockRate cudaX(DeviceAttributeClockRate)
#define cudaDevAttrTextureAlignment cudaX(DeviceAttributeTextureAlignment)
#define cudaDevAttrGpuOverlap cudaX(DeviceAttributeGpuOverlap)
#define cudaDevAttrMultiProcessorCount \
	cudaX(DeviceAttributeMultiProcessorCount)
#define cudaDevAttrKernelExecTimeout cudaX(DeviceAttributeKernelExecTimeout)
#define cudaDevAttrIntegrated cudaX(DeviceAttributeIntegrated)
#define cudaDevAttrCanMapHostMemory cudaX(DeviceAttributeCanMapHostMemory)
#define cudaDevAttrComputeMode cudaX(DeviceAttributeComputeMode)
#define cudaDevAttrMaxTexture1DWidth cudaX(DeviceAttributeMaxTexture1DWidth)
#define cudaDevAttrMaxTexture2DWidth cudaX(DeviceAttributeMaxTexture2DWidth)
#define cudaDevAttrMaxTexture2DHeight cudaX(DeviceAttributeMaxTexture2DHeight)
#define cudaDevAttrMaxTexture3DWidth cudaX(DeviceAttributeMaxTexture3DWidth)
#define cudaDevAttrMaxTexture3DHeight cudaX(DeviceAttributeMaxTexture3DHeight)
#define cudaDevAttrMaxTexture3DDepth cudaX(DeviceAttributeMaxTexture3DDepth)
#define cudaDevAttrMaxTexture2DLayeredWidth \
	cudaX(DeviceAttributeMaxTexture2DLayeredWidth)
#define cudaDevAttrMaxTexture2DLayeredHeight \
	cudaX(DeviceAttributeMaxTexture2DLayeredHeight)
#define cudaDevAttrMaxTexture2DLayeredLayers \
	cudaX(DeviceAttributeMaxTexture2DLayeredLayers)
#define cudaDevAttrSurfaceAligement cudaX(DeviceAttributeSurfaceAligement)
#define cudaDevAttrConcurrentKernels cudaX(DeviceAttributeConcurrentKernels)
#define cudaDevAttrEccEnabled cudaX(DeviceAttributeEccEnabled)
#define cudaDevAttrPciBusId cudaX(DeviceAttributePciBusId)
#define cudaDevAttrPciDeviceId cudaX(DeviceAttributePciDeviceId)
#define cudaDevAttrTccDriver cudaX(DeviceAttributeTccDriver)
#define cudaDevAttrMemoryClockRate cudaX(DeviceAttributeMemoryClockRate)
#define cudaDevAttrMemoryBusWidth cudaX(DeviceAttributeMemoryBusWidth)
#define cudaDevAttrL2CacheSize cudaX(DeviceAttributeL2CacheSize)
#define cudaDevAttrMaxThreadsPerMultiProcessor \
	cudaX(DeviceAttributeMaxThreadsPerMultiProcessor)
#define cudaDevAttrAsyncEngineCount cudaX(DeviceAttributeAsyncEngineCount)
#define cudaDevAttrUnifiedAddressing cudaX(DeviceAttributeUnifiedAddressing)
#define cudaDevAttrMaxTexture1DLayeredWidth \
	cudaX(DeviceAttributeMaxTexture1DLayeredWidth)
#define cudaDevAttrMaxTexture1DLayeredLayers \
	cudaX(DeviceAttributeMaxTexture1DLayeredLayers)
#define cudaDevAttrResvered44 cudaX(DeviceAttributeResvered44)
#define cudaDevAttrMaxTexture2DGatherWidth \
	cudaX(DeviceAttributeMaxTexture2DGatherWidth)
#define cudaDevAttrMaxTexture2DGatherHeight \
	cudaX(DeviceAttributeMaxTexture2DGatherHeight)
#define cudaDevAttrMaxTexture3DWidthAlt \
	cudaX(DeviceAttributeMaxTexture3DWidthAlt)
#define cudaDevAttrMaxTexture3DHeightAlt \
	cudaX(DeviceAttributeMaxTexture3DHeightAlt)
#define cudaDevAttrMaxTexture3DDepthAlt \
	cudaX(DeviceAttributeMaxTexture3DDepthAlt)
#define cudaDevAttrPciDomainId cudaX(DeviceAttributePciDomainId)
#define cudaDevAttrTexturePitchAlignment \
	cudaX(DeviceAttributeTexturePitchAlignment)
#define cudaDevAttrMaxTextureCubemapWidth \
	cudaX(DeviceAttributeMaxTextureCubemapWidth)
#define cudaDevAttrMaxTextureCubemapLayeredWidth \
	cudaX(DeviceAttributeMaxTextureCubemapLayeredWidth)
#define cudaDevAttrMaxTextureCubemapLayeredLayers \
	cudaX(DeviceAttributeMaxTextureCubemapLayeredLayers)
#define cudaDevAttrMaxSurface1DWidth cudaX(DeviceAttributeMaxSurface1DWidth)
#define cudaDevAttrMaxSurface2DWidth cudaX(DeviceAttributeMaxSurface2DWidth)
#define cudaDevAttrMaxSurface2DHeight cudaX(DeviceAttributeMaxSurface2DHeight)
#define cudaDevAttrMaxSurface3DWidth cudaX(DeviceAttributeMaxSurface3DWidth)
#define cudaDevAttrMaxSurface3DHeight cudaX(DeviceAttributeMaxSurface3DHeight)
#define cudaDevAttrMaxSurface3DDepth cudaX(DeviceAttributeMaxSurface3DDepth)
#define cudaDevAttrMaxSurface1DLayeredWidth \
	cudaX(DeviceAttributeMaxSurface1DLayeredWidth)
#define cudaDevAttrMaxSurface1DLayeredLayers \
	cudaX(DeviceAttributeMaxSurface1DLayeredLayers)
#define cudaDevAttrMaxSurface2DLayeredWidth \
	cudaX(DeviceAttributeMaxSurface2DLayeredWidth)
#define cudaDevAttrMaxSurface2DLayeredHeight \
	cudaX(DeviceAttributeMaxSurface2DLayeredHeight)
#define cudaDevAttrMaxSurface2DLayeredLayers \
	cudaX(DeviceAttributeMaxSurface2DLayeredLayers)
#define cudaDevAttrMaxSurfaceCubemapWidth \
	cudaX(DeviceAttributeMaxSurfaceCubemapWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredWidth \
	cudaX(DeviceAttributeMaxSurfaceCubemapLayeredWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredLayers \
	cudaX(DeviceAttributeMaxSurfaceCubemapLayeredLayers)
#define cudaDevAttrTexture1DLinearWidth \
	cudaX(DeviceAttributeTexture1DLinearWidth)
#define cudaDevAttrTexture2DLinearWidth \
	cudaX(DeviceAttributeTexture2DLinearWidth)
#define cudaDevAttrTexture2DLinearHeight \
	cudaX(DeviceAttributeTexture2DLinearHeight)
#define cudaDevAttrTexture2DLinearPitch \
	cudaX(DeviceAttributeTexture2DLinearPitch)
#define cudaDevAttrMaxTexture2DMipmappedWidth \
	cudaX(DeviceAttributeMaxTexture2DMipmappedWidth)
#define cudaDevAttrMaxTexture2DMipmappedHeight \
	cudaX(DeviceAttributeMaxTexture2DMipmappedHeight)
#define cudaDevAttrComputeCapabilityMajor \
	cudaX(DeviceAttributeComputeCapabilityMajor)
#define cudaDevAttrComputeCapabilityMinor \
	cudaX(DeviceAttributeComputeCapabilityMinor)
#define cudaDevAttrStreamPrioritiesSupported \
	cudaX(DeviceAttributeStreamPrioritiesSupported)
#define cudaDevAttrGlobalL1CacheSupported \
	cudaX(DeviceAttributeGlobalL1CacheSupported)
#define cudaDevAttrLocalL1CacheSupported \
	cudaX(DeviceAttributeLocalL1CacheSupported)
#define cudaDevAttrMaxSharedMemoryPerMultiprocessor \
	cudaX(DeviceAttributeMaxSharedMemoryPerMultiprocessor)
#define cudaDevAttrMaxRegistersPerMultiprocessor \
	cudaX(DeviceAttributeMaxRegistersPerMultiprocessor)
#define cudaDevAttrManagedMemory cudaX(DeviceAttributeManagedMemory)
#define cudaDevAttrIsMultiGpuBoard cudaX(DeviceAttributeIsMultiGpuBoard)
#define cudaDevAttrMultiGpuBoardGroupID \
	cudaX(DeviceAttributeMultiGpuBoardGroupID)
#define cudaDevAttrHostNativeAtomicSupported \
	cudaX(DeviceAttributeHostNativeAtomicSupported)
#define cudaDevAttrSingleToDoublePrecisionPerfRatio \
	cudaX(DeviceAttributeSingleToDoublePrecisionPerfRatio)
#define cudaDevAttrPageableMemoryAccess \
	cudaX(DeviceAttributePageableMemoryAccess)
#define cudaDevAttrConcurrentManagedAccess \
	cudaX(DeviceAttributeConcurrentManagedAccess)
#define cudaDevAttrComputePreemptionSupported \
	cudaX(DeviceAttributeComputePreemptionSupported)
#define cudaDevAttrCanUseHostPointerForRegisteredMem \
	cudaX(DeviceAttributeCanUseHostPointerForRegisteredMem)
#define cudaDevAttrReserved92 cudaX(DeviceAttributeReserved92)
#define cudaDevAttrReserved93 cudaX(DeviceAttributeReserved93)
#define cudaDevAttrReserved94 cudaX(DeviceAttributeReserved94)
#define cudaDevAttrCooperativeLaunch cudaX(DeviceAttributeCooperativeLaunch)
#define cudaDevAttrCooperativeMultiDeviceLaunch \
	cudaX(DeviceAttributeCooperativeMultiDeviceLaunch)
#define cudaDevAttrMaxSharedMemoryPerBlockOptin \
	cudaX(DeviceAttributeMaxSharedMemoryPerBlockOptin)
#define cudaDevAttrCanFlushRemoteWrites \
	cudaX(DeviceAttributeCanFlushRemoteWrites)
#define cudaDevAttrHostRegisterSupported \
	cudaX(DeviceAttributeHostRegisterSupported)
#define cudaDevAttrPageableMemoryAccessUsesHostPageTables \
	cudaX(DeviceAttributePageableMemoryAccessUsesHostPageTables)
#define cudaDevAttrDirectManagedMemAccessFromHost \
	cudaX(DeviceAttributeDirectManagedMemAccessFromHost)
#define cudaDevAttrReserved102 cudaX(DeviceAttributeReserved102)
#define cudaDevAttrReserved103 cudaX(DeviceAttributeReserved103)
#define cudaDevAttrReserved104 cudaX(DeviceAttributeReserved104)
#define cudaDevAttrReserved105 cudaX(DeviceAttributeReserved105)
#define cudaDevAttrReserved107 cudaX(DeviceAttributeReserved107)
#define cudaDevAttrMaxPersistingL2CacheSize \
	cudaX(DeviceAttributeMaxPersistingL2CacheSize)
#define cudaDevAttrMaxAccessPolicyWindowSize \
	cudaX(DeviceAttributeMaxAccessPolicyWindowSize)
#define cudaDevAttrReserved110 cudaX(DeviceAttributeReserved110)
#define cudaDevAttrReservedSharedMemoryPerBlock \
	cudaX(DeviceAttributeReservedSharedMemoryPerBlock)
#define cudaDevAttrSparseCudaArraySupported \
	cudaXCudaX(DeviceAttributeSparse, ArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported \
	cudaX(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported \
	cudaX(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported \
	cudaX(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported \
	cudaX(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions \
	cudaX(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering \
	cudaX(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes \
	cudaX(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch cudaX(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingCudaArraySupported \
	cudaXCudaX(DeviceAttributeDeferredMapping, ArraySupported)
#define cudaDevAttrReserved122 cudaX(DeviceAttributeReserved122)
#define cudaDevAttrReserved123 cudaX(DeviceAttributeReserved123)
#define cudaDevAttrReserved124 cudaX(DeviceAttributeReserved124)
#define cudaDevAttrIpcEventSupport cudaX(DeviceAttributeIpcEventSupport)
#define cudaDevAttrMemSyncDomainCount cudaX(DeviceAttributeMemSyncDomainCount)
#define cudaDevAttrReserved127 cudaX(DeviceAttributeReserved127)
#define cudaDevAttrReserved128 cudaX(DeviceAttributeReserved128)
#define cudaDevAttrReserved129 cudaX(DeviceAttributeReserved129)
#define cudaDevAttrNumaConfig cudaX(DeviceAttributeNumaConfig)
#define cudaDevAttrNumaId cudaX(DeviceAttributeNumaId)
#define cudaDevAttrReserved132 cudaX(DeviceAttributeReserved132)
#define cudaDevAttrMpsEnabled cudaX(DeviceAttributeMpsEnabled)
#define cudaDevAttrHostNumaId cudaX(DeviceAttributeHostNumaId)
#define cudaDevAttrWaveSize cudaX(DeviceAttributeWaveSize)
#define cudaDevAttrHdpMemFlushCntl cudaX(DeviceAttributeHdpMemFlushCntl)
#define cudaDevAttrHdpRegFlushCntl cudaX(DeviceAttributeHdpRegFlushCntl)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedFunc \
	cudaX(DeviceAttributeCooperativeMultiDeviceUnmatchedFunc)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim \
	cudaX(DeviceAttributeCooperativeMultiDeviceUnmatchedGridDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim \
	cudaX(DeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem \
	cudaX(DeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem)
#define cudaDevAttrAsicRevision cudaX(DeviceAttributeAsicRevision)
#define cudaDevAttrVirtualMemoryManagementSupported \
	cudaX(DeviceAttributeVirtualMemoryManagementSupported)
#define cudaDevAttrHandleTypePosixFileDescriptorSupported \
	cudaX(DeviceAttributeHandleTypePosixFileDescriptorSupported)
#define cudaDevAttrHandleTypeWin32HandleSupported \
	cudaX(DeviceAttributeHandleTypeWin32HandleSupported)
#define cudaDevAttrGenericCompressionSupported \
	cudaX(DeviceAttributeGenericCompressionSupported)
#define cudaDevAttrCanUseStreamWaitValue \
	cudaX(DeviceAttributeCanUseStreamWaitValue)
#define cudaDevAttrCanUseStreamMemOps cudaX(DeviceAttributeCanUseStreamMemOps)
#define cudaDevAttrCanUseStreamWaitWaitValueNor \
	cudaX(DeviceAttributeCanUseStreamWaitWaitValueNor)
#define cudaDevAttrLocalSocketId cudaX(DeviceAttributeLocalSocketId)
#define cudaDevAttrSocketId cudaX(DeviceAttributeSocketId)
#define cudaDevAttrPeerSocketId cudaX(DeviceAttributePeerSocketId)
#define cudaDevAttrMulticastSupported cudaX(DeviceAttributeMulticastSupported)

#endif
