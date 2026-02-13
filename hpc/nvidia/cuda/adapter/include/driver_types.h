// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_DRIVER_TYPES_H
#define __CUDA_ADAPTER_DRIVER_TYPES_H 1

#include "wrapper_defs.h"

/**
 * typedef __device_builtin__ enum cudaError cudaError_t
 */
#define cudaError_t __cuda(Error_t)
#define cudaSuccess __cuda(Success)
#define cudaErrorInvalidValue __cuda(ErrorInvalidValue)
#define cudaErrorMemoryAllocation __cuda(ErrorMemoryAllocation)
#define cudaErrorInitializationError __cuda(ErrorInitializationError)
#define cudaErrorCudartUnloading __cuda(ErrorCudartUnloading)
#define cudaErrorProfilerDisabled __cuda(ErrorProfilerDisabled)
#define cudaErrorProfilerNotInitialized __cuda(ErrorProfilerNotInitialized)
#define cudaErrorProfilerAlreadyStarted __cuda(ErrorProfilerAlreadyStarted)
#define cudaErrorProfilerAlreadyStopped __cuda(ErrorProfilerAlreadyStopped)
#define cudaErrorInvalidConfiguration __cuda(ErrorInvalidConfiguration)
#define cudaErrorInvalidPitchValue __cuda(ErrorInvalidPitchValue)
#define cudaErrorInvalidSymbol __cuda(ErrorInvalidSymbol)
#define cudaErrorInvalidHostPointer __cuda(ErrorInvalidHostPointer)
#define cudaErrorInvalidDevicePointer __cuda(ErrorInvalidDevicePointer)
#define cudaErrorInvalidTexture __cuda(ErrorInvalidTexture)
#define cudaErrorInvalidTextureBinding __cuda(ErrorInvalidTextureBinding)
#define cudaErrorInvalidChannelDescriptor __cuda(ErrorInvalidChannelDescriptor)
#define cudaErrorInvalidMemcpyDirection __cuda(ErrorInvalidMemcpyDirection)
#define cudaErrorAddressOfConstant __cuda(ErrorAddressOfConstant)
#define cudaErrorTextureFetchFailed __cuda(ErrorTextureFetchFailed)
#define cudaErrorTextureNotBound __cuda(ErrorTextureNotBound)
#define cudaErrorSynchronizationError __cuda(ErrorSynchronizationError)
#define cudaErrorInvalidFilterSetting __cuda(ErrorInvalidFilterSetting)
#define cudaErrorInvalidNormSetting __cuda(ErrorInvalidNormSetting)
#define cudaErrorMixedDeviceExecution __cuda(ErrorMixedDeviceExecution)
#define cudaErrorNotYetImplemented __cuda(ErrorNotYetImplemented)
#define cudaErrorMemoryValueTooLarge __cuda(ErrorMemoryValueTooLarge)
#define cudaErrorStubLibrary __cuda(ErrorStubLibrary)
#define cudaErrorInsufficientDriver __cuda(ErrorInsufficientDriver)
#define cudaErrorCallRequiresNewerDriver __cuda(ErrorCallRequiresNewerDriver)
#define cudaErrorInvalidSurface __cuda(ErrorInvalidSurface)
#define cudaErrorDuplicateVariableName __cuda(ErrorDuplicateVariableName)
#define cudaErrorDuplicateTextureName __cuda(ErrorDuplicateTextureName)
#define cudaErrorDuplicateSurfaceName __cuda(ErrorDuplicateSurfaceName)
#define cudaErrorDevicesUnavailable __cuda(ErrorDevicesUnavailable)
#define cudaErrorIncompatibleDriverContext \
	__cuda(ErrorIncompatibleDriverContext)
#define cudaErrorMissingConfiguration __cuda(ErrorMissingConfiguration)
#define cudaErrorPriorLaunchFailure __cuda(ErrorPriorLaunchFailure)
#define cudaErrorLaunchMaxDepthExceeded __cuda(ErrorLaunchMaxDepthExceeded)
#define cudaErrorLaunchFileScopedTex __cuda(ErrorLaunchFileScopedTex)
#define cudaErrorLaunchFileScopedSurf __cuda(ErrorLaunchFileScopedSurf)
#define cudaErrorSyncDepthExceeded __cuda(ErrorSyncDepthExceeded)
#define cudaErrorLaunchPendingCountExceeded \
	__cuda(ErrorLaunchPendingCountExceeded)
#define cudaErrorInvalidDeviceFunction __cuda(ErrorInvalidDeviceFunction)
#define cudaErrorNoDevice __cuda(ErrorNoDevice)
#define cudaErrorInvalidDevice __cuda(ErrorInvalidDevice)
#define cudaErrorDeviceNotLicensed __cuda(ErrorDeviceNotLicensed)
#define cudaErrorSoftwareValidityNotEstablished \
	__cuda(ErrorSoftwareValidityNotEstablished)
