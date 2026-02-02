// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * Input definitions:
 * - __USE_HIP__		AMD ROCm HIP
 * - __USE_HPCC__		Mars
 * - __USE_LUCA__		Luca
 *   LUCA_PHASE_II_PROJECT
 */
#ifndef __CUDA_ADAPTER_H
#define __CUDA_ADAPTER_H 1

#define CUDA_ADAPTER_MAJOR 1
#define CUDA_ADAPTER_MINOR 0
#define CUDA_ADAPTER_PATCH 0

/******************************************************************************\
 * HPCC: High Performance Computing Communications                            *
\******************************************************************************/
#if defined(__USE_HPCC__)
/* HPCC has CUDA-compatible APIs */
# define __cu(name)	hc##name
# define __cuda(name)	hc##name
# define __CU(name)	HC##name
# define __CU_cuda(n1, n2)	HC##n1##hc##n2
# define __cuda_Cuda(n1, n2)	hc##n1##Hpcc##n2
# define __CUDA(name)	HC_##name
# define __CUDA_ERROR(name)	HCC_STATUS_##name
# define __nv(name)	hc##name
# define ____nv_(name)	__hpcc_##name
# define ____NV_(name)	__HPCC_##name
# define __NV(name)	HC##name
# define __nccl(name)	hccl##name
# define __NCCL(name)	HCCL##name
# define __pnccl(name)	phccl##name
/******************************************************************************\
 * LUCA                                                                       *
\******************************************************************************/
#elif defined(__USE_LUCA__)
/**
 * In the second phase of LUCA development, the filename changed, and the
 * definition was deleted once development was completed.
 */
# ifdef LUCA_PHASE_II_PROJECT
#  define __cu(name)	lc##name
#  define __cuda(name)	lc##name
#  define __CU(name)	LC##name
#  define __CU_cuda(n1, n2)	LC##n1##lc##n2
#  define __cuda_Cuda(n1, n2)	lc##n1##Luca##n2
#  define __CUDA(name)	LC_##name
#  define __CUDA_ERROR(name)	LCC_STATUS_##name
#  define __nv(name)	lc##name
#  define __NV(name)	LC##name
#  define __nccl(name)	lccl##name
#  define __NCCL(name)	LCCL##name
#  define __pnccl(name)	plccl##name
# else /* LUCA_PHASE_II_PROJECT */
#  define __cu(name)	hc##name
#  define __cuda(name)	hc##name
#  define __CU(name)	HC##name
#  define __CU_cuda(n1, n2)	HC##n1##hc##n2
#  define __cuda_Cuda(n1, n2)	hc##n1##Hpcc##n2
#  define __CUDA(name)	HC_##name
#  define __CUDA_ERROR(name)	HCC_STATUS_##name
#  define __nv(name)	hc##name
#  define __NV(name)	HC##name
#  define __nccl(name)	hccl##name
#  define __NCCL(name)	HCCL##name
#  define __pnccl(name)	phccl##name
# endif /* LUCA_PHASE_II_PROJECT */
# define ____nv_(name)	__luca_##name
# define ____NV_(name)	__LUCA_##name
/******************************************************************************\
 * AMD ROCm HIP                                                               *
\******************************************************************************/
#elif defined(__USE_HIP__)
# define __cu(name)	hip##name
# define __cuda(name)	hip##name
# define __CU(name)	HIP##name
/* TODO: __CU_cuda, __cuda_Cuda */
# define __CUDA(name)	HIP_##name
# define __CUDA_ERROR(name)	HIP_##name
# define __nv(name)	hip##name
# define ____nv_(name)	__hip_##name
# define ____NV_(name)	__HIP_##name
# define __NV(name)	HIP##name
/* ROCm rccl use 'nccl' prefix, see /usr/include/rccl/rccl.h */
# define __nccl(name)	nccl##name
# define __NCCL(name)	NCCL##name
# define __pnccl(name)	pnccl##name
#else
# error "Must define one of __USE_HPCC__, __USE_HIP__, __USE_LUCA__"
#endif

/* typedef hcError_t	cudaError_t; */
#define cudaError_t	__cuda(Error_t)
#define cudaSuccess	__cuda(Success)
#define cudaErrorInvalidValue	__cuda(ErrorInvalidValue)
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
 * CUDA 13
 * cudaError_t cudaPeekAtLastError(void);
 *
 * HIP 6.3.42133-0
 * hipError_t hipPeekAtLastError(void);
 */
#define cudaPeekAtLastError()	__cuda(PeekAtLastError())

#define cudaGetLastError()	__cuda(GetLastError())
#define cudaGetErrorString(err)	__cuda(GetErrorString(err))

/**
 * CUDA 13:
 * const char* cudaGetErrorName(cudaError_t error);
 *
 * HIP 6.3.42133-0
 * const char* hipGetErrorName(hipError_t hip_error);
 */
#define cudaGetErrorName(error)	__cuda(GetErrorName(error))

/**
 * CUDA 13:
 * CUresult cuGetErrorName(CUresult error, const char **pStr);
 *
 * LUCA:
 * const char *lcGetErrorName(lcError_t lc_error);
 */
#if defined(__USE_LUCA__) || defined(__USE_HPCC__) || defined(__USE_HIP__)
#define cuGetErrorName(error, pStr)                  \
	do {                                         \
		const char **__pstr = pStr;          \
		*__pstr = __cu(GetErrorName(error)); \
	} while (0)
#else
#define cuGetErrorName __cu(GetErrorName)
#endif

#define cudaLimit	__cuda(Limit_t)
#define cudaLimitStackSize	__cuda(LimitStackSize)
#define cudaLimitPrintfFifoSize	__cuda(LimitPrintfFifoSize)
#define cudaLimitMallocHeapSize	__cuda(LimitMallocHeapSize)
#define cudaLimitDevRuntimeSyncDepth	__cuda(LimitDevRuntimeSyncDepth)
#define cudaLimitDevRuntimePendingLaunchCount	__cuda(LimitDevRuntimePendingLaunchCount)
#define cudaLimitMaxL2FetchGranularity	__cuda(LimitMaxL2FetchGranularity)
#define cudaLimitPersistingL2CacheSize	__cuda(LimitPersistingL2CacheSize)
#define cudaDeviceSetLimit(limit, value)	__cuda(DeviceSetLimit(limit, value))
#define cudaDeviceGetLimit(limit, value)	__cuda(DeviceGetLimit(limit, value))

/**
 * CUDA
 * cudaError_t cudaDriverGetVersion(int *driverVersion);
 */
#define cudaDriverGetVersion	__cuda(DriverGetVersion)

/**
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html
 */
#define cudaMalloc(pp, sz)	__cuda(Malloc(pp, sz))
#define cudaFree(ptr)	__cuda(Free(ptr))
/**
 * Pinned memory, on CPU memory, GPU accessable, DMA copy
 *
 * HIPCC 6.4
 * hipError_t hipMallocHost(void** ptr, size_t size);
 * hipError_t hipHostMalloc(void** ptr, size_t size, unsigned int flags);
 */
#define cudaMallocHost(ptr, sz, flags)	__cuda(MallocHost(ptr, sz, flags))
#define cudaFreeHost(ptr)	__cuda(FreeHost(ptr))
#define cudaMemset(ptr, v, size)	__cuda(Memset(ptr, v, size))

/**
 * CUDA 12
 * cudaError_t cudaMemsetAsync(void *devPtr, int value, size_t count,
 *                             cudaStream_t stream);
 *
 * HIP
 * hipError_t hipMemsetAsync(void* dst, int value, size_t sizeBytes,
 *                           hipStream_t stream);
 */
#define cudaMemsetAsync(ptr, v, size, stream)	__cuda(MemsetAsync(ptr, v, size, stream))
/**
 * CUDA 12
 * cudaError_t cudaMemset2DAsync(void *devPtr, size_t pitch, int value,
 *                               size_t width, size_t height,
 *                               cudaStream_t stream __dv(0));
 *
 * HIP
 * hipError_t hipMemset2DAsync(void* dst, size_t pitch, int value,
 *                             size_t width, size_t height,
 *                             hipStream_t stream __dparm(0));
 */
#define cudaMemset2DAsync(dst, pitch, value, width, height, stream)	\
	__cuda(Memset2DAsync(dst, pitch, value, width, height, stream))
#define cudaMemcpy(dst, src, size, flag)	__cuda(Memcpy(dst, src, size, flag))
#define cudaMemcpyKind	__cuda(MemcpyKind)
#define cudaMemcpyHostToHost	__cuda(MemcpyHostToHost)	/* 0 */
#define cudaMemcpyHostToDevice	__cuda(MemcpyHostToDevice)	/* 1 */
#define cudaMemcpyDeviceToHost	__cuda(MemcpyDeviceToHost)	/* 2 */
#define cudaMemcpyDeviceToDevice	__cuda(MemcpyDeviceToDevice)	/* 3 */
#define cudaMemcpyDefault	__cuda(MemcpyDefault)	/* 4 */

/**
 * CUDA 12
 * cudaError_t cudaMemcpyAsync(void *dst, const void *src, size_t count,
 *                             enum cudaMemcpyKind kind, cudaStream_t stream);
 *
 * HIP
 * hipError_t hipMemcpyAsync(void* dst, const void* src, size_t sizeBytes,
 *                           hipMemcpyKind kind,
 *                           hipStream_t stream __dparm(0));
 */
#define cudaMemcpyAsync	__cuda(MemcpyAsync)

/**
 * CUDA 13.0
 * cudaError_t cudaHostRegister(void *ptr, size_t size, unsigned int flags);
 * cudaError_t cudaHostUnregister(void *ptr);
 *
 * HIP 6.4
 * hipError_t hipHostRegister(void* hostPtr, size_t sizeBytes, unsigned int flags);
 */
#define cudaHostRegister(p,s,f)	__cuda(HostRegister(p,s,f))
#define cudaHostUnregister(p)	__cuda(HostUnregister(p))

/**
 * CUDA 13.0
 * cudaError_t cudaHostGetDevicePointer(T **pDevice, void *pHost, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipHostGetDevicePointer(void** devPtr, void* hstPtr, unsigned int flags);
 */
#define cudaHostGetDevicePointer(d,h,f)	__cuda(HostGetDevicePointer(d,h,f))

/**
 * CUDA: typedef const struct cudaArray *cudaArray_const_t;
 * HIP: typedef const struct hipArray* hipArray_const_t;
 */
#define cudaArray_const_t	__cuda(Array_const_t)

/**
 * CUDA
 * cudaError_t cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width,
 *                          size_t height, enum cudaMemcpyKind kind);
 * cudaError_t cudaMemcpy2DToArray(cudaArray_t dst, size_t wOffset, size_t hOffset, const void *src,
 *                                 size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind);
 * cudaError_t cudaMemcpy2DFromArray(void *dst, size_t dpitch, cudaArray_const_t src,
 *                                   size_t wOffset, size_t hOffset, size_t width, size_t height,
 *                                   enum cudaMemcpyKind kind);
 *
 * HIP
 * hipError_t hipMemcpy2D(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width,
 *                        size_t height, hipMemcpyKind kind);
 * hipError_t hipMemcpyParam2D(const hip_Memcpy2D* pCopy);
 * hipError_t hipMemcpyParam2DAsync(const hip_Memcpy2D* pCopy, hipStream_t stream __dparm(0));
 * hipError_t hipMemcpy2DAsync(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width,
 *                             size_t height, hipMemcpyKind kind, hipStream_t stream __dparm(0));
 * hipError_t hipMemcpy2DToArray(hipArray_t dst, size_t wOffset, size_t hOffset, const void* src,
 *                               size_t spitch, size_t width, size_t height, hipMemcpyKind kind);
 * hipError_t hipMemcpy2DToArrayAsync(hipArray_t dst, size_t wOffset, size_t hOffset, const void* src,
 *                                    size_t spitch, size_t width, size_t height, hipMemcpyKind kind,
 *                                    hipStream_t stream __dparm(0));
 * hipError_t hipMemcpy2DArrayToArray(hipArray_t dst, size_t wOffsetDst, size_t hOffsetDst,
 *                                    hipArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc,
 *                                    size_t width, size_t height, hipMemcpyKind kind);
 * hipError_t hipMemcpyToArray(hipArray_t dst, size_t wOffset, size_t hOffset, const void* src,
 *                             size_t count, hipMemcpyKind kind);
 * hipError_t hipMemcpyFromArray(void* dst, hipArray_const_t srcArray, size_t wOffset, size_t hOffset,
 *                               size_t count, hipMemcpyKind kind);
 * hipError_t hipMemcpy2DFromArray(void* dst, size_t dpitch, hipArray_const_t src,
 *                                 size_t wOffset, size_t hOffset,
 *                                 size_t width, size_t height, hipMemcpyKind kind);
 * hipError_t hipMemcpy2DFromArrayAsync(void* dst, size_t dpitch, hipArray_const_t src,
 *                                      size_t wOffset, size_t hOffset, size_t width,
 *                                      size_t height, hipMemcpyKind kind, hipStream_t stream __dparm(0));
 * hipError_t hipMemcpyAtoH(void* dst, hipArray_t srcArray, size_t srcOffset, size_t count);
 * hipError_t hipMemcpyHtoA(hipArray_t dstArray, size_t dstOffset, const void* srcHost, size_t count);
 * hipError_t hipMemcpy3D(const struct hipMemcpy3DParms* p);
 * hipError_t hipMemcpy3DAsync(const struct hipMemcpy3DParms* p, hipStream_t stream __dparm(0));
 * hipError_t hipDrvMemcpy3D(const HIP_MEMCPY3D* pCopy);
 * hipError_t hipDrvMemcpy3DAsync(const HIP_MEMCPY3D* pCopy, hipStream_t stream);
 */
#define cudaMemcpy2D	__cuda(Memcpy2D)

/**
 * CUDA 12
 * cudaError_t cudaMemcpy2DAsync(void *dst, size_t dpitch, const void *src,
 *                               size_t spitch, size_t width, size_t height,
 *                               enum cudaMemcpyKind kind, cudaStream_t stream __dv(0));
 *
 * HIP
 * hipError_t hipMemcpy2DAsync(void* dst, size_t dpitch, const void* src,
 *                             size_t spitch, size_t width, size_t height,
 *                             hipMemcpyKind kind, hipStream_t stream __dparm(0));
 */
#define cudaMemcpy2DAsync	__cuda(Memcpy2DAsync)

/**
 * CUDA 12 don't have cudaMemcpyWithStream()
 *
 * HIP
 * hipError_t hipMemcpyWithStream(void* dst, const void* src, size_t sizeBytes,
 *                                hipMemcpyKind kind, hipStream_t stream);
 */

/**
 * CUDA 13
 * cudaError_t cudaMemcpyFromSymbol(void *dst, const void *symbol,
 *                                  size_t count, size_t offset __dv(0),
 *                                  enum cudaMemcpyKind kind __dv(cudaMemcpyDeviceToHost));
 *
 * HIP
 * hipError_t hipMemcpyFromSymbol(void* dst, const void* symbol,
 *                                size_t sizeBytes, size_t offset __dparm(0),
 *                                hipMemcpyKind kind __dparm(hipMemcpyDeviceToHost));
 */
#define cudaMemcpyFromSymbol	__cuda(MemcpyFromSymbol)
#define cudaMemcpyToSymbol	__cuda(MemcpyToSymbol)

