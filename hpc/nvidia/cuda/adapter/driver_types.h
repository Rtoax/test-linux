// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_DRIVER_TYPES_H
#define __CUDA_ADAPTER_DRIVER_TYPES_H 1

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

#endif