#define cudaErrorStartupFailure __cuda(ErrorStartupFailure)
#define cudaErrorInvalidKernelImage __cuda(ErrorInvalidKernelImage)
#define cudaErrorDeviceUninitialized __cuda(ErrorDeviceUninitialized)
#define cudaErrorMapBufferObjectFailed __cuda(ErrorMapBufferObjectFailed)
#define cudaErrorUnmapBufferObjectFailed __cuda(ErrorUnmapBufferObjectFailed)
#define cudaErrorArrayIsMapped __cuda(ErrorArrayIsMapped)
#define cudaErrorAlreadyMapped __cuda(ErrorAlreadyMapped)
#define cudaErrorNoKernelImageForDevice __cuda(ErrorNoKernelImageForDevice)
#define cudaErrorAlreadyAcquired __cuda(ErrorAlreadyAcquired)
#define cudaErrorNotMapped __cuda(ErrorNotMapped)
#define cudaErrorNotMappedAsArray __cuda(ErrorNotMappedAsArray)
#define cudaErrorNotMappedAsPointer __cuda(ErrorNotMappedAsPointer)
#define cudaErrorECCUncorrectable __cuda(ErrorECCUncorrectable)
#define cudaErrorUnsupportedLimit __cuda(ErrorUnsupportedLimit)
#define cudaErrorDeviceAlreadyInUse __cuda(ErrorDeviceAlreadyInUse)
#define cudaErrorPeerAccessUnsupported __cuda(ErrorPeerAccessUnsupported)
#define cudaErrorInvalidPtx __cuda(ErrorInvalidPtx)
#define cudaErrorInvalidGraphicsContext __cuda(ErrorInvalidGraphicsContext)
#define cudaErrorNvlinkUncorrectable __cuda(ErrorNvlinkUncorrectable)
#define cudaErrorJitCompilerNotFound __cuda(ErrorJitCompilerNotFound)
#define cudaErrorUnsupportedPtxVersion __cuda(ErrorUnsupportedPtxVersion)
#define cudaErrorJitCompilationDisabled __cuda(ErrorJitCompilationDisabled)
#define cudaErrorUnsupportedExecAffinity __cuda(ErrorUnsupportedExecAffinity)
#define cudaErrorUnsupportedDevSideSync __cuda(ErrorUnsupportedDevSideSync)
#define cudaErrorContained __cuda(ErrorContained)
#define cudaErrorInvalidSource __cuda(ErrorInvalidSource)
#define cudaErrorFileNotFound __cuda(ErrorFileNotFound)
#define cudaErrorSharedObjectSymbolNotFound \
	__cuda(ErrorSharedObjectSymbolNotFound)
#define cudaErrorSharedObjectInitFailed __cuda(ErrorSharedObjectInitFailed)
#define cudaErrorOperatingSystem __cuda(ErrorOperatingSystem)
#define cudaErrorInvalidResourceHandle __cuda(ErrorInvalidResourceHandle)
#define cudaErrorIllegalState __cuda(ErrorIllegalState)
#define cudaErrorLossyQuery __cuda(ErrorLossyQuery)
#define cudaErrorSymbolNotFound __cuda(ErrorSymbolNotFound)
#define cudaErrorNotReady __cuda(ErrorNotReady)
#define cudaErrorIllegalAddress __cuda(ErrorIllegalAddress)
#define cudaErrorLaunchOutOfResources __cuda(ErrorLaunchOutOfResources)
#define cudaErrorLaunchTimeout __cuda(ErrorLaunchTimeout)
#define cudaErrorLaunchIncompatibleTexturing \
	__cuda(ErrorLaunchIncompatibleTexturing)
#define cudaErrorPeerAccessAlreadyEnabled __cuda(ErrorPeerAccessAlreadyEnabled)
#define cudaErrorPeerAccessNotEnabled __cuda(ErrorPeerAccessNotEnabled)
#define cudaErrorSetOnActiveProcess __cuda(ErrorSetOnActiveProcess)
#define cudaErrorContextIsDestroyed __cuda(ErrorContextIsDestroyed)
#define cudaErrorAssert __cuda(ErrorAssert)
#define cudaErrorTooManyPeers __cuda(ErrorTooManyPeers)
#define cudaErrorHostMemoryAlreadyRegistered \
	__cuda(ErrorHostMemoryAlreadyRegistered)
#define cudaErrorHostMemoryNotRegistered __cuda(ErrorHostMemoryNotRegistered)
#define cudaErrorHardwareStackError __cuda(ErrorHardwareStackError)
#define cudaErrorIllegalInstruction __cuda(ErrorIllegalInstruction)
#define cudaErrorMisalignedAddress __cuda(ErrorMisalignedAddress)
#define cudaErrorInvalidAddressSpace __cuda(ErrorInvalidAddressSpace)
#define cudaErrorInvalidPc __cuda(ErrorInvalidPc)
#define cudaErrorLaunchFailure __cuda(ErrorLaunchFailure)
#define cudaErrorCooperativeLaunchTooLarge \
	__cuda(ErrorCooperativeLaunchTooLarge)