/**
 * CUDA 13:
 * cudaError_t cudaGetSymbolAddress(void **devPtr, const void *symbol);
 *
 * HPCC:
 * hcError_t hcGetSymbolAddress(void **devPtr, const void *symbol);
 */
#define cudaGetSymbolAddress	__cuda(GetSymbolAddress)

/**
 * CUDA 13
 * cudaError_t cudaMemcpyPeer(void *dst, int dstDevice, const void *src, int srcDevice,
 *                            size_t count);
 *
 * HIP
 * hipError_t hipMemcpyPeer(void* dst, int dstDeviceId, const void* src, int srcDeviceId,
 *                          size_t sizeBytes);
 *
 * LUCA:
 * lcError_t lcMemcpyPeer(void *dst, int dstDevice, const void *src, int srcDevice,
 *                        size_t sizeBytes);
 */
#define cudaMemcpyPeer	__cuda(MemcpyPeer)

/**
 * CUDA 13
 * cudaError_t cudaMemcpyPeerAsync(void *dst, int dstDevice, const void *src, int srcDevice,
 *                                 size_t count, cudaStream_t stream __dv(0));
 *
 * HIP
 * hipError_t hipMemcpyPeerAsync(void* dst, int dstDeviceId, const void* src, int srcDevice,
 *                               size_t sizeBytes, hipStream_t stream __dparm(0));
 *
 * LUCA
 * lcError_t lcMemcpyPeerAsync(void *dst, int dstDevice, const void *src, int srcDevice,
 *                             size_t sizeBytes, lcStream_t stream);
 */
#define cudaMemcpyPeerAsync	__cuda(MemcpyPeerAsync)

/**
 * cudaError_t cudaMallocManaged(void **devPtr, size_t size,
 *                               unsigned int flags = cudaMemAttachGlobal);
 * hcError_t hcMallocManaged(void **dev_ptr, size_t size,
 *                           unsigned int flags __dparm(hcMemAttachGlobal));
 */
/* flags */
#define cudaMemAttachGlobal	__cuda(MemAttachGlobal)
#define cudaMemAttachHost	__cuda(MemAttachHost)
#define cudaMemAttachSingle	__cuda(MemAttachSingle)
#define cudaMallocManaged(pp, sz, flags)	__cuda(MallocManaged(pp, sz, flags))
/**
 * CUDA 12
 * cudaError_t cudaMallocAsync(void **devPtr, size_t size, cudaStream_t hStream);
 *
 * HIP
 * hipError_t hipMallocAsync(void** dev_ptr, size_t size, hipStream_t stream);
 *
 * LUCA
 * lcError_t lcMallocAsync(void **devPtr, size_t size, lcStream_t hStream);
 */
#define cudaMallocAsync(pp, sz, stream)	__cuda(MallocAsync(pp, sz, stream))

/**
 * CUDA 12:
 * cudaError_t cudaFreeAsync(void *devPtr, cudaStream_t hStream);
 *
 * HIP:
 * hipError_t hipFreeAsync(void* dev_ptr, hipStream_t stream);
 */
#define cudaFreeAsync(ptr, stream)	__cuda(FreeAsync(ptr, stream))

/**
 * CUDA V13.0.48
 * cudaError_t cudaMemAdvise(const void* devPtr, size_t count,
 *                           cudaMemoryAdvise advice,
 *                           cudaMemLocation location);
 *
 * CUDA
 * V12.2.140 CUDA_VERSION=12020 Ubuntu 25.04
 * V12.4.131 CUDA_VERSION=12040 Debian 13
 * cudaError_t cudaMemAdvise(const void* devPtr, size_t count,
 *                           cudaMemoryAdvise advice,
 *                           int device);
 * cudaError_t cudaMemAdvise_v2(const void *devPtr, size_t count,
 *                              enum cudaMemoryAdvise advice,
 *                              struct cudaMemLocation location)
 *
 * HPCC 2.33.1, 3.0.0
 * hcError_t hcMemAdvise(const void *dev_ptr, size_t count,
 *                       hcMemoryAdvise_t advice,
 *                       int device);
 *
 * HIP 5.7.31921-0
 * hipError_t hipMemAdvise(const void* devPtr, size_t count,
 *                         hipMemoryAdvise advice,
 *                         int device);
 */
#define cudaMemAdvise(ptr, count, advice, location_or_device)	\
	__cuda(MemAdvise(ptr, count, advice, location_or_device))
#define cudaMemAdvise_v2(ptr, count, advice, location_or_device)	\
	__cuda(MemAdvise_v2(ptr, count, advice, location_or_device))

#ifdef __USE_HIP__
#define cudaMemoryAdvise	__cuda(MemoryAdvise)	/* enum */
#else
#define cudaMemoryAdvise	__cuda(MemoryAdvise_t)	/* enum */
#endif
#define cudaMemAdviseSetReadMostly	__cuda(MemAdviseSetReadMostly)
#define cudaMemAdviseUnsetReadMostly	__cuda(MemAdviseUnsetReadMostly)
#define cudaMemAdviseSetPreferredLocation	__cuda(MemAdviseSetPreferredLocation)
#define cudaMemAdviseUnsetPreferredLocation	__cuda(MemAdviseUnsetPreferredLocation)
#define cudaMemAdviseSetAccessedBy	__cuda(MemAdviseSetAccessedBy)
#define cudaMemAdviseUnsetAccessedBy	__cuda(MemAdviseUnsetAccessedBy)
#define cudaMemLocation	__cuda(MemLocation)	/* struct */
#define cudaMemLocationType	__cuda(MemLocationType)	/* enum */
#define cudaMemLocationTypeInvalid	__cuda(MemLocationTypeInvalid)
#define cudaMemLocationTypeNone	__cuda(MemLocationTypeNone)
#define cudaMemLocationTypeDevice	__cuda(MemLocationTypeDevice)
#define cudaMemLocationTypeHost	__cuda(MemLocationTypeHost)
#define cudaMemLocationTypeHostNuma	__cuda(MemLocationTypeHostNuma)
#define cudaMemLocationTypeHostNumaCurrent	__cuda(MemLocationTypeHostNumaCurrent)

#define cudaMemPool_t	__cuda(MemPool_t)
#define cudaMemPoolProps __cuda(MemPoolProps)

/**
 * cudaError_t cudaMemPoolCreate(cudaMemPool_t *memPool,
 *                               const struct cudaMemPoolProps *poolProps);
 */
#define cudaMemPoolCreate __cuda(MemPoolCreate)

/**
 * cudaError_t cudaMemPoolDestroy(cudaMemPool_t memPool);
 */
#define cudaMemPoolDestroy __cuda(MemPoolDestroy)

/**
 * CUDA V13.0.48
 * cudaError_t cudaDeviceGetDefaultMemPool(cudaMemPool_t *memPool, int device);
 *
 * HIP 6.4
 * hipError_t hipDeviceGetDefaultMemPool(hipMemPool_t* mem_pool, int device);
 */
#define cudaDeviceGetDefaultMemPool(pool, dev)	__cuda(DeviceGetDefaultMemPool(pool, dev))

/**
 * CUDA
 * cudaError_t cudaMemPoolTrimTo(cudaMemPool_t memPool, size_t minBytesToKeep);
 *
 * HIP
 * hipError_t hipMemPoolTrimTo(hipMemPool_t mem_pool, size_t min_bytes_to_hold);
 */
#define cudaMemPoolTrimTo(p, b)	__cuda(MemPoolTrimTo(p, b))

#if defined(__USE_HIP__) || defined(__USE_LUCA__) || defined(__USE_HPCC__)
#define cudaPointerAttributes	__cuda(PointerAttribute_t) /* for HIP */
#else
#define cudaPointerAttributes	__cuda(PointerAttributes)
#endif
/**
 * CUDA V13.0
 * cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *attributes, const void *ptr);
 *
 * HIP 6.4
 * hipError_t hipPointerGetAttributes(hipPointerAttribute_t* attributes, const void* ptr);
 *
 * LUCA 3.1.3
 * hcError_t hcPointerGetAttributes(hcPointerAttribute_t *attributes, const void *ptr);
 */
#define cudaPointerGetAttributes(a, p)	__cuda(PointerGetAttributes(a, p))

/**
 * CUDA: typedef __attribute__((device_builtin)) struct CUevent_st *cudaEvent_t;
 * HPCC: typedef struct HCevent_st *hcEvent_t;
 * HIP: typedef struct ihipEvent_t* hipEvent_t;
 */
#ifdef __USE_HIP__
#define CUevent_st	ihipEvent_t
#else
#define CUevent_st	__CU(event_st)
#endif
#define cudaEvent_t	__cuda(Event_t)
#define cudaEventCreate(pe)	__cuda(EventCreate(pe))
#define cudaEventCreateWithFlags(pe, f)	__cuda(EventCreateWithFlags(pe, f))
#define cudaEventDestroy(ev)	__cuda(EventDestroy(ev))
/**
 * cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
 */
#define cudaEventRecord(ev, stream)	__cuda(EventRecord(ev, stream))
#define cudaEventElapsedTime(pt, start, stop)	__cuda(EventElapsedTime(pt, start, stop))
/**
 * cudaEventSynchronize() will block the CPU until the CPU waits for the GPU
 * calculation to complete the event 'ev'.
 */
#define cudaEventSynchronize(ev)	__cuda(EventSynchronize(ev))

/**
 * CUDA 13.0
 * cudaError_t cudaEventQuery(cudaEvent_t event);
 *
 * HIP 6.4
 * hipError_t hipEventQuery(hipEvent_t event);
 */
#define cudaEventQuery	__cuda(EventQuery)

/**
 * cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim,
 *                              void **args, size_t sharedMem, cudaStream_t stream);
 * hcError_t hcLaunchKernel(const void *function_address, dim3 numBlocks, dim3 dimBlocks,
 *                          void **args, size_t sharedMemBytes, hcStream_t stream);
 */
#define cudaLaunchKernel(func, g, b, args, mem, stream) \
	__cuda(LaunchKernel(func, g, b, args, mem, stream))

/**
 * cudaError_t cudaLaunchDevice(void *func, void *parameterBuffer,
 *                              dim3 gridDimension, dim3 blockDimension,
 *                              unsigned int sharedMemSize, cudaStream_t stream);
 */
#define cudaLaunchDevice __cuda(LaunchDevice)

/**
 * CUDA 13
 * CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX,
 *                         unsigned int gridDimY, unsigned int gridDimZ,
 *                         unsigned int blockDimX, unsigned int blockDimY,
 *                         unsigned int blockDimZ, unsigned int sharedMemBytes,
 *                         CUstream hStream, void **kernelParams, void **extra);
 *
 * LUCA:
 * lcError_t lcLaunchKernel(const void *function_address, dim3 numBlocks,
 *                          dim3 dimBlocks, void **args,
 */
#define cuLaunchKernel __cu(LaunchKernel)

/**
 * CUDA 12/13:
 * don't have nvModuleLaunchKernel, cudaModuleLaunchKernel, cuModuleLaunchKernel
 * but cuLaunchKernel looks like hipModuleLaunchKernel.
 *
 * HIP:
 * hipError_t hipModuleLaunchKernel(hipFunction_t f,
 *                                  unsigned int gridDimX, unsigned int gridDimY,
 *                                  unsigned int gridDimZ, unsigned int blockDimX,
 *                                  unsigned int blockDimY, unsigned int blockDimZ,
 *                                  unsigned int sharedMemBytes, hipStream_t stream,
 *                                  void** kernelParams, void** extra);
 *
 * LUCA:
 * lcError_t lcModuleLaunchKernel(lcFunction_t f,
 *                                unsigned int gridDimX, unsigned int gridDimY,
 *                                unsigned int gridDimZ, unsigned int blockDimX,
 *                                unsigned int blockDimY, unsigned int blockDimZ,
 *                                unsigned int sharedMemBytes, lcStream_t hStream,
 *                                void **kernelParams, void **extra);
 */
#define hipModuleLaunchKernel __cu(ModuleLaunchKernel)

/**
 * HPCC 3.0.0:
 * hcError_t hcLaunchCooperativeKernel(const void *f, dim3 gridDim, dim3 blockDim,
 *                                     void **kernelParams, unsigned int sharedMemBytes,
 *                                     hcStream_t stream);
 *
 * CUDA V13.0.48:
 * cudaError_t cudaLaunchCooperativeKernel(const void *func, dim3 gridDim, dim3 blockDim,
 *                                         void **args, size_t sharedMem,
 *                                         cudaStream_t stream);
 */
#define cudaLaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, stream) \
	__cuda(LaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, stream))

/**
 * CUDA 13.0
 * cudaError_t cudaLaunchHostFunc(cudaStream_t stream, cudaHostFn_t fn, void *userData);
 *
 * HIP 6.4
 * hipError_t hipLaunchHostFunc(hipStream_t stream, hipHostFn_t fn, void* userData);
 */
#define cudaLaunchHostFunc	__cuda(LaunchHostFunc)

#define cudaFuncAttributes	__cuda(FuncAttributes)
#define cudaFuncAttribute	__cuda(FuncAttribute)
/**
 * CUDA V13.0
 * cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const void *func);
 *
 * HIP 6.4
 * hipError_t hipFuncGetAttributes(struct hipFuncAttributes* attr, const void* func);
 */
#define cudaFuncGetAttributes(a, f)	__cuda(FuncGetAttributes(a, f))

/**
 * CUDA V13.0
 * cudaError_t cudaFuncSetAttribute(T *func, enum cudaFuncAttribute a, int value);
 *
 * HIP 6.4
 * hipError_t hipFuncSetAttribute(const void* func, hipFuncAttribute attr, int value);
 */
#define cudaFuncSetAttribute(f, a, v)	__cuda(FuncSetAttribute(f, a, v))

/**
 * cudaError_t cudaGetFuncBySymbol(cudaFunction_t* functionPtr, const void* symbolPtr);
 */
#define cudaGetFuncBySymbol __cuda(GetFuncBySymbol)

/**
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
/**
 * CUDA: typedef __device_builtin__ struct CUstream_st *cudaStream_t;
 */
#define CUstream_st	__CU(stream_st)
/**
 * CUDA: typedef struct CUstream_st *CUstream;
 * LUCA: typedef struct LCstream_st *lcStream_t;
 */
#define cudaStream_t	__cuda(Stream_t)
#define cudaStreamCreate(pstream)	__cuda(StreamCreate(pstream))
#define cudaStreamCreateWithFlags(s, f)	__cuda(StreamCreateWithFlags(s, f))
/**
 * cudaStreamCreateWithFlags()'s flags
 */
#define cudaStreamDefault	__cuda(StreamDefault)
#define cudaStreamNonBlocking	__cuda(StreamNonBlocking)

#define cudaStreamSynchronize(stream)	__cuda(StreamSynchronize(stream))
#define cudaStreamDestroy(stream)	__cuda(StreamDestroy(stream))
/**
 * CUDA V13.0:
 * cudaError_t CUDARTAPI cudaStreamQuery(cudaStream_t stream);
 *
 * HIP 6.4
 * hipError_t hipStreamQuery(hipStream_t stream);
 */
#define cudaStreamQuery(s)	__cuda(StreamQuery(s))

#define cudaStreamBeginCapture __cuda(StreamBeginCapture)
#define cudaStreamEndCapture __cuda(StreamEndCapture)