#define cudaErrorTensorMemoryLeak __cuda(ErrorTensorMemoryLeak)
#define cudaErrorNotPermitted __cuda(ErrorNotPermitted)
#define cudaErrorNotSupported __cuda(ErrorNotSupported)
#define cudaErrorSystemNotReady __cuda(ErrorSystemNotReady)
#define cudaErrorSystemDriverMismatch __cuda(ErrorSystemDriverMismatch)
#define cudaErrorCompatNotSupportedOnDevice \
	__cuda(ErrorCompatNotSupportedOnDevice)
#define cudaErrorMpsConnectionFailed __cuda(ErrorMpsConnectionFailed)
#define cudaErrorMpsRpcFailure __cuda(ErrorMpsRpcFailure)
#define cudaErrorMpsServerNotReady __cuda(ErrorMpsServerNotReady)
#define cudaErrorMpsMaxClientsReached __cuda(ErrorMpsMaxClientsReached)
#define cudaErrorMpsMaxConnectionsReached __cuda(ErrorMpsMaxConnectionsReached)
#define cudaErrorMpsClientTerminated __cuda(ErrorMpsClientTerminated)
#define cudaErrorCdpNotSupported __cuda(ErrorCdpNotSupported)
#define cudaErrorCdpVersionMismatch __cuda(ErrorCdpVersionMismatch)
#define cudaErrorStreamCaptureUnsupported __cuda(ErrorStreamCaptureUnsupported)
#define cudaErrorStreamCaptureInvalidated __cuda(ErrorStreamCaptureInvalidated)
#define cudaErrorStreamCaptureMerge __cuda(ErrorStreamCaptureMerge)
#define cudaErrorStreamCaptureUnmatched __cuda(ErrorStreamCaptureUnmatched)
#define cudaErrorStreamCaptureUnjoined __cuda(ErrorStreamCaptureUnjoined)
#define cudaErrorStreamCaptureIsolation __cuda(ErrorStreamCaptureIsolation)
#define cudaErrorStreamCaptureImplicit __cuda(ErrorStreamCaptureImplicit)
#define cudaErrorCapturedEvent __cuda(ErrorCapturedEvent)
#define cudaErrorStreamCaptureWrongThread __cuda(ErrorStreamCaptureWrongThread)
#define cudaErrorTimeout __cuda(ErrorTimeout)
#define cudaErrorGraphExecUpdateFailure __cuda(ErrorGraphExecUpdateFailure)
#define cudaErrorExternalDevice __cuda(ErrorExternalDevice)
#define cudaErrorInvalidClusterSize __cuda(ErrorInvalidClusterSize)
#define cudaErrorFunctionNotLoaded __cuda(ErrorFunctionNotLoaded)
#define cudaErrorInvalidResourceType __cuda(ErrorInvalidResourceType)
#define cudaErrorInvalidResourceConfiguration \
	__cuda(ErrorInvalidResourceConfiguration)
#define cudaErrorUnknown __cuda(ErrorUnknown)
#define cudaErrorApiFailureBase __cuda(ErrorApiFailureBase)

/**
 * CUDA: struct __device_builtin__ cudaDeviceProp {...};
 * HIP: typedef struct hipDeviceProp_t {...} hipDeviceProp_t;
 * LUCA: typedef struct _lcDeviceProp_t {...} lcDeviceProp_t;
 */
#define cudaDeviceProp __cuda(DeviceProp_t)

#define cudaMemcpyKind __cuda(MemcpyKind) /* enum */
#define cudaMemcpyHostToHost __cuda(MemcpyHostToHost) /* 0 */
#define cudaMemcpyHostToDevice __cuda(MemcpyHostToDevice) /* 1 */
#define cudaMemcpyDeviceToHost __cuda(MemcpyDeviceToHost) /* 2 */
#define cudaMemcpyDeviceToDevice __cuda(MemcpyDeviceToDevice) /* 3 */
#define cudaMemcpyDefault __cuda(MemcpyDefault) /* 4 */

/* cudaMallocManaged::flags */
#define cudaMemAttachGlobal __cuda(MemAttachGlobal)
#define cudaMemAttachHost __cuda(MemAttachHost)
#define cudaMemAttachSingle __cuda(MemAttachSingle)

#define cudaLimit __cuda(Limit_t)
#define cudaLimitStackSize __cuda(LimitStackSize)
#define cudaLimitPrintfFifoSize __cuda(LimitPrintfFifoSize)
#define cudaLimitMallocHeapSize __cuda(LimitMallocHeapSize)
#define cudaLimitDevRuntimeSyncDepth __cuda(LimitDevRuntimeSyncDepth)
#define cudaLimitDevRuntimePendingLaunchCount \
	__cuda(LimitDevRuntimePendingLaunchCount)
#define cudaLimitMaxL2FetchGranularity __cuda(LimitMaxL2FetchGranularity)
#define cudaLimitPersistingL2CacheSize __cuda(LimitPersistingL2CacheSize)

/**
 * CUDA: typedef const struct cudaArray *cudaArray_const_t;
 * HIP: typedef const struct hipArray* hipArray_const_t;
 */
#define cudaArray_const_t __cuda(Array_const_t)

#if defined(__USE_HIP__)
#define cudaMemoryAdvise __cuda(MemoryAdvise) /* enum */
#elif defined(__USE_LUCA__) || defined(__USE_HPCC__)
#define cudaMemoryAdvise __cuda(MemoryAdvise_t) /* enum */
#endif
#define cudaMemAdviseSetReadMostly __cuda(MemAdviseSetReadMostly)
#define cudaMemAdviseUnsetReadMostly __cuda(MemAdviseUnsetReadMostly)
#define cudaMemAdviseSetPreferredLocation __cuda(MemAdviseSetPreferredLocation)
#define cudaMemAdviseUnsetPreferredLocation \
	__cuda(MemAdviseUnsetPreferredLocation)
#define cudaMemAdviseSetAccessedBy __cuda(MemAdviseSetAccessedBy)
#define cudaMemAdviseUnsetAccessedBy __cuda(MemAdviseUnsetAccessedBy)

#define cudaMemLocation __cuda(MemLocation) /* struct */
#define cudaMemLocationType __cuda(MemLocationType) /* enum */
#define cudaMemLocationTypeInvalid __cuda(MemLocationTypeInvalid)
#define cudaMemLocationTypeNone __cuda(MemLocationTypeNone)
#define cudaMemLocationTypeDevice __cuda(MemLocationTypeDevice)
#define cudaMemLocationTypeHost __cuda(MemLocationTypeHost)
#define cudaMemLocationTypeHostNuma __cuda(MemLocationTypeHostNuma)
#define cudaMemLocationTypeHostNumaCurrent \
	__cuda(MemLocationTypeHostNumaCurrent)

/**
 * CUDA: typedef __device_builtin__ struct CUmemPoolHandle_st *cudaMemPool_t;
 */
#define cudaMemPool_t __cuda(MemPool_t)

#define cudaMemPoolProps __cuda(MemPoolProps) /* struct */

#if defined(__USE_HIP__) || defined(__USE_LUCA__) || defined(__USE_HPCC__)
#define cudaPointerAttributes __cuda(PointerAttribute_t)
#else
#define cudaPointerAttributes __cuda(PointerAttributes)
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
#define cudaEvent_t __cuda(Event_t)

/**
 * CUDA: typedef __device_builtin__ struct CUgraph_st *cudaGraph_t;
 */
#define cudaGraph_t __cuda(Graph_t)

/**
 * CUDA: typedef __device_builtin__ struct CUgraphNode_st *cudaGraphNode_t;
 */
#define cudaGraphNode_t __cuda(GraphNode_t)

/**
 * CUDA: typedef struct CUgraphExec_st* cudaGraphExec_t;
 */
#define cudaGraphExec_t __cuda(GraphExec_t)

/**
 * CUDA: typedef struct cudaGraphEdgeData_st { ... } cudaGraphEdgeData;
 */
#define cudaGraphEdgeData __cuda(GraphEdgeData)

/**
 * CUDA: struct __device_builtin__ cudaFuncAttributes { ... };
 */
#define cudaFuncAttributes __cuda(FuncAttributes)

/**
 * CUDA: enum __device_builtin__ cudaFuncAttribute { ... };
 */
#define cudaFuncAttribute __cuda(FuncAttribute)
#define cudaFuncAttributeMaxDynamicSharedMemorySize \
	__cuda(FuncAttributeMaxDynamicSharedMemorySize)
#define cudaFuncAttributePreferredSharedMemoryCarveout \
	__cuda(FuncAttributePreferredSharedMemoryCarveout)
#define cudaFuncAttributeClusterDimMustBeSet \
	__cuda(FuncAttributeClusterDimMustBeSet)
#define cudaFuncAttributeRequiredClusterWidth \
	__cuda(FuncAttributeRequiredClusterWidth)
#define cudaFuncAttributeRequiredClusterHeight \
	__cuda(FuncAttributeRequiredClusterHeight)
#define cudaFuncAttributeRequiredClusterDepth \
	__cuda(FuncAttributeRequiredClusterDepth)
#define cudaFuncAttributeNonPortableClusterSizeAllowed \
	__cuda(FuncAttributeNonPortableClusterSizeAllowed)
#define cudaFuncAttributeClusterSchedulingPolicyPreference \
	__cuda(FuncAttributeClusterSchedulingPolicyPreference)
#define cudaFuncAttributeMax __cuda(FuncAttributeMax)

/**
 * cudaStreamCreateWithFlags()::flags
 */
#define cudaStreamDefault __cuda(StreamDefault) /* 0x00 */
#define cudaStreamNonBlocking __cuda(StreamNonBlocking) /* 0x01 */

/**
 * #define cudaStreamAttrID cudaLaunchAttributeID
 */
#define cudaStreamAttrID __cuda(StreamAttrID)
#define cudaStreamAttributeAccessPolicyWindow \
	__cuda(StreamAttributeAccessPolicyWindow)
#define cudaStreamAttributeSynchronizationPolicy \
	__cuda(StreamAttributeSynchronizationPolicy)