/**
 * CUDA 12
 * cudaError_t cudaStreamIsCapturing(cudaStream_t stream,
 *                                   cudaStreamCaptureStatus *pCaptureStatus);
 *
 * HIP
 * hipError_t hipStreamIsCapturing(hipStream_t stream,
 *                                 hipStreamCaptureStatus* pCaptureStatus);
 *
 * HPCC
 * hcError_t hcStreamIsCapturing(hcStream_t stream,
 *                               hcStreamCaptureStatus *pCaptureStatus);
 */
#define cudaStreamIsCapturing(stream, pCaptureStatus)	\
	__cuda(StreamIsCapturing(stream, pCaptureStatus))

/**
 * LUCA:
 * lcError_t lcStreamCopyAttributes(lcStream_t dst, lcStream_t src);
 */
#define cudaStreamCopyAttributes	__cuda(StreamCopyAttributes)

#define cudaStreamAttrID	__cuda(StreamAttrID)
#define cudaStreamAttributeAccessPolicyWindow	__cuda(StreamAttributeAccessPolicyWindow)
#define cudaStreamAttributeSynchronizationPolicy	__cuda(StreamAttributeSynchronizationPolicy)
#define cudaStreamAttributeMemSyncDomainMap	__cuda(StreamAttributeMemSyncDomainMap)
#define cudaStreamAttributeMemSyncDomain	__cuda(StreamAttributeMemSyncDomain)
#define cudaStreamAttributePriority	__cuda(StreamAttributePriority)

/**
 * LUCA:
 * lcError_t lcStreamGetAttribute(lcStream_t hStream, lcStreamAttrID attr,
 *                                lcStreamAttrValue *value_out);
 */
#define cudaStreamGetAttribute	__cuda(StreamGetAttribute)

/**
 * LUCA:
 * lcError_t lcStreamSetAttribute(lcStream_t hStream, lcStreamAttrID attr,
 *                                const lcStreamAttrValue *value);
 */
#define cudaStreamSetAttribute	__cuda(StreamSetAttribute)

/**
 * LUCA:
 * lcError_t lcStreamGetPriority(lcStream_t hStream, int *priority);
 */
#define cudaStreamGetPriority	__cuda(StreamGetPriority)

/**
 * LUCA:
 * lcError_t lcStreamGetFlags(lcStream_t hStream, unsigned int *flags);
 */
#define cudaStreamGetFlags	__cuda(StreamGetFlags)

/**
 * CUDA 13
 * cudaError_t cudaStreamAddCallback(cudaStream_t stream, cudaStreamCallback_t callback,
 *                                   void *userData, unsigned int flags);
 */
#define cudaStreamAddCallback	__cuda(StreamAddCallback)

/**
 * CUDA V13.0
 * cudaError_t cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipStreamWaitEvent(hipStream_t stream, hipEvent_t event, unsigned int flags);
 */
#define cudaStreamWaitEvent(s, e, f)	__cuda(StreamWaitEvent(s, e, f))

#define cudaStreamCaptureStatus	__cuda(StreamCaptureStatus)

#define cudaGraph_t		__cuda(Graph_t)
#define cudaGraphNode_t		__cuda(GraphNode_t)
#define cudaGraphExec_t		__cuda(GraphExec_t)
#define cudaGraphEdgeData	__cuda(GraphEdgeData)

#define cudaMemAllocNodeParams	__cuda(MemAllocNodeParams)
#define cudaMemAllocationTypeInvalid	__cuda(MemAllocationTypeInvalid) /* 0 */
#define cudaMemAllocationTypePinned	__cuda(MemAllocationTypePinned) /* 1 */
#define cudaMemAllocationTypeManaged	__cuda(MemAllocationTypeManaged) /* 2 */
#define cudaMemAllocationTypeMax	__cuda(MemAllocationTypeMax) /* 0x7FFFFFFF */

/**
 * CUDA 13
 * cudaError_t cudaGraphCreate(cudaGraph_t *pGraph, unsigned int flags);
 *
 * LUCA
 * lcError_t lcGraphCreate(lcGraph_t *pGraph, unsigned int flags);
 * lcError_t lcGraphDestroy(lcGraph_t graph);
 */
#define cudaGraphCreate	__cuda(GraphCreate)
#define cudaGraphDestroy	__cuda(GraphDestroy)

/**
 * CUDA:
 * #if __CUDART_API_VERSION >= 11010
 * cudaError_t cudaGraphAddMemcpyNode1D(cudaGraphNode_t *pGraphNode, cudaGraph_t graph,
 *                                      const cudaGraphNode_t *pDependencies, size_t numDependencies,
 *                                      void* dst, const void* src, size_t count, enum cudaMemcpyKind kind);
 * #endif
 *
 * LUCA
 * lcError_t lcGraphAddMemcpyNode1D(lcGraphNode_t *pGraphNode, lcGraph_t graph,
 *                                  const lcGraphNode_t *pDependencies, size_t numDependencies,
 *                                  void *dst, const void *src, size_t count, lcMemcpyKind kind);
 */
#define cudaGraphAddMemcpyNode1D	__cuda(GraphAddMemcpyNode1D)

#define cudaGraphAddMemAllocNode __cuda(GraphAddMemAllocNode)
#define cudaGraphAddMemFreeNode __cuda(GraphAddMemFreeNode)

#define cudaGraphInstantiate __cuda(GraphInstantiate)
#define cudaGraphExecDestroy __cuda(GraphExecDestroy)
#define cudaGraphLaunch __cuda(GraphLaunch)

/**
 * CUDA 13.0
 * cudaError_t cudaStreamGetCaptureInfo(cudaStream_t stream,
 *                                      enum cudaStreamCaptureStatus *captureStatus_out,
 *                                      unsigned long long *id_out __dv(0),
 *                                      cudaGraph_t *graph_out __dv(0),
 *                                      const cudaGraphNode_t **dependencies_out __dv(0),
 *                                      const cudaGraphEdgeData **edgeData_out __dv(0),
 *                                      size_t *numDependencies_out __dv(0));
 * cudaError_t cudaStreamGetCaptureInfo_ptsz(...);
 *
 * HIP 6.4
 * hipError_t hipStreamGetCaptureInfo(hipStream_t stream,
 *                                    hipStreamCaptureStatus* pCaptureStatus,
 *                                    unsigned long long* pId);
 * hipError_t hipStreamGetCaptureInfo_v2(hipStream_t stream,
 *                                       hipStreamCaptureStatus* captureStatus_out,
 *                                       unsigned long long* id_out,
 *                                       hipGraph_t* graph_out,
 *                                       const hipGraphNode_t** dependencies_out,
 *                                       size_t* numDependencies_out);
 * hipError_t hipStreamGetCaptureInfo_spt(hipStream_t stream,
 *                                        hipStreamCaptureStatus* pCaptureStatus,
 *                                        unsigned long long* pId);
 * hipError_t hipStreamGetCaptureInfo_v2_spt(hipStream_t stream,
 *                                           hipStreamCaptureStatus* captureStatus_out,
 *                                           unsigned long long* id_out,
 *                                           hipGraph_t* graph_out,
 *                                           const hipGraphNode_t** dependencies_out,
 *                                           size_t* numDependencies_out);
 *
 * LUCA 3.1.3
 * hcError_t hcStreamGetCaptureInfo(hcStream_t stream,
 *                                  hcStreamCaptureStatus *captureStatus_out,
 *                                  unsigned long long *id_out __dparm(0),
 *                                  hcGraph_t *graph_out __dparm(0),
 *                                  const hcGraphNode_t **dependencies_out __dparm(0),
 *                                  size_t *numDependencies_out __dparm(0));
 */
#define cudaStreamGetCaptureInfo	__cuda(StreamGetCaptureInfo)

/**
 * CUDA 13.0
 * cudaError_t cudaStreamUpdateCaptureDependencies(cudaStream_t stream, cudaGraphNode_t *dependencies,
 *                                                 const cudaGraphEdgeData *dependencyData,
 *                                                 size_t numDependencies, unsigned int flags __dv(0));
 *
 * HIP 6.4
 * hipError_t hipStreamUpdateCaptureDependencies(hipStream_t stream, hipGraphNode_t* dependencies,
 *                                               size_t numDependencies,
 *                                               unsigned int flags __dparm(0));
 *
 * HPCC 3.0.0
 * hcError_t hcStreamUpdateCaptureDependencies(hcStream_t stream, hcGraphNode_t *dependencies,
 *                                             size_t numDependencies, unsigned int flags __dparm(0));
 */
#define cudaStreamUpdateCaptureDependencies	__cuda(StreamUpdateCaptureDependencies)

#define cudaStreamCaptureMode	__cuda(StreamCaptureMode)
#define cudaStreamCaptureModeGlobal __cuda(StreamCaptureModeGlobal)
/**
 * CUDA 13.0
 * cudaError_t cudaThreadExchangeStreamCaptureMode(enum cudaStreamCaptureMode *mode);
 *
 * HIP 6.4
 * hipError_t hipThreadExchangeStreamCaptureMode(hipStreamCaptureMode* mode);
 */
#define cudaThreadExchangeStreamCaptureMode(m)	__cuda(ThreadExchangeStreamCaptureMode(m))

#define cudaUserObject_t	__cuda(UserObject_t)
#define cudaUserObjectFlags	__cuda(UserObjectFlags)
/* typedef void (*cudaHostFn_t)(void *userData); */
#define cudaHostFn_t	__cuda(HostFn_t)
/**
 * CUDA 13.0
 * cudaError_t cudaUserObjectCreate(cudaUserObject_t *object_out, T *objectToWrap,
 *                                  unsigned int initialRefcount, unsigned int flags);
 * cudaError_t cudaUserObjectCreate(cudaUserObject_t *object_out, T *objectToWrap,
 *                                  unsigned int initialRefcount, cudaUserObjectFlags flags);
 * cudaError_t cudaUserObjectCreate(cudaUserObject_t *object_out, void *ptr,
 *                                  cudaHostFn_t destroy,
 *                                  unsigned int initialRefcount, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipUserObjectCreate(hipUserObject_t* object_out, void* ptr,
 *                                hipHostFn_t destroy,
 *                                unsigned int initialRefcount, unsigned int flags);
 */
#define cudaUserObjectCreate	__cuda(UserObjectCreate)

/**
 * CUDA 13.0
 * cudaError_t cudaGraphRetainUserObject(cudaGraph_t graph, cudaUserObject_t object,
 *                                       unsigned int count __dv(1),
 *                                       unsigned int flags __dv(0));
 *
 * HIP 6.4
 * hipError_t hipGraphRetainUserObject(hipGraph_t graph, hipUserObject_t object,
 *                                     unsigned int count, unsigned int flags);
 */
#define cudaGraphRetainUserObject	__cuda(GraphRetainUserObject)

/**
 * CUDA 13.0
 * cudaError_t cudaGraphAddEventWaitNode(cudaGraphNode_t *pGraphNode,
 *                                       cudaGraph_t graph,
 *                                       const cudaGraphNode_t *pDependencies,
 *                                       size_t numDependencies,
 *                                       cudaEvent_t event);
 *
 * HIP 6.4
 * hipError_t hipGraphAddEventWaitNode(hipGraphNode_t* pGraphNode,
 *                                     hipGraph_t graph,
 *                                     const hipGraphNode_t* pDependencies,
 *                                     size_t numDependencies,
 *                                     hipEvent_t event);
 */
#define cudaGraphAddEventWaitNode	__cuda(GraphAddEventWaitNode)

/**
 * CUDA 13.0
 * cudaError_t cudaGraphAddEventRecordNode(cudaGraphNode_t *pGraphNode,
 *                                         cudaGraph_t graph,
 *                                         const cudaGraphNode_t *pDependencies,
 *                                         size_t numDependencies,
 *                                         cudaEvent_t event);
 *
 * HIP 6.4
 * hipError_t hipGraphAddEventRecordNode(hipGraphNode_t* pGraphNode,
 *                                       hipGraph_t graph,
 *                                       const hipGraphNode_t* pDependencies,
 *                                       size_t numDependencies,
 *                                       hipEvent_t event);
 */
#define cudaGraphAddEventRecordNode	__cuda(GraphAddEventRecordNode)

#define cudaHostNodeParams	__cuda(HostNodeParams)

/**
 * CUDA 13.0
 * cudaError_t cudaGraphAddHostNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph,
 *                                  const cudaGraphNode_t *pDependencies,
 *                                  size_t numDependencies,
 *                                  const struct cudaHostNodeParams *pNodeParams);
 *
 * HIP 6.4
 * hipError_t hipGraphAddHostNode(hipGraphNode_t* pGraphNode, hipGraph_t graph,
 *                                const hipGraphNode_t* pDependencies,
 *                                size_t numDependencies,
 *                                const hipHostNodeParams* pNodeParams);
 * hipError_t hipGraphAddHostNode(hipGraphNode_t* pGraphNode, hipGraph_t graph,
 *                                const hipGraphNode_t* pDependencies,
 *                                size_t numDependencies,
 *                                const hipHostNodeParams* pNodeParams);
 *
 * HPCC 3.0.0
 * hcError_t hcGraphAddHostNode(hcGraphNode_t *pGraphNode, hcGraph_t graph,
 *                              const hcGraphNode_t *pDependencies,
 *                              size_t numDependencies,
 *                              const hcHostNodeParams *pNodeParams);
 */
#define cudaGraphAddHostNode	__cuda(GraphAddHostNode)

#define cudaKernelNodeParams	__cuda(KernelNodeParams)
/**
 * CUDA 13.0
 * cudaError_t cudaGraphAddKernelNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph,
 *                                    const cudaGraphNode_t *pDependencies, size_t numDependencies,
 *                                    const struct cudaKernelNodeParams *pNodeParams);
 *
 * HIP 6.4
 * hipError_t hipGraphAddKernelNode(hipGraphNode_t* pGraphNode, hipGraph_t graph,
 *                                  const hipGraphNode_t* pDependencies, size_t numDependencies,
 *                                  const hipKernelNodeParams* pNodeParams);
 */
#define cudaGraphAddKernelNode	__cuda(GraphAddKernelNode)

/**
 * CUDA V13.0.48
 * CUresult cuDeviceGet(CUdevice *device, int ordinal);
 *
 * HIP
 * hipError_t hipDeviceGet(hipDevice_t*, int ordinal);
 *
 * HPCC 3.0.0
 * hcError_t hcDeviceGet(hcDevice_t *device, int ordinal);
 */
#define CUdevice	__CU(device)
#define cuDeviceGet(pdevice, dev_id)	__cu(DeviceGet(pdevice, dev_id))
#define cuDeviceComputeCapability(pmajor, pminor, pdev) \
	__cu(DeviceComputeCapability(pmajor, pminor, pdev))

/* CUresult */
#ifndef CUDA_SUCCESS
#define CUDA_SUCCESS	__CUDA_ERROR(SUCCESS);
#endif
#define CUDA_ERROR_INVALID_VALUE	__CUDA_ERROR(ERROR_INVALID_VALUE)
#define CUDA_ERROR_OUT_OF_MEMORY	__CUDA_ERROR(ERROR_OUT_OF_MEMORY)
#define CUDA_ERROR_NOT_INITIALIZED	__CUDA_ERROR(ERROR_NOT_INITIALIZED)
#define CUDA_ERROR_DEINITIALIZED	__CUDA_ERROR(ERROR_DEINITIALIZED)
#define CUDA_ERROR_PROFILER_DISABLED	__CUDA_ERROR(ERROR_PROFILER_DISABLED)
#define CUDA_ERROR_PROFILER_NOT_INITIALIZED	__CUDA_ERROR(ERROR_PROFILER_NOT_INITIALIZED)
#define CUDA_ERROR_PROFILER_ALREADY_STARTED	__CUDA_ERROR(ERROR_PROFILER_ALREADY_STARTED)
#define CUDA_ERROR_PROFILER_ALREADY_STOPPED	__CUDA_ERROR(ERROR_PROFILER_ALREADY_STOPPED)
#define CUDA_ERROR_STUB_LIBRARY	__CUDA_ERROR(ERROR_STUB_LIBRARY)
#define CUDA_ERROR_CALL_REQUIRES_NEWER_DRIVER	__CUDA_ERROR(ERROR_CALL_REQUIRES_NEWER_DRIVER)
#define CUDA_ERROR_DEVICE_UNAVAILABLE	__CUDA_ERROR(ERROR_DEVICE_UNAVAILABLE)
#define CUDA_ERROR_NO_DEVICE	__CUDA_ERROR(ERROR_NO_DEVICE)
#define CUDA_ERROR_INVALID_DEVICE	__CUDA_ERROR(ERROR_INVALID_DEVICE)
#define CUDA_ERROR_DEVICE_NOT_LICENSED	__CUDA_ERROR(ERROR_DEVICE_NOT_LICENSED)
#define CUDA_ERROR_INVALID_IMAGE	__CUDA_ERROR(ERROR_INVALID_IMAGE)
#define CUDA_ERROR_INVALID_CONTEXT	__CUDA_ERROR(ERROR_INVALID_CONTEXT)
#define CUDA_ERROR_CONTEXT_ALREADY_CURRENT	__CUDA_ERROR(ERROR_CONTEXT_ALREADY_CURRENT)
#define CUDA_ERROR_MAP_FAILED	__CUDA_ERROR(ERROR_MAP_FAILED)
#define CUDA_ERROR_UNMAP_FAILED	__CUDA_ERROR(ERROR_UNMAP_FAILED)
#define CUDA_ERROR_ARRAY_IS_MAPPED	__CUDA_ERROR(ERROR_ARRAY_IS_MAPPED)
#define CUDA_ERROR_ALREADY_MAPPED	__CUDA_ERROR(ERROR_ALREADY_MAPPED)
#define CUDA_ERROR_NO_BINARY_FOR_GPU	__CUDA_ERROR(ERROR_NO_BINARY_FOR_GPU)
#define CUDA_ERROR_ALREADY_ACQUIRED	__CUDA_ERROR(ERROR_ALREADY_ACQUIRED)
#define CUDA_ERROR_NOT_MAPPED	__CUDA_ERROR(ERROR_NOT_MAPPED)
#define CUDA_ERROR_NOT_MAPPED_AS_ARRAY	__CUDA_ERROR(ERROR_NOT_MAPPED_AS_ARRAY)
#define CUDA_ERROR_NOT_MAPPED_AS_POINTER	__CUDA_ERROR(ERROR_NOT_MAPPED_AS_POINTER)
#define CUDA_ERROR_ECC_UNCORRECTABLE	__CUDA_ERROR(ERROR_ECC_UNCORRECTABLE)
#define CUDA_ERROR_UNSUPPORTED_LIMIT	__CUDA_ERROR(ERROR_UNSUPPORTED_LIMIT)
#define CUDA_ERROR_CONTEXT_ALREADY_IN_USE	__CUDA_ERROR(ERROR_CONTEXT_ALREADY_IN_USE)
#define CUDA_ERROR_PEER_ACCESS_UNSUPPORTED	__CUDA_ERROR(ERROR_PEER_ACCESS_UNSUPPORTED)
#define CUDA_ERROR_INVALID_PTX	__CUDA_ERROR(ERROR_INVALID_PTX)
#define CUDA_ERROR_INVALID_GRAPHICS_CONTEXT	__CUDA_ERROR(ERROR_INVALID_GRAPHICS_CONTEXT)
#define CUDA_ERROR_NVLINK_UNCORRECTABLE	__CUDA_ERROR(ERROR_NVLINK_UNCORRECTABLE)
#define CUDA_ERROR_JIT_COMPILER_NOT_FOUND	__CUDA_ERROR(ERROR_JIT_COMPILER_NOT_FOUND)
#define CUDA_ERROR_UNSUPPORTED_PTX_VERSION	__CUDA_ERROR(ERROR_UNSUPPORTED_PTX_VERSION)
#define CUDA_ERROR_JIT_COMPILATION_DISABLED	__CUDA_ERROR(ERROR_JIT_COMPILATION_DISABLED)
#define CUDA_ERROR_UNSUPPORTED_EXEC_AFFINITY	__CUDA_ERROR(ERROR_UNSUPPORTED_EXEC_AFFINITY)
#define CUDA_ERROR_UNSUPPORTED_DEVSIDE_SYNC	__CUDA_ERROR(ERROR_UNSUPPORTED_DEVSIDE_SYNC)
#define CUDA_ERROR_CONTAINED	__CUDA_ERROR(ERROR_CONTAINED)
#define CUDA_ERROR_INVALID_SOURCE	__CUDA_ERROR(ERROR_INVALID_SOURCE)
#define CUDA_ERROR_FILE_NOT_FOUND	__CUDA_ERROR(ERROR_FILE_NOT_FOUND)
#define CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND	__CUDA_ERROR(ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND)
#define CUDA_ERROR_SHARED_OBJECT_INIT_FAILED	__CUDA_ERROR(ERROR_SHARED_OBJECT_INIT_FAILED)
#define CUDA_ERROR_OPERATING_SYSTEM	__CUDA_ERROR(ERROR_OPERATING_SYSTEM)
#define CUDA_ERROR_INVALID_HANDLE	__CUDA_ERROR(ERROR_INVALID_HANDLE)
#define CUDA_ERROR_ILLEGAL_STATE	__CUDA_ERROR(ERROR_ILLEGAL_STATE)
#define CUDA_ERROR_LOSSY_QUERY	__CUDA_ERROR(ERROR_LOSSY_QUERY)
#define CUDA_ERROR_NOT_FOUND	__CUDA_ERROR(ERROR_NOT_FOUND)
#define CUDA_ERROR_NOT_READY	__CUDA_ERROR(ERROR_NOT_READY)
#define CUDA_ERROR_ILLEGAL_ADDRESS	__CUDA_ERROR(ERROR_ILLEGAL_ADDRESS)
#define CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES	__CUDA_ERROR(ERROR_LAUNCH_OUT_OF_RESOURCES)
#define CUDA_ERROR_LAUNCH_TIMEOUT	__CUDA_ERROR(ERROR_LAUNCH_TIMEOUT)
#define CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING	__CUDA_ERROR(ERROR_LAUNCH_INCOMPATIBLE_TEXTURING)
#define CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED	__CUDA_ERROR(ERROR_PEER_ACCESS_ALREADY_ENABLED)
#define CUDA_ERROR_PEER_ACCESS_NOT_ENABLED	__CUDA_ERROR(ERROR_PEER_ACCESS_NOT_ENABLED)
#define CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE	__CUDA_ERROR(ERROR_PRIMARY_CONTEXT_ACTIVE)
#define CUDA_ERROR_CONTEXT_IS_DESTROYED	__CUDA_ERROR(ERROR_CONTEXT_IS_DESTROYED)
#define CUDA_ERROR_ASSERT	__CUDA_ERROR(ERROR_ASSERT)
#define CUDA_ERROR_TOO_MANY_PEERS	__CUDA_ERROR(ERROR_TOO_MANY_PEERS)
#define CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED	__CUDA_ERROR(ERROR_HOST_MEMORY_ALREADY_REGISTERED)
#define CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED	__CUDA_ERROR(ERROR_HOST_MEMORY_NOT_REGISTERED)
#define CUDA_ERROR_HARDWARE_STACK_ERROR	__CUDA_ERROR(ERROR_HARDWARE_STACK_ERROR)
#define CUDA_ERROR_ILLEGAL_INSTRUCTION	__CUDA_ERROR(ERROR_ILLEGAL_INSTRUCTION)
#define CUDA_ERROR_MISALIGNED_ADDRESS	__CUDA_ERROR(ERROR_MISALIGNED_ADDRESS)
#define CUDA_ERROR_INVALID_ADDRESS_SPACE	__CUDA_ERROR(ERROR_INVALID_ADDRESS_SPACE)
#define CUDA_ERROR_INVALID_PC	__CUDA_ERROR(ERROR_INVALID_PC)
#define CUDA_ERROR_LAUNCH_FAILED	__CUDA_ERROR(ERROR_LAUNCH_FAILED)
#define CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE	__CUDA_ERROR(ERROR_COOPERATIVE_LAUNCH_TOO_LARGE)
#define CUDA_ERROR_TENSOR_MEMORY_LEAK	__CUDA_ERROR(ERROR_TENSOR_MEMORY_LEAK)
#define CUDA_ERROR_NOT_PERMITTED	__CUDA_ERROR(ERROR_NOT_PERMITTED)
#define CUDA_ERROR_NOT_SUPPORTED	__CUDA_ERROR(ERROR_NOT_SUPPORTED)
#define CUDA_ERROR_SYSTEM_NOT_READY	__CUDA_ERROR(ERROR_SYSTEM_NOT_READY)
#define CUDA_ERROR_SYSTEM_DRIVER_MISMATCH	__CUDA_ERROR(ERROR_SYSTEM_DRIVER_MISMATCH)
#define CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE	__CUDA_ERROR(ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE)
#define CUDA_ERROR_MPS_CONNECTION_FAILED	__CUDA_ERROR(ERROR_MPS_CONNECTION_FAILED)
#define CUDA_ERROR_MPS_RPC_FAILURE	__CUDA_ERROR(ERROR_MPS_RPC_FAILURE)
#define CUDA_ERROR_MPS_SERVER_NOT_READY	__CUDA_ERROR(ERROR_MPS_SERVER_NOT_READY)
#define CUDA_ERROR_MPS_MAX_CLIENTS_REACHED	__CUDA_ERROR(ERROR_MPS_MAX_CLIENTS_REACHED)
#define CUDA_ERROR_MPS_MAX_CONNECTIONS_REACHED	__CUDA_ERROR(ERROR_MPS_MAX_CONNECTIONS_REACHED)
#define CUDA_ERROR_MPS_CLIENT_TERMINATED	__CUDA_ERROR(ERROR_MPS_CLIENT_TERMINATED)
#define CUDA_ERROR_CDP_NOT_SUPPORTED	__CUDA_ERROR(ERROR_CDP_NOT_SUPPORTED)
#define CUDA_ERROR_CDP_VERSION_MISMATCH	__CUDA_ERROR(ERROR_CDP_VERSION_MISMATCH)
#define CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED	__CUDA_ERROR(ERROR_STREAM_CAPTURE_UNSUPPORTED)
#define CUDA_ERROR_STREAM_CAPTURE_INVALIDATED	__CUDA_ERROR(ERROR_STREAM_CAPTURE_INVALIDATED)
#define CUDA_ERROR_STREAM_CAPTURE_MERGE	__CUDA_ERROR(ERROR_STREAM_CAPTURE_MERGE)
#define CUDA_ERROR_STREAM_CAPTURE_UNMATCHED	__CUDA_ERROR(ERROR_STREAM_CAPTURE_UNMATCHED)
#define CUDA_ERROR_STREAM_CAPTURE_UNJOINED	__CUDA_ERROR(ERROR_STREAM_CAPTURE_UNJOINED)
#define CUDA_ERROR_STREAM_CAPTURE_ISOLATION	__CUDA_ERROR(ERROR_STREAM_CAPTURE_ISOLATION)
#define CUDA_ERROR_STREAM_CAPTURE_IMPLICIT	__CUDA_ERROR(ERROR_STREAM_CAPTURE_IMPLICIT)
#define CUDA_ERROR_CAPTURED_EVENT	__CUDA_ERROR(ERROR_CAPTURED_EVENT)
#define CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD	__CUDA_ERROR(ERROR_STREAM_CAPTURE_WRONG_THREAD)
#define CUDA_ERROR_TIMEOUT	__CUDA_ERROR(ERROR_TIMEOUT)
#define CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE	__CUDA_ERROR(ERROR_GRAPH_EXEC_UPDATE_FAILURE)
#define CUDA_ERROR_EXTERNAL_DEVICE	__CUDA_ERROR(ERROR_EXTERNAL_DEVICE)
#define CUDA_ERROR_INVALID_CLUSTER_SIZE	__CUDA_ERROR(ERROR_INVALID_CLUSTER_SIZE)
#define CUDA_ERROR_FUNCTION_NOT_LOADED	__CUDA_ERROR(ERROR_FUNCTION_NOT_LOADED)
#define CUDA_ERROR_INVALID_RESOURCE_TYPE	__CUDA_ERROR(ERROR_INVALID_RESOURCE_TYPE)
#define CUDA_ERROR_INVALID_RESOURCE_CONFIGURATION	__CUDA_ERROR(ERROR_INVALID_RESOURCE_CONFIGURATION)
#define CUDA_ERROR_KEY_ROTATION	__CUDA_ERROR(ERROR_KEY_ROTATION)
#define CUDA_ERROR_UNKNOWN	__CUDA_ERROR(ERROR_UNKNOWN)

#define cudaGetDeviceCount(pgpus)	__cuda(GetDeviceCount(pgpus))
#define cudaGetDevice(p_id)	__cuda(GetDevice(p_id))
#define cudaSetDevice(dev_id)	__cuda(SetDevice(dev_id))

#define cudaDeviceProp	__cuda(DeviceProp_t)
/**
 * CUDA V12.2.140 cuda_runtime_api.h
 * #define cudaGetDeviceProperties cudaGetDeviceProperties_v2
 * cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device);
 *
 * HIP
 * hipError_t hipGetDeviceProperties(hipDeviceProp_t* prop, int deviceId);
 */
#if defined(__USE_HPCC__) || defined(__USE_LUCA__) || defined(__USE_HIP__)
#define cudaGetDeviceProperties(prop, devid)	__cuda(GetDeviceProperties(prop, devid))
#else
#define cudaGetDeviceProperties(prop, devid)	__cuda(GetDeviceProperties_v2(prop, devid))
#endif

/**
 * HIP 5.7.31921-0
 * hipError_t hipDeviceGetAttribute(int *value, hipDeviceAttribute_t attr,
 *                                  int dev_id);
 */
#define cudaDeviceGetAttribute(pval, attr, dev_id)	__cuda(DeviceGetAttribute(pval, attr, dev_id))
#if defined(__USE_HPCC__) || defined(__USE_LUCA__) || defined(__USE_HIP__)
/* WARNING: different name */
/**
 * CUDA 13.0.0: enum __device_builtin__ cudaDeviceAttr
 * HIP: typedef enum hipDeviceAttribute_t {} hipDeviceAttribute_t;
 */