#define cudaStreamAttributeMemSyncDomainMap \
	__cuda(StreamAttributeMemSyncDomainMap)
#define cudaStreamAttributeMemSyncDomain __cuda(StreamAttributeMemSyncDomain)
#define cudaStreamAttributePriority __cuda(StreamAttributePriority)

/**
 * enum cudaStreamCaptureStatus {...};
 */
#define cudaStreamCaptureStatus __cuda(StreamCaptureStatus)
#define cudaStreamCaptureStatusNone __cuda(StreamCaptureStatusNone)
#define cudaStreamCaptureStatusActive __cuda(StreamCaptureStatusActive)
#define cudaStreamCaptureStatusInvalidated \
	__cuda(StreamCaptureStatusInvalidated)

/**
 * enum cudaStreamCaptureMode {...};
 */
#define cudaStreamCaptureMode __cuda(StreamCaptureMode)
#define cudaStreamCaptureModeGlobal __cuda(StreamCaptureModeGlobal) /* 0 */
#define cudaStreamCaptureModeThreadLocal __cuda(StreamCaptureModeThreadLocal)
#define cudaStreamCaptureModeRelaxed __cuda(StreamCaptureModeRelaxed)

/**
 * struct cudaMemAllocNodeParams {...};
 */
#define cudaMemAllocNodeParams __cuda(MemAllocNodeParams)

/**
 * struct cudaMemAllocNodeParamsV2 {...};
 */
#define cudaMemAllocNodeParamsV2 __cuda(MemAllocNodeParamsV2)

#define cudaMemAllocationType __cuda(MemAllocationType) /* enum */
#define cudaMemAllocationTypeInvalid __cuda(MemAllocationTypeInvalid) /* 0 */
#define cudaMemAllocationTypePinned __cuda(MemAllocationTypePinned) /* 1 */
#define cudaMemAllocationTypeManaged __cuda(MemAllocationTypeManaged) /* 2 */
#define cudaMemAllocationTypeMax __cuda(MemAllocationTypeMax) /* 0x7FFFFFFF */

/**
 * typedef __device_builtin__ struct CUuserObject_st *cudaUserObject_t;
 */
#define cudaUserObject_t __cuda(UserObject_t)
#define cudaUserObjectFlags __cuda(UserObjectFlags) /* enum */
#define cudaUserObjectNoDestructorSync __cuda(UserObjectNoDestructorSync)

/* typedef void (*cudaHostFn_t)(void *userData); */
#define cudaHostFn_t __cuda(HostFn_t)

#define cudaHostNodeParams __cuda(HostNodeParams) /* struct */

#define cudaKernelNodeParams __cuda(KernelNodeParams) /* struct */

#define cudaDeviceP2PAttr __cuda(DeviceP2PAttr) /* enum */
#define cudaDevP2PAttrPerformanceRank __cuda(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported __cuda(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported \
	__cuda(DevP2PAttrNativeAtomicSupported)
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
	__cuda(DevP2PAttrOnlyPartialNativeAtomicSupported)

/**
 * CUDA: typedef struct cudaIpcMemHandle_st {} cudaIpcEventHandle_t;
 */
#define cudaIpcMemHandle_t __cuda(IpcMemHandle_t)

/**
 * CUDA 13.0.0: enum __device_builtin__ cudaDeviceAttr {};
 * HIP: typedef enum hipDeviceAttribute_t {} hipDeviceAttribute_t;
 * LUCA: enum lcDeviceAttribute_t {};
 */
#define cudaDeviceAttr __cuda(DeviceAttribute_t)
#define cudaDevAttrMaxThreadsPerBlock __cuda(DeviceAttributeMaxThreadsPerBlock)
#define cudaDevAttrMaxBlockDimX __cuda(DeviceAttributeMaxBlockDimX)
#define cudaDevAttrMaxBlockDimY __cuda(DeviceAttributeMaxBlockDimY)
#define cudaDevAttrMaxBlockDimZ __cuda(DeviceAttributeMaxBlockDimZ)
#define cudaDevAttrMaxGridDimX __cuda(DeviceAttributeMaxGridDimX)
#define cudaDevAttrMaxGridDimY __cuda(DeviceAttributeMaxGridDimY)
#define cudaDevAttrMaxGridDimZ __cuda(DeviceAttributeMaxGridDimZ)
#define cudaDevAttrMaxSharedMemoryPerBlock \
	__cuda(DeviceAttributeMaxSharedMemoryPerBlock)
#define cudaDevAttrTotalConstantMemory \
	__cuda(DeviceAttributeTotalConstantMemory)
#define cudaDevAttrWarpSize __cuda(DeviceAttributeWarpSize)
#define cudaDevAttrMaxPitch __cuda(DeviceAttributeMaxPitch)
#define cudaDevAttrMaxRegistersPerBlock \
	__cuda(DeviceAttributeMaxRegistersPerBlock)