#define cudaDeviceAttr	__cuda(DeviceAttribute_t)
#define cudaDevAttrMaxThreadsPerBlock	__cuda(DeviceAttributeMaxThreadsPerBlock)
#define cudaDevAttrMaxBlockDimX	__cuda(DeviceAttributeMaxBlockDimX)
#define cudaDevAttrMaxBlockDimY	__cuda(DeviceAttributeMaxBlockDimY)
#define cudaDevAttrMaxBlockDimZ	__cuda(DeviceAttributeMaxBlockDimZ)
#define cudaDevAttrMaxGridDimX	__cuda(DeviceAttributeMaxGridDimX)
#define cudaDevAttrMaxGridDimY	__cuda(DeviceAttributeMaxGridDimY)
#define cudaDevAttrMaxGridDimZ	__cuda(DeviceAttributeMaxGridDimZ)
#define cudaDevAttrMaxSharedMemoryPerBlock	__cuda(DeviceAttributeMaxSharedMemoryPerBlock)
#define cudaDevAttrTotalConstantMemory	__cuda(DeviceAttributeTotalConstantMemory)
#define cudaDevAttrWarpSize	__cuda(DeviceAttributeWarpSize)
#define cudaDevAttrMaxPitch	__cuda(DeviceAttributeMaxPitch)
#define cudaDevAttrMaxRegistersPerBlock	__cuda(DeviceAttributeMaxRegistersPerBlock)
#define cudaDevAttrClockRate	__cuda(DeviceAttributeClockRate)
#define cudaDevAttrTextureAlignment	__cuda(DeviceAttributeTextureAlignment)
#define cudaDevAttrGpuOverlap	__cuda(DeviceAttributeGpuOverlap)
#define cudaDevAttrMultiProcessorCount	__cuda(DeviceAttributeMultiProcessorCount)
#define cudaDevAttrKernelExecTimeout	__cuda(DeviceAttributeKernelExecTimeout)
#define cudaDevAttrIntegrated	__cuda(DeviceAttributeIntegrated)
#define cudaDevAttrCanMapHostMemory	__cuda(DeviceAttributeCanMapHostMemory)
#define cudaDevAttrComputeMode	__cuda(DeviceAttributeComputeMode)
#define cudaDevAttrMaxTexture1DWidth	__cuda(DeviceAttributeMaxTexture1DWidth)
#define cudaDevAttrMaxTexture2DWidth	__cuda(DeviceAttributeMaxTexture2DWidth)
#define cudaDevAttrMaxTexture2DHeight	__cuda(DeviceAttributeMaxTexture2DHeight)
#define cudaDevAttrMaxTexture3DWidth	__cuda(DeviceAttributeMaxTexture3DWidth)
#define cudaDevAttrMaxTexture3DHeight	__cuda(DeviceAttributeMaxTexture3DHeight)
#define cudaDevAttrMaxTexture3DDepth	__cuda(DeviceAttributeMaxTexture3DDepth)
#define cudaDevAttrMaxTexture2DLayeredWidth	__cuda(DeviceAttributeMaxTexture2DLayeredWidth)
#define cudaDevAttrMaxTexture2DLayeredHeight	__cuda(DeviceAttributeMaxTexture2DLayeredHeight)
#define cudaDevAttrMaxTexture2DLayeredLayers	__cuda(DeviceAttributeMaxTexture2DLayeredLayers)
#define cudaDevAttrSurfaceAligement	__cuda(DeviceAttributeSurfaceAligement)
#define cudaDevAttrConcurrentKernels	__cuda(DeviceAttributeConcurrentKernels)
#define cudaDevAttrEccEnabled	__cuda(DeviceAttributeEccEnabled)
#define cudaDevAttrPciBusId	__cuda(DeviceAttributePciBusId)
#define cudaDevAttrPciDeviceId	__cuda(DeviceAttributePciDeviceId)
#define cudaDevAttrTccDriver	__cuda(DeviceAttributeTccDriver)
#define cudaDevAttrMemoryClockRate	__cuda(DeviceAttributeMemoryClockRate)
#define cudaDevAttrMemoryBusWidth	__cuda(DeviceAttributeMemoryBusWidth)
#define cudaDevAttrL2CacheSize	__cuda(DeviceAttributeL2CacheSize)
#define cudaDevAttrMaxThreadsPerMultiProcessor	__cuda(DeviceAttributeMaxThreadsPerMultiProcessor)
#define cudaDevAttrAsyncEngineCount	__cuda(DeviceAttributeAsyncEngineCount)
#define cudaDevAttrUnifiedAddressing	__cuda(DeviceAttributeUnifiedAddressing)
#define cudaDevAttrMaxTexture1DLayeredWidth	__cuda(DeviceAttributeMaxTexture1DLayeredWidth)
#define cudaDevAttrMaxTexture1DLayeredLayers	__cuda(DeviceAttributeMaxTexture1DLayeredLayers)
#define cudaDevAttrResvered44	__cuda(DeviceAttributeResvered44)
#define cudaDevAttrMaxTexture2DGatherWidth	__cuda(DeviceAttributeMaxTexture2DGatherWidth)
#define cudaDevAttrMaxTexture2DGatherHeight	__cuda(DeviceAttributeMaxTexture2DGatherHeight)
#define cudaDevAttrMaxTexture3DWidthAlt	__cuda(DeviceAttributeMaxTexture3DWidthAlt)
#define cudaDevAttrMaxTexture3DHeightAlt	__cuda(DeviceAttributeMaxTexture3DHeightAlt)
#define cudaDevAttrMaxTexture3DDepthAlt	__cuda(DeviceAttributeMaxTexture3DDepthAlt)
#define cudaDevAttrPciDomainId	__cuda(DeviceAttributePciDomainId)
#define cudaDevAttrTexturePitchAlignment	__cuda(DeviceAttributeTexturePitchAlignment)
#define cudaDevAttrMaxTextureCubemapWidth	__cuda(DeviceAttributeMaxTextureCubemapWidth)
#define cudaDevAttrMaxTextureCubemapLayeredWidth	__cuda(DeviceAttributeMaxTextureCubemapLayeredWidth)
#define cudaDevAttrMaxTextureCubemapLayeredLayers	__cuda(DeviceAttributeMaxTextureCubemapLayeredLayers)
#define cudaDevAttrMaxSurface1DWidth	__cuda(DeviceAttributeMaxSurface1DWidth)
#define cudaDevAttrMaxSurface2DWidth	__cuda(DeviceAttributeMaxSurface2DWidth)
#define cudaDevAttrMaxSurface2DHeight	__cuda(DeviceAttributeMaxSurface2DHeight)
#define cudaDevAttrMaxSurface3DWidth	__cuda(DeviceAttributeMaxSurface3DWidth)
#define cudaDevAttrMaxSurface3DHeight	__cuda(DeviceAttributeMaxSurface3DHeight)
#define cudaDevAttrMaxSurface3DDepth	__cuda(DeviceAttributeMaxSurface3DDepth)
#define cudaDevAttrMaxSurface1DLayeredWidth	__cuda(DeviceAttributeMaxSurface1DLayeredWidth)
#define cudaDevAttrMaxSurface1DLayeredLayers	__cuda(DeviceAttributeMaxSurface1DLayeredLayers)
#define cudaDevAttrMaxSurface2DLayeredWidth	__cuda(DeviceAttributeMaxSurface2DLayeredWidth)
#define cudaDevAttrMaxSurface2DLayeredHeight	__cuda(DeviceAttributeMaxSurface2DLayeredHeight)
#define cudaDevAttrMaxSurface2DLayeredLayers	__cuda(DeviceAttributeMaxSurface2DLayeredLayers)
#define cudaDevAttrMaxSurfaceCubemapWidth	__cuda(DeviceAttributeMaxSurfaceCubemapWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredWidth	__cuda(DeviceAttributeMaxSurfaceCubemapLayeredWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredLayers	__cuda(DeviceAttributeMaxSurfaceCubemapLayeredLayers)
#define cudaDevAttrTexture1DLinearWidth	__cuda(DeviceAttributeTexture1DLinearWidth)
#define cudaDevAttrTexture2DLinearWidth	__cuda(DeviceAttributeTexture2DLinearWidth)
#define cudaDevAttrTexture2DLinearHeight	__cuda(DeviceAttributeTexture2DLinearHeight)
#define cudaDevAttrTexture2DLinearPitch	__cuda(DeviceAttributeTexture2DLinearPitch)
#define cudaDevAttrMaxTexture2DMipmappedWidth	__cuda(DeviceAttributeMaxTexture2DMipmappedWidth)
#define cudaDevAttrMaxTexture2DMipmappedHeight	__cuda(DeviceAttributeMaxTexture2DMipmappedHeight)
#define cudaDevAttrComputeCapabilityMajor	__cuda(DeviceAttributeComputeCapabilityMajor)
#define cudaDevAttrComputeCapabilityMinor	__cuda(DeviceAttributeComputeCapabilityMinor)
#define cudaDevAttrStreamPrioritiesSupported	__cuda(DeviceAttributeStreamPrioritiesSupported)
#define cudaDevAttrGlobalL1CacheSupported	__cuda(DeviceAttributeGlobalL1CacheSupported)
#define cudaDevAttrLocalL1CacheSupported	__cuda(DeviceAttributeLocalL1CacheSupported)
#define cudaDevAttrMaxSharedMemoryPerMultiprocessor	__cuda(DeviceAttributeMaxSharedMemoryPerMultiprocessor)
#define cudaDevAttrMaxRegistersPerMultiprocessor	__cuda(DeviceAttributeMaxRegistersPerMultiprocessor)
#define cudaDevAttrManagedMemory	__cuda(DeviceAttributeManagedMemory)
#define cudaDevAttrIsMultiGpuBoard	__cuda(DeviceAttributeIsMultiGpuBoard)
#define cudaDevAttrMultiGpuBoardGroupID	__cuda(DeviceAttributeMultiGpuBoardGroupID)
#define cudaDevAttrHostNativeAtomicSupported	__cuda(DeviceAttributeHostNativeAtomicSupported)
#define cudaDevAttrSingleToDoublePrecisionPerfRatio	__cuda(DeviceAttributeSingleToDoublePrecisionPerfRatio)
#define cudaDevAttrPageableMemoryAccess	__cuda(DeviceAttributePageableMemoryAccess)
#define cudaDevAttrConcurrentManagedAccess	__cuda(DeviceAttributeConcurrentManagedAccess)
#define cudaDevAttrComputePreemptionSupported	__cuda(DeviceAttributeComputePreemptionSupported)
#define cudaDevAttrCanUseHostPointerForRegisteredMem	__cuda(DeviceAttributeCanUseHostPointerForRegisteredMem)
#define cudaDevAttrReserved92	__cuda(DeviceAttributeReserved92)
#define cudaDevAttrReserved93	__cuda(DeviceAttributeReserved93)
#define cudaDevAttrReserved94	__cuda(DeviceAttributeReserved94)
#define cudaDevAttrCooperativeLaunch	__cuda(DeviceAttributeCooperativeLaunch)
#define cudaDevAttrCooperativeMultiDeviceLaunch	__cuda(DeviceAttributeCooperativeMultiDeviceLaunch)
#define cudaDevAttrMaxSharedMemoryPerBlockOptin	__cuda(DeviceAttributeMaxSharedMemoryPerBlockOptin)
#define cudaDevAttrCanFlushRemoteWrites	__cuda(DeviceAttributeCanFlushRemoteWrites)
#define cudaDevAttrHostRegisterSupported	__cuda(DeviceAttributeHostRegisterSupported)
#define cudaDevAttrPageableMemoryAccessUsesHostPageTables	__cuda(DeviceAttributePageableMemoryAccessUsesHostPageTables)
#define cudaDevAttrDirectManagedMemAccessFromHost	__cuda(DeviceAttributeDirectManagedMemAccessFromHost)
#define cudaDevAttrReserved102	__cuda(DeviceAttributeReserved102)
#define cudaDevAttrReserved103	__cuda(DeviceAttributeReserved103)
#define cudaDevAttrReserved104	__cuda(DeviceAttributeReserved104)
#define cudaDevAttrReserved105	__cuda(DeviceAttributeReserved105)
#define cudaDevAttrReserved107	__cuda(DeviceAttributeReserved107)
#define cudaDevAttrMaxPersistingL2CacheSize	__cuda(DeviceAttributeMaxPersistingL2CacheSize)
#define cudaDevAttrMaxAccessPolicyWindowSize	__cuda(DeviceAttributeMaxAccessPolicyWindowSize)
#define cudaDevAttrReserved110	__cuda(DeviceAttributeReserved110)
#define cudaDevAttrReservedSharedMemoryPerBlock	__cuda(DeviceAttributeReservedSharedMemoryPerBlock)
#define cudaDevAttrSparseCudaArraySupported	__cuda_Cuda(DeviceAttributeSparse, ArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported	__cuda(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported	__cuda(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported	__cuda(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported	__cuda(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions	__cuda(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering	__cuda(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes	__cuda(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch	__cuda(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingCudaArraySupported	__cuda_Cuda(DeviceAttributeDeferredMapping, ArraySupported)
#define cudaDevAttrReserved122	__cuda(DeviceAttributeReserved122)
#define cudaDevAttrReserved123	__cuda(DeviceAttributeReserved123)
#define cudaDevAttrReserved124	__cuda(DeviceAttributeReserved124)
#define cudaDevAttrIpcEventSupport	__cuda(DeviceAttributeIpcEventSupport)
#define cudaDevAttrMemSyncDomainCount	__cuda(DeviceAttributeMemSyncDomainCount)
#define cudaDevAttrReserved127	__cuda(DeviceAttributeReserved127)
#define cudaDevAttrReserved128	__cuda(DeviceAttributeReserved128)
#define cudaDevAttrReserved129	__cuda(DeviceAttributeReserved129)
#define cudaDevAttrNumaConfig	__cuda(DeviceAttributeNumaConfig)
#define cudaDevAttrNumaId	__cuda(DeviceAttributeNumaId)
#define cudaDevAttrReserved132	__cuda(DeviceAttributeReserved132)
#define cudaDevAttrMpsEnabled	__cuda(DeviceAttributeMpsEnabled)
#define cudaDevAttrHostNumaId	__cuda(DeviceAttributeHostNumaId)
#define cudaDevAttrWaveSize	__cuda(DeviceAttributeWaveSize)
#define cudaDevAttrHdpMemFlushCntl	__cuda(DeviceAttributeHdpMemFlushCntl)
#define cudaDevAttrHdpRegFlushCntl	__cuda(DeviceAttributeHdpRegFlushCntl)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedFunc	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedFunc)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedGridDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem	__cuda(DeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem)
#define cudaDevAttrAsicRevision	__cuda(DeviceAttributeAsicRevision)
#define cudaDevAttrVirtualMemoryManagementSupported	__cuda(DeviceAttributeVirtualMemoryManagementSupported)
#define cudaDevAttrHandleTypePosixFileDescriptorSupported	__cuda(DeviceAttributeHandleTypePosixFileDescriptorSupported)
#define cudaDevAttrHandleTypeWin32HandleSupported	__cuda(DeviceAttributeHandleTypeWin32HandleSupported)
#define cudaDevAttrGenericCompressionSupported	__cuda(DeviceAttributeGenericCompressionSupported)
#define cudaDevAttrCanUseStreamWaitValue	__cuda(DeviceAttributeCanUseStreamWaitValue)
#define cudaDevAttrCanUseStreamMemOps	__cuda(DeviceAttributeCanUseStreamMemOps)
#define cudaDevAttrCanUseStreamWaitWaitValueNor	__cuda(DeviceAttributeCanUseStreamWaitWaitValueNor)
#define cudaDevAttrLocalSocketId	__cuda(DeviceAttributeLocalSocketId)
#define cudaDevAttrSocketId	__cuda(DeviceAttributeSocketId)
#define cudaDevAttrPeerSocketId	__cuda(DeviceAttributePeerSocketId)
#define cudaDevAttrMulticastSupported	__cuda(DeviceAttributeMulticastSupported)
#endif	/* __USE_HPCC__ */

#define cudaDeviceP2PAttr	__cuda(DeviceP2PAttr)
/**
 * cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr,
 *                                       int srcDevice, int dstDevice);
 */
#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	__cuda(DeviceGetP2PAttribute(v, attr, src, dst))
#define cudaDevP2PAttrPerformanceRank	__cuda(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported	__cuda(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported	__cuda(DevP2PAttrNativeAtomicSupported)
#ifdef __USE_HPCC__
#define cudaDevP2PAttrCudaArrayAccessSupported	hcDevP2PAttrHcArrayAccessSupported
#elif defined(__USE_LUCA__)
#define cudaDevP2PAttrCudaArrayAccessSupported	lcDevP2PAttrLcArrayAccessSupported
#elif defined(__USE_HIP__)
#define cudaDevP2PAttrCudaArrayAccessSupported	hipDevP2PAttrHipArrayAccessSupported
#else
#define cudaDevP2PAttrCudaArrayAccessSupported	cudaDevP2PAttrCudaArrayAccessSupported
#endif

/**
 * CUDA 13.0
 * cudaError_t cudaDeviceGetPCIBusId(char *pciBusId, int len, int device);
 *
 * HIP 6.4
 * hipError_t hipDeviceGetPCIBusId(char* pciBusId, int len, int device);
 */
#define cudaDeviceGetPCIBusId(p,l,d)	__cuda(DeviceGetPCIBusId(p,l,d))

/**
 * CUDA 13.0
 * cudaError_t cudaDeviceGetByPCIBusId(int *device, const char *pciBusId);
 *
 * HIP 6.4
 * hipError_t hipDeviceGetByPCIBusId(int* device, const char* pciBusId);
 */
#define cudaDeviceGetByPCIBusId(d,p)	__cuda(DeviceGetByPCIBusId(d,p))

/**
 * cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice);
 */
#define cudaDeviceCanAccessPeer(can, devfrom, devto) __cuda(DeviceCanAccessPeer(can, devfrom, devto))
/**
 * CUDA 13.0
 * cudaError_t cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipDeviceEnablePeerAccess(int peerDeviceId, unsigned int flags);
 */
#define cudaDeviceEnablePeerAccess(peerdev, flag)	__cuda(DeviceEnablePeerAccess(peerdev, flag))

/**
 * CUDA
 * cudaError_t cudaDeviceDisablePeerAccess(int peerDevice);
 *
 * LUCA
 * lcError_t lcDeviceDisablePeerAccess(int peerDeviceId);
 */
#define cudaDeviceDisablePeerAccess(dev)	__cuda(DeviceDisablePeerAccess(dev))

/**
 * CUDA 12:
 * cudaError_t cudaDeviceSynchronize(void);
 *
 * HIP:
 * hipError_t hipDeviceSynchronize(void);
 */
#define cudaDeviceSynchronize()	__cuda(DeviceSynchronize())

#define cudaIpcMemHandle_t	__cuda(IpcMemHandle_t)
/**
 * CUDA 13.0
 * cudaError_t cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle, void *devPtr);
 *
 * HIP 6.4
 * hipError_t hipIpcGetMemHandle(hipIpcMemHandle_t* handle, void* devPtr);
 */
#define cudaIpcGetMemHandle	__cuda(IpcGetMemHandle)

/**
 * CUDA 13.0
 * cudaError_t cudaIpcOpenMemHandle(void **devPtr, cudaIpcMemHandle_t handle, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipIpcOpenMemHandle(void** devPtr, hipIpcMemHandle_t handle, unsigned int flags);
 */
#define cudaIpcOpenMemHandle	__cuda(IpcOpenMemHandle)

/**
 * CUDA 13.0
 * cudaError_t cudaIpcCloseMemHandle(void *devPtr);
 *
 * HIP 6.4
 * hipError_t hipIpcCloseMemHandle(void* devPtr);
 */
#define cudaIpcCloseMemHandle(p)	__cuda(IpcCloseMemHandle(p))

#include "adapter/cublas.h"

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */
#define cuComplex	__cu(Complex)
#define cuDoubleComplex	__cu(DoubleComplex)

#include "adapter/curand.h"
#include "adapter/cufft.h"
#include "adapter/cusparse.h"

/**
 * Module Management
 */
/**
 * CUDA 13: typedef struct CUmod_st *CUmodule;
 */
#define CUmodule	__CU(module)

/**
 * CUDA 13
 * CUresult cuModuleLoad(CUmodule* module, const char *fname);
 *
 * HIP
 * hipError_t hipModuleLoad(hipModule_t *module, const char* fname);
 */
#define cuModuleLoad(pmodule, name)	__cu(ModuleLoad(pmodule, name))

/**
 * CUDA 13
 * CUresult cuModuleUnload(CUmodule hmod);
 *
 * HIP
 * typedef struct ihipModule_t* hipModule_t;
 * hipError_t hipModuleUnload(hipModule_t module);
 */
#define cuModuleUnload(mod)	__cu(ModuleUnload(mod))
#define CUfunction	__CU(function)
/**
 * CUDA 13
 * CUresult cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name);
 *
 * HIP
 * hipError_t hipModuleGetFunction(hipFunction_t* function, hipModule_t module,
 *                                 const char* kname);
 *
 * HPCC
 * hcError_t hcModuleGetFunction(hcFunction_t *function, hcModule_t module,
 *                               const char *kname);
 */
#define cuModuleGetFunction(pfunc, mod, name)	__cu(ModuleGetFunction(pfunc, mod, name))

/**
 * CUDA 13:
 * CUresult cuModuleLoadData(CUmodule *module, const void *image);
 *
 * HIP
 * hipError_t hipModuleLoadData(hipModule_t* module, const void* image);
 */
#define cuModuleLoadData	__cu(ModuleLoadData)

/**
 * CUDA 13
 * CUresult cuModuleLoadDataEx(CUmodule *module, const void *image,
 *                             unsigned int numOptions, CUjit_option *options,
 *                             void **optionValues);
 *
 * HIP
 * hipError_t hipModuleLoadDataEx(hipModule_t* module, const void* image,
 *                                unsigned int numOptions,
 *                                hipJitOption* options, void** optionValues);
 */
#define CUjit_option	__CU(jit_option)
#define cuModuleLoadDataEx	__cu(ModuleLoadDataEx)

/******************************************************************************\
 *             RTC                                                            *
\******************************************************************************/
#define nvrtcResult	__nv(rtcResult)
#define NVRTC_SUCCESS	__NV(RTC_SUCCESS)
#define NVRTC_ERROR_OUT_OF_MEMORY	__NV(RTC_ERROR_OUT_OF_MEMORY)
#define NVRTC_ERROR_PROGRAM_CREATION_FAILURE	__NV(RTC_ERROR_PROGRAM_CREATION_FAILURE)
#define NVRTC_ERROR_INVALID_INPUT	__NV(RTC_ERROR_INVALID_INPUT)
#define NVRTC_ERROR_INVALID_PROGRAM	__NV(RTC_ERROR_INVALID_PROGRAM)
#define NVRTC_ERROR_INVALID_OPTION	__NV(RTC_ERROR_INVALID_OPTION)
#define NVRTC_ERROR_COMPILATION	__NV(RTC_ERROR_COMPILATION)
#define NVRTC_ERROR_BUILTIN_OPERATION_FAILURE	__NV(RTC_ERROR_BUILTIN_OPERATION_FAILURE)
#define NVRTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION	__NV(RTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION)
#define NVRTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION	__NV(RTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION)
#define NVRTC_ERROR_NAME_EXPRESSION_NOT_VALID	__NV(RTC_ERROR_NAME_EXPRESSION_NOT_VALID)
#define NVRTC_ERROR_INTERNAL_ERROR	__NV(RTC_ERROR_INTERNAL_ERROR)
#define NVRTC_ERROR_TIME_FILE_WRITE_FAILED	__NV(RTC_ERROR_TIME_FILE_WRITE_FAILED)

#define nvrtcGetErrorString __nv(rtcGetErrorString)

#define nvrtcProgram	__nv(rtcProgram)

/**
 * CUDA 13
 * nvrtcResult nvrtcCreateProgram(nvrtcProgram *prog,
 *                                const char *src,
 *                                const char *name,
 *                                int numHeaders,
 *                                const char * const *headers,
 *                                const char * const *includeNames);
 *
 * HIP
 * hiprtcResult hiprtcCreateProgram(hiprtcProgram* prog,
 *                                  const char* src,
 *                                  const char* name,
 *                                  int numHeaders,
 *                                  const char** headers,
 *                                  const char** includeNames);
 */
#define nvrtcCreateProgram __nv(rtcCreateProgram)

/**
 * CUDA 12:
 * nvrtcResult nvrtcDestroyProgram(nvrtcProgram *prog);
 *
 * HIP:
 * hiprtcResult hiprtcDestroyProgram(hiprtcProgram* prog);
 */
#define nvrtcDestroyProgram(prog) __nv(rtcDestroyProgram(prog))

/**
 * CUDA 12 and 13 don't have it?
 * HIP:
 * hiprtcResult hiprtcGetCode(hiprtcProgram prog, char* code);
 * hiprtcResult hiprtcGetCodeSize(hiprtcProgram prog, size_t* codeSizeRet);
 * hiprtcResult hiprtcGetBitcode(hiprtcProgram prog, char* bitcode);
 * hiprtcResult hiprtcGetBitcodeSize(hiprtcProgram prog, size_t* bitcode_size);
 */

/**
 * CUDA 12:
 * nvrtcResult nvrtcCompileProgram(nvrtcProgram prog,
 *                                 int numOptions, const char * const *options);
 * HIP:
 * hiprtcResult hiprtcCompileProgram(hiprtcProgram prog,
 *                                   int numOptions,
 *                                   const char** options);
 */
#define nvrtcCompileProgram(prog, numOptions, options)	\
	__nv(rtcCompileProgram(prog, numOptions, options))

/**
 * CUDA 12:
 * nvrtcResult nvrtcGetProgramLog(nvrtcProgram prog, char *log);
 *
 * HIP:
 * hiprtcResult hiprtcGetProgramLog(hiprtcProgram prog, char* log);
 */
#define nvrtcGetProgramLog(prog, log)	__nv(rtcGetProgramLog(prog, log))

/**
 * CUDA 13
 * nvrtcResult nvrtcGetProgramLogSize(nvrtcProgram prog, size_t *logSizeRet);
 *
 * HIP
 * hiprtcResult hiprtcGetProgramLogSize(hiprtcProgram prog, size_t* logSizeRet);
 */
#define nvrtcGetProgramLogSize	__nv(rtcGetProgramLogSize)

#define nvrtcGetPTXSize __nv(rtcGetPTXSize)
#define nvrtcGetPTX __nv(rtcGetPTX)

/**
 * WARNING: cuda don't has Bitcode functions, this use to normalize development.
 * LUCA/HPCC like ROCm HIP, thus, just define HIP here.
 */
#define hiprtcGetBitcodeSize __nv(rtcGetBitcodeSize)
#define hiprtcGetBitcode __nv(rtcGetBitcode)

/**
 * There are store some special macros from here.
 */
#if defined(__USE_HPCC__) || defined(__USE_LUCA__)
# undef CUresult
# undef CUdevice
# undef CUmodule
# undef CUfunction
# undef CUjit_option
# undef CUDA_ERROR_INVALID_VALUE
# undef CUDA_SUCCESS

# if defined(__USE_HPCC__)
#  define CUresult	hcError_t
#  define CUdevice	hcDevice_t
#  define CUmodule	hcModule_t
#  define CUfunction	hcFunction_t
#  define CUjit_option	hcJitOption
# elif defined(__USE_LUCA__)
#  ifdef LUCA_PHASE_II_PROJECT
#   define CUresult	lcError_t
#   define CUdevice	lcDevice_t
#   define CUmodule	lcModule_t
#   define CUfunction	lcFunction_t
#   define CUjit_option	lcJitOption
#  else
#   define CUresult	hcError_t
#   define CUdevice	hcDevice_t
#   define CUmodule	hcModule_t
#   define CUfunction	hcFunction_t
#   define CUjit_option	hcJitOption
#  endif
# endif
# define CUDA_ERROR_INVALID_VALUE	cudaErrorInvalidValue
# define CUDA_SUCCESS	cudaSuccess
#elif defined(__USE_HIP__)
# undef CUresult
# undef CUdevice
# undef CUmodule
# undef CUfunction
# undef CUjit_option
# undef CUDA_ERROR_INVALID_VALUE
# undef CUDA_SUCCESS

# define CUresult	hipError_t
# define CUdevice	hipDevice_t
# define CUmodule	hipModule_t
# define CUfunction	hipFunction_t
# define CUjit_option	hipJitOption
# define CUDA_ERROR_INVALID_VALUE	hipErrorInvalidValue
# define CUDA_SUCCESS	hipSuccess
#endif

/* enum cudaRoundMode */
#define cudaRoundMode	__cuda(RoundMode)
#define cudaRoundNearest	__cuda(RoundNearest)
#define cudaRoundZero	__cuda(RoundZero)
#define cudaRoundPosInf	__cuda(RoundPosInf)
#define cudaRoundMinInf	__cuda(RoundMinInf)

/**
 * fp6
 *   typedef __nv_fp8_storage_t __nv_fp6_storage_t;
 *   typedef __nv_fp8x2_storage_t __nv_fp6x2_storage_t;
 *   typedef __nv_fp8x4_storage_t __nv_fp6x4_storage_t;
 */
#define __nv_fp6_storage_t	____nv_(fp6_storage_t)
#define __nv_fp6x2_storage_t	____nv_(fp6x2_storage_t)
#define __nv_fp6x4_storage_t	____nv_(fp6x4_storage_t)

#define __nv_fp6_e2m3	____nv_(fp6_e2m3)
#define __nv_fp6_e3m2	____nv_(fp6_e3m2)
#define __nv_fp6x2_e2m3	____nv_(fp6x2_e2m3)
#define __nv_fp6x2_e3m2	____nv_(fp6x2_e3m2)
#define __nv_fp6x4_e2m3	____nv_(fp6x4_e2m3)
#define __nv_fp6x4_e3m2	____nv_(fp6x4_e3m2)

#define __nv_fp6_interpretation_t	____nv_(fp6_interpretation_t)
#define __NV_E2M3	____NV_(E2M3)
#define __NV_E3M2	____NV_(E3M2)

/**
 * fp8
 *   typedef unsigned char __nv_fp8_storage_t;
 *
 *   typedef unsigned short int __nv_fp8x2_storage_t;
 *   typedef __nv_fp8x2_storage_t __nv_fp4x4_storage_t;
 *
 *   typedef unsigned int __nv_fp8x4_storage_t;
 *
 * bfloat16
 *
 *   typedef struct __CUDA_ALIGN__(2) {
 *     unsigned short x;
 *   } __nv_bfloat16_raw;
 *
 *   typedef struct __CUDA_ALIGN__(4) {
 *     unsigned short x;
 *     unsigned short y;
 *   } __nv_bfloat162_raw;
 */
#define __nv_fp8_storage_t	____nv_(fp8_storage_t)
#define __nv_fp8x2_storage_t	____nv_(fp8x2_storage_t)
#define __nv_fp8x4_storage_t	____nv_(fp8x4_storage_t)