#define cudaDevAttrClockRate __cuda(DeviceAttributeClockRate)
#define cudaDevAttrTextureAlignment __cuda(DeviceAttributeTextureAlignment)
#define cudaDevAttrGpuOverlap __cuda(DeviceAttributeGpuOverlap)
#define cudaDevAttrMultiProcessorCount \
	__cuda(DeviceAttributeMultiProcessorCount)
#define cudaDevAttrKernelExecTimeout __cuda(DeviceAttributeKernelExecTimeout)
#define cudaDevAttrIntegrated __cuda(DeviceAttributeIntegrated)
#define cudaDevAttrCanMapHostMemory __cuda(DeviceAttributeCanMapHostMemory)
#define cudaDevAttrComputeMode __cuda(DeviceAttributeComputeMode)
#define cudaDevAttrMaxTexture1DWidth __cuda(DeviceAttributeMaxTexture1DWidth)
#define cudaDevAttrMaxTexture2DWidth __cuda(DeviceAttributeMaxTexture2DWidth)
#define cudaDevAttrMaxTexture2DHeight __cuda(DeviceAttributeMaxTexture2DHeight)
#define cudaDevAttrMaxTexture3DWidth __cuda(DeviceAttributeMaxTexture3DWidth)
#define cudaDevAttrMaxTexture3DHeight __cuda(DeviceAttributeMaxTexture3DHeight)
#define cudaDevAttrMaxTexture3DDepth __cuda(DeviceAttributeMaxTexture3DDepth)
#define cudaDevAttrMaxTexture2DLayeredWidth \
	__cuda(DeviceAttributeMaxTexture2DLayeredWidth)
#define cudaDevAttrMaxTexture2DLayeredHeight \
	__cuda(DeviceAttributeMaxTexture2DLayeredHeight)
#define cudaDevAttrMaxTexture2DLayeredLayers \
	__cuda(DeviceAttributeMaxTexture2DLayeredLayers)
#define cudaDevAttrSurfaceAligement __cuda(DeviceAttributeSurfaceAligement)
#define cudaDevAttrConcurrentKernels __cuda(DeviceAttributeConcurrentKernels)
#define cudaDevAttrEccEnabled __cuda(DeviceAttributeEccEnabled)
#define cudaDevAttrPciBusId __cuda(DeviceAttributePciBusId)
#define cudaDevAttrPciDeviceId __cuda(DeviceAttributePciDeviceId)
#define cudaDevAttrTccDriver __cuda(DeviceAttributeTccDriver)
#define cudaDevAttrMemoryClockRate __cuda(DeviceAttributeMemoryClockRate)
#define cudaDevAttrMemoryBusWidth __cuda(DeviceAttributeMemoryBusWidth)
#define cudaDevAttrL2CacheSize __cuda(DeviceAttributeL2CacheSize)
#define cudaDevAttrMaxThreadsPerMultiProcessor \
	__cuda(DeviceAttributeMaxThreadsPerMultiProcessor)
#define cudaDevAttrAsyncEngineCount __cuda(DeviceAttributeAsyncEngineCount)
#define cudaDevAttrUnifiedAddressing __cuda(DeviceAttributeUnifiedAddressing)
#define cudaDevAttrMaxTexture1DLayeredWidth \
	__cuda(DeviceAttributeMaxTexture1DLayeredWidth)
#define cudaDevAttrMaxTexture1DLayeredLayers \
	__cuda(DeviceAttributeMaxTexture1DLayeredLayers)
#define cudaDevAttrResvered44 __cuda(DeviceAttributeResvered44)
#define cudaDevAttrMaxTexture2DGatherWidth \
	__cuda(DeviceAttributeMaxTexture2DGatherWidth)
#define cudaDevAttrMaxTexture2DGatherHeight \
	__cuda(DeviceAttributeMaxTexture2DGatherHeight)
#define cudaDevAttrMaxTexture3DWidthAlt \
	__cuda(DeviceAttributeMaxTexture3DWidthAlt)
#define cudaDevAttrMaxTexture3DHeightAlt \
	__cuda(DeviceAttributeMaxTexture3DHeightAlt)
#define cudaDevAttrMaxTexture3DDepthAlt \
	__cuda(DeviceAttributeMaxTexture3DDepthAlt)
#define cudaDevAttrPciDomainId __cuda(DeviceAttributePciDomainId)
#define cudaDevAttrTexturePitchAlignment \
	__cuda(DeviceAttributeTexturePitchAlignment)
#define cudaDevAttrMaxTextureCubemapWidth \
	__cuda(DeviceAttributeMaxTextureCubemapWidth)
#define cudaDevAttrMaxTextureCubemapLayeredWidth \
	__cuda(DeviceAttributeMaxTextureCubemapLayeredWidth)
#define cudaDevAttrMaxTextureCubemapLayeredLayers \
	__cuda(DeviceAttributeMaxTextureCubemapLayeredLayers)