#define __nv_fp8_interpretation_t	____nv_(fp8_interpretation_t)
#define __NV_E4M3	____NV_(E4M3)
#define __NV_E5M2	____NV_(E5M2)

#define __nv_saturation_t	____nv_(saturation_t)
#define __NV_NOSAT	____NV_(NOSAT)
#define __NV_SATFINITE	____NV_(SATFINITE)

#define __nv_fp8_e4m3	____nv_(fp8_e4m3)
#define __nv_fp8_e5m2	____nv_(fp8_e5m2)
#define __nv_fp8_e8m0	____nv_(fp8_e8m0)
#define __nv_fp8x2_e4m3	____nv_(fp8x2_e4m3)
#define __nv_fp8x2_e5m2	____nv_(fp8x2_e5m2)
#define __nv_fp8x2_e8m0	____nv_(fp8x2_e8m0)
#define __nv_fp8x4_e4m3	____nv_(fp8x4_e4m3)
#define __nv_fp8x4_e5m2	____nv_(fp8x4_e5m2)
#define __nv_fp8x4_e8m0	____nv_(fp8x4_e8m0)

#define __nv_bfloat16	____nv_(bfloat16)
#define __nv_bfloat16_raw	____nv_(bfloat16_raw)
#define __nv_bfloat162	____nv_(bfloat162)
#define __nv_bfloat162_raw	____nv_(bfloat162_raw)

#define __nv_cvt_halfraw_to_fp8		____nv_(cvt_halfraw_to_fp8)
#define __nv_cvt_halfraw2_to_fp8x2	____nv_(cvt_halfraw2_to_fp8x2)

#define __nv_cvt_bfloat16raw_to_e8m0	____nv_(cvt_bfloat16raw_to_e8m0)
#define __nv_cvt_bfloat16raw_to_fp8	____nv_(cvt_bfloat16raw_to_fp8)

#define __nv_cvt_bfloat162raw_to_e8m0x2	____nv_(cvt_bfloat162raw_to_e8m0x2)
#define __nv_cvt_bfloat16raw2_to_fp8x2	____nv_(cvt_bfloat16raw2_to_fp8x2)

#define __nv_cvt_double2_to_e8m0x2	____nv_(cvt_double2_to_e8m0x2)
#define __nv_cvt_double2_to_fp8x2	____nv_(cvt_double2_to_fp8x2)
#define __nv_cvt_double_to_e8m0		____nv_(cvt_double_to_e8m0)
#define __nv_cvt_double_to_fp8		____nv_(cvt_double_to_fp8)

#define __nv_cvt_e8m0_to_bf16raw	____nv_(cvt_e8m0_to_bf16raw)
#define __nv_cvt_e8m0x2_to_bf162raw	____nv_(cvt_e8m0x2_to_bf162raw)

#define __nv_cvt_float2_to_e8m0x2	____nv_(cvt_float2_to_e8m0x2)
#define __nv_cvt_float2_to_fp8x2	____nv_(cvt_float2_to_fp8x2)

#define __nv_cvt_float_to_e8m0		____nv_(cvt_float_to_e8m0)
#define __nv_cvt_float_to_fp8		____nv_(cvt_float_to_fp8)

#define __nv_cvt_fp8_to_halfraw		____nv_(cvt_fp8_to_halfraw)
#define __nv_cvt_fp8x2_to_halfraw2	____nv_(cvt_fp8x2_to_halfraw2)

/******************************************************************************\
 *             Solver: LAPACK-marshalling library                             *
\******************************************************************************/
#define cusolverStatus_t	__nv(solverStatus_t)
#define CUSOLVER_STATUS_SUCCESS __CU(SOLVER_STATUS_SUCCESS)
#define CUSOLVER_STATUS_NOT_INITIALIZED __CU(SOLVER_STATUS_NOT_INITIALIZED)
#define CUSOLVER_STATUS_ALLOC_FAILED __CU(SOLVER_STATUS_ALLOC_FAILED)
#define CUSOLVER_STATUS_INVALID_VALUE __CU(SOLVER_STATUS_INVALID_VALUE)
#define CUSOLVER_STATUS_ARCH_MISMATCH __CU(SOLVER_STATUS_ARCH_MISMATCH)
#define CUSOLVER_STATUS_MAPPING_ERROR __CU(SOLVER_STATUS_MAPPING_ERROR)
#define CUSOLVER_STATUS_EXECUTION_FAILED __CU(SOLVER_STATUS_EXECUTION_FAILED)
#define CUSOLVER_STATUS_INTERNAL_ERROR __CU(SOLVER_STATUS_INTERNAL_ERROR)
#define CUSOLVER_STATUS_MATRIX_TYPE_NOT_SUPPORTED __CU(SOLVER_STATUS_MATRIX_TYPE_NOT_SUPPORTED)
#define CUSOLVER_STATUS_NOT_SUPPORTED __CU(SOLVER_STATUS_NOT_SUPPORTED)
#define CUSOLVER_STATUS_ZERO_PIVOT __CU(SOLVER_STATUS_ZERO_PIVOT)
#define CUSOLVER_STATUS_INVALID_LICENSE __CU(SOLVER_STATUS_INVALID_LICENSE)
#define CUSOLVER_STATUS_IRS_PARAMS_NOT_INITIALIZED __CU(SOLVER_STATUS_IRS_PARAMS_NOT_INITIALIZED)
#define CUSOLVER_STATUS_IRS_PARAMS_INVALID __CU(SOLVER_STATUS_IRS_PARAMS_INVALID)
#define CUSOLVER_STATUS_IRS_PARAMS_INVALID_PREC __CU(SOLVER_STATUS_IRS_PARAMS_INVALID_PREC)
#define CUSOLVER_STATUS_IRS_PARAMS_INVALID_REFINE __CU(SOLVER_STATUS_IRS_PARAMS_INVALID_REFINE)
#define CUSOLVER_STATUS_IRS_PARAMS_INVALID_MAXITER __CU(SOLVER_STATUS_IRS_PARAMS_INVALID_MAXITER)
#define CUSOLVER_STATUS_IRS_INTERNAL_ERROR __CU(SOLVER_STATUS_IRS_INTERNAL_ERROR)
#define CUSOLVER_STATUS_IRS_NOT_SUPPORTED __CU(SOLVER_STATUS_IRS_NOT_SUPPORTED)
#define CUSOLVER_STATUS_IRS_OUT_OF_RANGE __CU(SOLVER_STATUS_IRS_OUT_OF_RANGE)
#define CUSOLVER_STATUS_IRS_NRHS_NOT_SUPPORTED_FOR_REFINE_GMRES __CU(SOLVER_STATUS_IRS_NRHS_NOT_SUPPORTED_FOR_REFINE_GMRES)
#define CUSOLVER_STATUS_IRS_INFOS_NOT_INITIALIZED __CU(SOLVER_STATUS_IRS_INFOS_NOT_INITIALIZED)
#define CUSOLVER_STATUS_IRS_INFOS_NOT_DESTROYED __CU(SOLVER_STATUS_IRS_INFOS_NOT_DESTROYED)
#define CUSOLVER_STATUS_IRS_MATRIX_SINGULAR __CU(SOLVER_STATUS_IRS_MATRIX_SINGULAR)
#define CUSOLVER_STATUS_INVALID_WORKSPACE __CU(SOLVER_STATUS_INVALID_WORKSPACE)
/**
 * cusolverStatus_t cusolverGetVersion(int *version);
 */
#define cusolverGetVersion(v)	__nv(solverGetVersion(v))

/******************************************************************************\
 *             NCCL: NVIDIA Collective Communication Library                  *
\******************************************************************************/
/* /usr/include/nccl.h, /opt/luca/include/hccl.h */
/**
 * HPCC 3.0.0
 * LUCA 3.2.1
 *   struct {
 *     // attributes that users should never touch.
 *     size_t size;
 *     unsigned int magic;
 *     unsigned int version;
 *     // attributes that users are able to customize.
 *     int blocking;
 *   };
 *
 * NCCL 2.27.7
 *   struct ncclConfig_v22700 {
 *     // attributes that users should never touch.
 *     size_t size;
 *     unsigned int magic;
 *     unsigned int version;
 *     // attributes that users are able to customize.
 *     int blocking;
 *     int cgaClusterSize;
 *     int minCTAs;
 *     int maxCTAs;
 *     const char *netName;
 *     int splitShare;
 *     int trafficClass;
 *     const char *commName;
 *     int collnetEnable;
 *     int CTAPolicy;
 *     int shrinkShare;
 *     int nvlsCTAs;
 *   } ncclConfig_t;
 */
#define ncclConfig_t		__nccl(Config_t)
/**
 * ROCm rccl already define this in /usr/include/rccl/rccl.h
 */
#ifndef NCCL_CONFIG_INITIALIZER
#define NCCL_CONFIG_INITIALIZER	__NCCL(_CONFIG_INITIALIZER)
#endif
#define ncclResult_t		__nccl(Result_t)
#define ncclSuccess		__nccl(Success)	/* 0 */
#ifdef __USE_HPCC__
#define ncclUnhandledCudaError	__nccl(UnhandledHpccError)	/* 1 */
#elif defined(__USE_LUCA__)
#define ncclUnhandledCudaError	__nccl(UnhandledLucaError)	/* 1 */
#else /* for HIP and CUDA */
#define ncclUnhandledCudaError	__nccl(UnhandledCudaError)	/* 1 */
#endif
#define ncclSystemError		__nccl(SystemError)	/* 2 */
#define ncclInternalError	__nccl(InternalError)
#define ncclInvalidArgument	__nccl(InvalidArgument)
#define ncclInvalidUsage	__nccl(InvalidUsage)
#define ncclRemoteError		__nccl(RemoteError)
#define ncclInProgress		__nccl(InProgress)
#define ncclNumResults		__nccl(NumResults)	/* 8 */

/* const char*  ncclGetErrorString(ncclResult_t result); */
#define ncclGetErrorString(result)	__nccl(GetErrorString(result))

#define ncclGetVersion(version)	__nccl(GetVersion(version))
#define pncclGetVersion(version)	__pnccl(GetVersion(version))

/**
 * typedef struct {
 *   char internal[128];
 * } ncclUniqueId;
 */
#define ncclUniqueId		__nccl(UniqueId)
/**
 * ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId);
 */
#define ncclGetUniqueId(id)	__nccl(GetUniqueId(id))

/* Communicator */
#define ncclComm_t	__nccl(Comm_t)

/**
 * ncclResult_t ncclCommInitRank(ncclComm_t* comm, int nranks, ncclUniqueId commId, int rank);
 */
#define ncclCommInitRank	__nccl(CommInitRank)

/**
 * ncclResult_t ncclCommInitRankConfig(ncclComm_t* comm, int nranks,
 *                                     ncclUniqueId commId, int rank,
 *                                     ncclConfig_t* config);
 */
#define ncclCommInitRankConfig	__nccl(CommInitRankConfig)

/**
 * ncclResult_t ncclCommInitAll(ncclComm_t* comms, int ndev, const int* devlist);
 */
#define ncclCommInitAll(comm, ndev, devlist)	__nccl(CommInitAll(comm, ndev, devlist))
#define ncclCommDestroy	__nccl(CommDestroy)

#define ncclGroupStart	__nccl(GroupStart)
#define ncclGroupEnd	__nccl(GroupEnd)

#define ncclRedOp_t	__nccl(RedOp_t)
#define ncclSum		__nccl(Sum)
#define ncclProd	__nccl(Prod)
#define ncclMax		__nccl(Max)
#define ncclMin		__nccl(Min)
#define ncclAvg		__nccl(Avg)
#define ncclNumOps	__nccl(NumOps)
#define ncclMaxRedOp	__nccl(MaxRedOp)

#define ncclDataType_t	__nccl(DataType_t)
#define ncclInt8	__nccl(Int8)
#define ncclChar	__nccl(Char)
#define ncclUint8	__nccl(Uint8)
#define ncclInt32	__nccl(Int32)
#define ncclInt		__nccl(Int)
#define ncclUint32	__nccl(Uint32)
#define ncclInt64	__nccl(Int64)
#define ncclUint64	__nccl(Uint64)
#define ncclFloat16	__nccl(Float16)
#define ncclHalf	__nccl(Half)
#define ncclFloat32	__nccl(Float32)
#define ncclFloat	__nccl(Float)
#define ncclFloat64	__nccl(Float64)
#define ncclDouble	__nccl(Double)
#define ncclBfloat16	__nccl(Bfloat16)
#define ncclNumTypes	__nccl(NumTypes)

/**
 * ncclResult_t  ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
 *                             ncclDataType_t datatype, ncclRedOp_t op,
 *                             ncclComm_t comm, cudaStream_t stream);
 */
#define ncclAllReduce	__nccl(AllReduce)

/******************************************************************************\
 *             DNN                                                            *
\******************************************************************************/
// TODO

/******************************************************************************\
 * GPUDirect Storage, cuFile                                                  *
\******************************************************************************/
#define CUfileHandle_t	__CU(fileHandle_t)
#define CUfileFileHandleType	__CU(fileFileHandleType)
/* Linux based fd */
#define CU_FILE_HANDLE_TYPE_OPAQUE_FD	__CU(_FILE_HANDLE_TYPE_OPAQUE_FD)
/* Windows based handle (unsupported) */
#define CU_FILE_HANDLE_TYPE_OPAQUE_WIN32	__CU(_FILE_HANDLE_TYPE_OPAQUE_WIN32)
/* Userspace based FS */
#define CU_FILE_HANDLE_TYPE_USERSPACE_FS	__CU(_FILE_HANDLE_TYPE_USERSPACE_FS)

#define CUfileDescr_t	__CU(fileDescr_t)
#define CUfileError_t	__CU(fileError_t)
#define CU_FILE_SUCCESS	__CU(_FILE_SUCCESS)

#define CUfileOpError	__CU(fileOpError)
/**
 * static inline const char *cufileop_status_error(CUfileOpError status)
 */
#define cufileop_status_error	__cu(fileop_status_error)

/**
 * CUfileError_t cuFileDriverOpen(void);
 * LCfileError_t lcFileDriverOpen(void);
 */
#define cuFileDriverOpen	__cu(FileDriverOpen)

/**
 * LUCA 3.2.1
 * LCfileError_t lcFileHandleRegister(LCfileHandle_t *fh, LCfileDescr_t *descr);
 */
#define cuFileHandleRegister	__cu(FileHandleRegister)
#define cuFileHandleDeregister	__cu(FileHandleDeregister)

/**
 * LCfileError_t lcFileBufRegister(const void *devPtr_base, size_t length, int flags);
 */
#define cuFileBufRegister	__cu(FileBufRegister)
/**
 * LCfileError_t lcFileBufDeregister(const void *devPtr_base);
 */
#define cuFileBufDeregister	__cu(FileBufDeregister)

/**
 * ssize_t cuFileWrite(CUfileHandle_t fh, const void *bufPtr_base, size_t size,
 *                     off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileWrite	__cu(FileWrite)
/**
 * ssize_t cuFileRead(CUfileHandle_t fh, void *bufPtr_base, size_t size,
 *                    off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileRead	__cu(FileRead)

/**
 * CUDA/HPCC/LUCA all have this macro
 * #define CUFILEOP_STATUS_ENTRIES \
 *     CUFILE_OP(0, LC_FILE_SUCCESS, lcfile success) \
 *     ....
 */
#define CUFILEOP_STATUS_ENTRIES	__CU(FILEOP_STATUS_ENTRIES)