#define cudaDevAttrMaxSurface1DWidth __cuda(DeviceAttributeMaxSurface1DWidth)
#define cudaDevAttrMaxSurface2DWidth __cuda(DeviceAttributeMaxSurface2DWidth)
#define cudaDevAttrMaxSurface2DHeight __cuda(DeviceAttributeMaxSurface2DHeight)
#define cudaDevAttrMaxSurface3DWidth __cuda(DeviceAttributeMaxSurface3DWidth)
#define cudaDevAttrMaxSurface3DHeight __cuda(DeviceAttributeMaxSurface3DHeight)
#define cudaDevAttrMaxSurface3DDepth __cuda(DeviceAttributeMaxSurface3DDepth)
#define cudaDevAttrMaxSurface1DLayeredWidth \
	__cuda(DeviceAttributeMaxSurface1DLayeredWidth)
#define cudaDevAttrMaxSurface1DLayeredLayers \
	__cuda(DeviceAttributeMaxSurface1DLayeredLayers)
#define cudaDevAttrMaxSurface2DLayeredWidth \
	__cuda(DeviceAttributeMaxSurface2DLayeredWidth)
#define cudaDevAttrMaxSurface2DLayeredHeight \
	__cuda(DeviceAttributeMaxSurface2DLayeredHeight)
#define cudaDevAttrMaxSurface2DLayeredLayers \
	__cuda(DeviceAttributeMaxSurface2DLayeredLayers)