/******************************************************************************\
 *             PTI - CUDA Profiling Tools Interface                           *
\******************************************************************************/
#define CUPTI_API_VERSION	__CU(PTI_API_VERSION)
/**
 * CUptiResult cuptiGetVersion(uint32_t *version);
 */
#define cuptiGetVersion	__cu(ptiGetVersion)

#define CUpti_SubscriberHandle	__CU(pti_SubscriberHandle)
#define CUpti_CallbackDomain	__CU(pti_CallbackDomain)
#define CUpti_CallbackId	__CU(pti_CallbackId)
#define CUpti_CallbackData	__CU(pti_CallbackData)

/**
 * CUptiResult cuptiGetCallbackName(CUpti_CallbackDomain domain,
 *                                  uint32_t cbid, const char **name)
 */
#define cuptiGetCallbackName	__cu(ptiGetCallbackName)

#define CUptiResult	__CU(ptiResult)
#define CUPTI_SUCCESS	__CU(PTI_SUCCESS)
#define cuptiGetResultString(n, pstr)	__cu(ptiGetResultString(n, pstr))

/**
 * CUptiResult cuptiSubscribe(CUpti_SubscriberHandle *subscriber,
 *                            CUpti_CallbackFunc callback,
 *                            void *userdata);
 *
 * CUptiResult cuptiSubscribe_v2(CUpti_SubscriberHandle *subscriber,
 *                               CUpti_CallbackFunc callback,
 *                               void *userdata,
 *                               CUpti_SubscriberParams *pParams)
 */
#define cuptiSubscribe(s, c, u)	__cu(ptiSubscribe(s, c, u))
#define cuptiSubscribe_v2	__cu(ptiSubscribe_v2)

/**
 * CUptiResult cuptiUnsubscribe(CUpti_SubscriberHandle subscriber);
 */
#define cuptiUnsubscribe(s)	__cu(ptiUnsubscribe(s))

/**
 * CUptiResult cuptiEnableDomain(uint32_t enable,
 *                               CUpti_SubscriberHandle subscriber,
 *                               CUpti_CallbackDomain domain);
 */
#define cuptiEnableDomain(e, s, d)	__cu(ptiEnableDomain(e, s, d))

/**
 * CUptiResult cuptiEnableAllDomains(uint32_t enable, CUpti_SubscriberHandle subscriber)
 */
#define cuptiEnableAllDomains	__cu(ptiEnableAllDomains)

/**
 * CUptiResult cuptiSupportedDomains(size_t *domainCount,
 *                                   CUpti_DomainTable *domainTable)
 */
#define cuptiSupportedDomains	__cu(ptiSupportedDomains)

/**
 * CUptiResult cuptiEnableCallback(uint32_t enable,
 *                                 CUpti_SubscriberHandle subscriber,
 *                                 CUpti_CallbackDomain domain,
 *                                 CUpti_CallbackId cbid)
 */
#define cuptiEnableCallback	__cu(ptiEnableCallback)

/**
 * CUptiResult cuptiGetCallbackState(uint32_t *enable,
 *                                   CUpti_SubscriberHandle subscriber,
 *                                   CUpti_CallbackDomain domain,
 *                                   CUpti_CallbackId cbid)
 */
#define cuptiGetCallbackState	__cu(ptiGetCallbackState)

#define CUPTI_CB_DOMAIN_INVALID	__CU(PTI_CB_DOMAIN_INVALID)
#define CUPTI_CB_DOMAIN_DRIVER_API	__CU(PTI_CB_DOMAIN_DRIVER_API)
#define CUPTI_CB_DOMAIN_RUNTIME_API	__CU(PTI_CB_DOMAIN_RUNTIME_API)
#define CUPTI_CB_DOMAIN_RESOURCE	__CU(PTI_CB_DOMAIN_RESOURCE)
#define CUPTI_CB_DOMAIN_SYNCHRONIZE	__CU(PTI_CB_DOMAIN_SYNCHRONIZE)
#define CUPTI_CB_DOMAIN_NVTX	__CU(PTI_CB_DOMAIN_NVTX)
#define CUPTI_CB_DOMAIN_STATE	__CU(PTI_CB_DOMAIN_STATE)
#define CUPTI_CB_DOMAIN_SIZE	__CU(PTI_CB_DOMAIN_SIZE)
#define CUPTI_CB_DOMAIN_FORCE_INT	__CU(PTI_CB_DOMAIN_FORCE_INT)

#define CUPTI_API_ENTER	__CU(PTI_API_ENTER)

#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, Memcpy)
#define cudaMemcpy_v3020_params	__cuda(Memcpy_params)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, Malloc)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernel_v7000	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, LaunchKernel)
/**
 * CUDA 13.0
 * typedef struct cudaLaunchKernel_v7000_params_st {
 *   const void *func;
 *   dim3 gridDim;
 *   dim3 blockDim;
 *   void **args;
 *   size_t sharedMem;
 *   cudaStream_t stream;
 * } cudaLaunchKernel_v7000_params;
 *
 * LUCA 3.2.1
 * typedef struct lcLaunchKernel_params_st {
 *   const void* function_address;
 *   dim3 numBlocks;
 *   dim3 dimBlocks;
 *   void** args;
 *   void* args__val;
 *   size_t sharedMemBytes;
 *   lcStream_t stream;
 * } lcLaunchKernel_params;
 */
#define cudaLaunchKernel_v7000_params	__cuda(LaunchKernel_params)

/**
 * CUDA 13:
 * typedef struct cudaMalloc_v3020_params_st {
 *   void **devPtr;
 *   size_t size;
 * } cudaMalloc_v3020_params;
 *
 * LUCA:
 * typedef struct lcMalloc_params_st {
 *   void** ptr;
 *   void* ptr__val;
 *   size_t bytesize;
 * } lcMalloc_params;
 */
#define cudaMalloc_v3020_params	__cuda(Malloc_params)

#define CUcontext	__CU(context)
#define cuCtxCreate __cu(CtxCreate)
#define cuCtxDestroy __cu(CtxDestroy)

/**
 * LUCA: lcError_t lcCtxSynchronize();
 */
#define cuCtxSynchronize __cu(CtxSynchronize)

#define CUpti_Activity	__CU(pti_Activity)
#define CUpti_ActivityKernel	__CU(pti_ActivityKernel)
#define CUpti_ActivityKernel1	__CU(pti_ActivityKernel1)
#define CUpti_ActivityKernel2	__CU(pti_ActivityKernel2)
#define CUpti_ActivityKernel3	__CU(pti_ActivityKernel3)
#define CUpti_ActivityKernel4	__CU(pti_ActivityKernel4)
#define CUpti_ActivityKernel5	__CU(pti_ActivityKernel5)
#define CUpti_ActivityKernel6	__CU(pti_ActivityKernel6)
#define CUpti_ActivityKernel7	__CU(pti_ActivityKernel7)
#define CUpti_ActivityKernel8	__CU(pti_ActivityKernel8)
#define CUpti_ActivityKernel9	__CU(pti_ActivityKernel9)
#define CUpti_ActivityKernel10	__CU(pti_ActivityKernel10)

#define cuptiActivityRegisterCallbacks	__cu(ptiActivityRegisterCallbacks)
#define cuptiActivityEnable	__cu(ptiActivityEnable)
#define cuptiActivityFlushAll	__cu(ptiActivityFlushAll)
#define cuptiActivityDisable	__cu(ptiActivityDisable)
#define cuptiActivityGetNextRecord	__cu(ptiActivityGetNextRecord)

#define CUPTI_ACTIVITY_KIND_INVALID	__CU(PTI_ACTIVITY_KIND_INVALID)
#define CUPTI_ACTIVITY_KIND_MEMCPY	__CU(PTI_ACTIVITY_KIND_MEMCPY)
#define CUPTI_ACTIVITY_KIND_MEMSET	__CU(PTI_ACTIVITY_KIND_MEMSET)
#define CUPTI_ACTIVITY_KIND_KERNEL	__CU(PTI_ACTIVITY_KIND_KERNEL)
#define CUPTI_ACTIVITY_KIND_DRIVER	__CU(PTI_ACTIVITY_KIND_DRIVER)
#define CUPTI_ACTIVITY_KIND_RUNTIME	__CU(PTI_ACTIVITY_KIND_RUNTIME)
#define CUPTI_ACTIVITY_KIND_EVENT	__CU(PTI_ACTIVITY_KIND_EVENT)
#define CUPTI_ACTIVITY_KIND_METRIC	__CU(PTI_ACTIVITY_KIND_METRIC)
#define CUPTI_ACTIVITY_KIND_DEVICE	__CU(PTI_ACTIVITY_KIND_DEVICE)
#define CUPTI_ACTIVITY_KIND_CONTEXT	__CU(PTI_ACTIVITY_KIND_CONTEXT)
#define CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL	__CU(PTI_ACTIVITY_KIND_CONCURRENT_KERNEL)
#define CUPTI_ACTIVITY_KIND_NAME	__CU(PTI_ACTIVITY_KIND_NAME)
#define CUPTI_ACTIVITY_KIND_MARKER	__CU(PTI_ACTIVITY_KIND_MARKER)
#define CUPTI_ACTIVITY_KIND_MARKER_DATA	__CU(PTI_ACTIVITY_KIND_MARKER_DATA)
#define CUPTI_ACTIVITY_KIND_SOURCE_LOCATOR	__CU(PTI_ACTIVITY_KIND_SOURCE_LOCATOR)
#define CUPTI_ACTIVITY_KIND_GLOBAL_ACCESS	__CU(PTI_ACTIVITY_KIND_GLOBAL_ACCESS)
#define CUPTI_ACTIVITY_KIND_BRANCH	__CU(PTI_ACTIVITY_KIND_BRANCH)
#define CUPTI_ACTIVITY_KIND_OVERHEAD	__CU(PTI_ACTIVITY_KIND_OVERHEAD)
#define CUPTI_ACTIVITY_KIND_CDP_KERNEL	__CU(PTI_ACTIVITY_KIND_CDP_KERNEL)
#define CUPTI_ACTIVITY_KIND_PREEMPTION	__CU(PTI_ACTIVITY_KIND_PREEMPTION)
#define CUPTI_ACTIVITY_KIND_ENVIRONMENT	__CU(PTI_ACTIVITY_KIND_ENVIRONMENT)
#define CUPTI_ACTIVITY_KIND_EVENT_INSTANCE	__CU(PTI_ACTIVITY_KIND_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMCPY2	__CU(PTI_ACTIVITY_KIND_MEMCPY2)
#define CUPTI_ACTIVITY_KIND_METRIC_INSTANCE	__CU(PTI_ACTIVITY_KIND_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION	__CU(PTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION)
#define CUPTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER	__CU(PTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER)
#define CUPTI_ACTIVITY_KIND_FUNCTION	__CU(PTI_ACTIVITY_KIND_FUNCTION)
#define CUPTI_ACTIVITY_KIND_MODULE	__CU(PTI_ACTIVITY_KIND_MODULE)
#define CUPTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE	__CU(PTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE)
#define CUPTI_ACTIVITY_KIND_SHARED_ACCESS	__CU(PTI_ACTIVITY_KIND_SHARED_ACCESS)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING	__CU(PTI_ACTIVITY_KIND_PC_SAMPLING)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO	__CU(PTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION	__CU(PTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION)
#define CUPTI_ACTIVITY_KIND_OPENACC_DATA	__CU(PTI_ACTIVITY_KIND_OPENACC_DATA)
#define CUPTI_ACTIVITY_KIND_OPENACC_LAUNCH	__CU(PTI_ACTIVITY_KIND_OPENACC_LAUNCH)
#define CUPTI_ACTIVITY_KIND_OPENACC_OTHER	__CU(PTI_ACTIVITY_KIND_OPENACC_OTHER)
#define CUPTI_ACTIVITY_KIND_CUDA_EVENT	__CU(PTI_ACTIVITY_KIND_CUDA_EVENT)
#define CUPTI_ACTIVITY_KIND_STREAM	__CU(PTI_ACTIVITY_KIND_STREAM)
#define CUPTI_ACTIVITY_KIND_SYNCHRONIZATION	__CU(PTI_ACTIVITY_KIND_SYNCHRONIZATION)
#define CUPTI_ACTIVITY_KIND_EXTERNAL_CORRELATION	__CU(PTI_ACTIVITY_KIND_EXTERNAL_CORRELATION)
#define CUPTI_ACTIVITY_KIND_NVLINK	__CU(PTI_ACTIVITY_KIND_NVLINK)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMORY	__CU(PTI_ACTIVITY_KIND_MEMORY)
#define CUPTI_ACTIVITY_KIND_PCIE	__CU(PTI_ACTIVITY_KIND_PCIE)
#define CUPTI_ACTIVITY_KIND_OPENMP	__CU(PTI_ACTIVITY_KIND_OPENMP)
#define CUPTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API	__CU(PTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API)
#define CUPTI_ACTIVITY_KIND_MEMORY2	__CU(PTI_ACTIVITY_KIND_MEMORY2)
#define CUPTI_ACTIVITY_KIND_MEMORY_POOL	__CU(PTI_ACTIVITY_KIND_MEMORY_POOL)
#define CUPTI_ACTIVITY_KIND_GRAPH_TRACE	__CU(PTI_ACTIVITY_KIND_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_JIT	__CU(PTI_ACTIVITY_KIND_JIT)
#define CUPTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE	__CU(PTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_MEM_DECOMPRESS	__CU(PTI_ACTIVITY_KIND_MEM_DECOMPRESS)
#define CUPTI_ACTIVITY_KIND_COUNT	__CU(PTI_ACTIVITY_KIND_COUNT)
#define CUPTI_ACTIVITY_KIND_FORCE_INT	__CU(PTI_ACTIVITY_KIND_FORCE_INT)

/**
 * FIXME: LUCA not support PmSampling
 */
#define CUpti_PmSampling_Object	__CU(pti_PmSampling_Object)
#define CUpti_PmSampling_CounterData_GetSampleInfo_Params	__CU(pti_PmSampling_CounterData_GetSampleInfo_Params)
#define CUpti_PmSampling_Enable_Params	__CU(pti_PmSampling_Enable_Params)
#define CUpti_PmSampling_SetConfig_Params	__CU(pti_PmSampling_SetConfig_Params)
#define CUpti_PmSampling_Start_Params	__CU(pti_PmSampling_Start_Params)
#define CUpti_Profiler_Host_Initialize_Params	__CU(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object	__CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_ConfigAddMetrics_Params	__CU(pti_Profiler_Host_ConfigAddMetrics_Params)
#define CUpti_Profiler_Host_GetConfigImageSize_Params	__CU(pti_Profiler_Host_GetConfigImageSize_Params)
#define CUpti_Profiler_Host_GetConfigImage_Params	__CU(pti_Profiler_Host_GetConfigImage_Params)
#define CUpti_Profiler_Host_GetNumOfPasses_Params	__CU(pti_Profiler_Host_GetNumOfPasses_Params)
#define CUpti_Profiler_Host_Deinitialize_Params	__CU(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Host_Object	__CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_EvaluateToGpuValues_Params	__CU(pti_Profiler_Host_EvaluateToGpuValues_Params)
#define CUpti_Profiler_Host_Initialize_Params	__CU(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object	__CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_Deinitialize_Params	__CU(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Initialize_Params	__CU(pti_Profiler_Initialize_Params)
#define CUpti_Device_GetChipName_Params	__CU(pti_Device_GetChipName_Params)

#endif