#define cudaDevAttrMaxSurfaceCubemapWidth \
	__cuda(DeviceAttributeMaxSurfaceCubemapWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredWidth \
	__cuda(DeviceAttributeMaxSurfaceCubemapLayeredWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredLayers \
	__cuda(DeviceAttributeMaxSurfaceCubemapLayeredLayers)
#define cudaDevAttrTexture1DLinearWidth \
	__cuda(DeviceAttributeTexture1DLinearWidth)
#define cudaDevAttrTexture2DLinearWidth \
	__cuda(DeviceAttributeTexture2DLinearWidth)
#define cudaDevAttrTexture2DLinearHeight \
	__cuda(DeviceAttributeTexture2DLinearHeight)
#define cudaDevAttrTexture2DLinearPitch \
	__cuda(DeviceAttributeTexture2DLinearPitch)
#define cudaDevAttrMaxTexture2DMipmappedWidth \
	__cuda(DeviceAttributeMaxTexture2DMipmappedWidth)
#define cudaDevAttrMaxTexture2DMipmappedHeight \
	__cuda(DeviceAttributeMaxTexture2DMipmappedHeight)
#define cudaDevAttrComputeCapabilityMajor \
	__cuda(DeviceAttributeComputeCapabilityMajor)
#define cudaDevAttrComputeCapabilityMinor \
	__cuda(DeviceAttributeComputeCapabilityMinor)
#define cudaDevAttrStreamPrioritiesSupported \
	__cuda(DeviceAttributeStreamPrioritiesSupported)
#define cudaDevAttrGlobalL1CacheSupported \
	__cuda(DeviceAttributeGlobalL1CacheSupported)
#define cudaDevAttrLocalL1CacheSupported \
	__cuda(DeviceAttributeLocalL1CacheSupported)
#define cudaDevAttrMaxSharedMemoryPerMultiprocessor \
	__cuda(DeviceAttributeMaxSharedMemoryPerMultiprocessor)
#define cudaDevAttrMaxRegistersPerMultiprocessor \
	__cuda(DeviceAttributeMaxRegistersPerMultiprocessor)
#define cudaDevAttrManagedMemory __cuda(DeviceAttributeManagedMemory)
#define cudaDevAttrIsMultiGpuBoard __cuda(DeviceAttributeIsMultiGpuBoard)
#define cudaDevAttrMultiGpuBoardGroupID \
	__cuda(DeviceAttributeMultiGpuBoardGroupID)
#define cudaDevAttrHostNativeAtomicSupported \
	__cuda(DeviceAttributeHostNativeAtomicSupported)
#define cudaDevAttrSingleToDoublePrecisionPerfRatio \
	__cuda(DeviceAttributeSingleToDoublePrecisionPerfRatio)
#define cudaDevAttrPageableMemoryAccess \
	__cuda(DeviceAttributePageableMemoryAccess)
#define cudaDevAttrConcurrentManagedAccess \
	__cuda(DeviceAttributeConcurrentManagedAccess)
#define cudaDevAttrComputePreemptionSupported \
	__cuda(DeviceAttributeComputePreemptionSupported)
#define cudaDevAttrCanUseHostPointerForRegisteredMem \
	__cuda(DeviceAttributeCanUseHostPointerForRegisteredMem)
#define cudaDevAttrReserved92 __cuda(DeviceAttributeReserved92)
#define cudaDevAttrReserved93 __cuda(DeviceAttributeReserved93)
#define cudaDevAttrReserved94 __cuda(DeviceAttributeReserved94)
#define cudaDevAttrCooperativeLaunch __cuda(DeviceAttributeCooperativeLaunch)
#define cudaDevAttrCooperativeMultiDeviceLaunch \
	__cuda(DeviceAttributeCooperativeMultiDeviceLaunch)
#define cudaDevAttrMaxSharedMemoryPerBlockOptin \
	__cuda(DeviceAttributeMaxSharedMemoryPerBlockOptin)
#define cudaDevAttrCanFlushRemoteWrites \
	__cuda(DeviceAttributeCanFlushRemoteWrites)
#define cudaDevAttrHostRegisterSupported \
	__cuda(DeviceAttributeHostRegisterSupported)
#define cudaDevAttrPageableMemoryAccessUsesHostPageTables \
	__cuda(DeviceAttributePageableMemoryAccessUsesHostPageTables)
#define cudaDevAttrDirectManagedMemAccessFromHost \
	__cuda(DeviceAttributeDirectManagedMemAccessFromHost)
#define cudaDevAttrReserved102 __cuda(DeviceAttributeReserved102)
#define cudaDevAttrReserved103 __cuda(DeviceAttributeReserved103)
#define cudaDevAttrReserved104 __cuda(DeviceAttributeReserved104)
#define cudaDevAttrReserved105 __cuda(DeviceAttributeReserved105)
#define cudaDevAttrReserved107 __cuda(DeviceAttributeReserved107)
#define cudaDevAttrMaxPersistingL2CacheSize \
	__cuda(DeviceAttributeMaxPersistingL2CacheSize)
#define cudaDevAttrMaxAccessPolicyWindowSize \
	__cuda(DeviceAttributeMaxAccessPolicyWindowSize)
#define cudaDevAttrReserved110 __cuda(DeviceAttributeReserved110)
#define cudaDevAttrReservedSharedMemoryPerBlock \
	__cuda(DeviceAttributeReservedSharedMemoryPerBlock)
#define cudaDevAttrSparseCudaArraySupported \
	__cuda_Cuda(DeviceAttributeSparse, ArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported \
	__cuda(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported \
	__cuda(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported \
	__cuda(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported \
	__cuda(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions \
	__cuda(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering \
	__cuda(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes \
	__cuda(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch __cuda(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingCudaArraySupported \
	__cuda_Cuda(DeviceAttributeDeferredMapping, ArraySupported)
#define cudaDevAttrReserved122 __cuda(DeviceAttributeReserved122)
#define cudaDevAttrReserved123 __cuda(DeviceAttributeReserved123)
#define cudaDevAttrReserved124 __cuda(DeviceAttributeReserved124)
#define cudaDevAttrIpcEventSupport __cuda(DeviceAttributeIpcEventSupport)
#define cudaDevAttrMemSyncDomainCount __cuda(DeviceAttributeMemSyncDomainCount)
#define cudaDevAttrReserved127 __cuda(DeviceAttributeReserved127)
#define cudaDevAttrReserved128 __cuda(DeviceAttributeReserved128)
#define cudaDevAttrReserved129 __cuda(DeviceAttributeReserved129)
#define cudaDevAttrNumaConfig __cuda(DeviceAttributeNumaConfig)
#define cudaDevAttrNumaId __cuda(DeviceAttributeNumaId)
#define cudaDevAttrReserved132 __cuda(DeviceAttributeReserved132)
#define cudaDevAttrMpsEnabled __cuda(DeviceAttributeMpsEnabled)
#define cudaDevAttrHostNumaId __cuda(DeviceAttributeHostNumaId)
#define cudaDevAttrWaveSize __cuda(DeviceAttributeWaveSize)
#define cudaDevAttrHdpMemFlushCntl __cuda(DeviceAttributeHdpMemFlushCntl)
#define cudaDevAttrHdpRegFlushCntl __cuda(DeviceAttributeHdpRegFlushCntl)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedFunc \
	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedFunc)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim \
	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedGridDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim \
	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem \
	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem)
#define cudaDevAttrAsicRevision __cuda(DeviceAttributeAsicRevision)
#define cudaDevAttrVirtualMemoryManagementSupported \
	__cuda(DeviceAttributeVirtualMemoryManagementSupported)
#define cudaDevAttrHandleTypePosixFileDescriptorSupported \
	__cuda(DeviceAttributeHandleTypePosixFileDescriptorSupported)
#define cudaDevAttrHandleTypeWin32HandleSupported \
	__cuda(DeviceAttributeHandleTypeWin32HandleSupported)
#define cudaDevAttrGenericCompressionSupported \
	__cuda(DeviceAttributeGenericCompressionSupported)
#define cudaDevAttrCanUseStreamWaitValue \
	__cuda(DeviceAttributeCanUseStreamWaitValue)
#define cudaDevAttrCanUseStreamMemOps __cuda(DeviceAttributeCanUseStreamMemOps)
#define cudaDevAttrCanUseStreamWaitWaitValueNor \
	__cuda(DeviceAttributeCanUseStreamWaitWaitValueNor)
#define cudaDevAttrLocalSocketId __cuda(DeviceAttributeLocalSocketId)
#define cudaDevAttrSocketId __cuda(DeviceAttributeSocketId)
#define cudaDevAttrPeerSocketId __cuda(DeviceAttributePeerSocketId)
#define cudaDevAttrMulticastSupported __cuda(DeviceAttributeMulticastSupported)

#endif
