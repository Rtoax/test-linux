// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#if defined(HAVE_HCCL)
/* Metax has CUDA-compatible APIs */
# define __pfx(name)	hc##name
# define __PFX(name)	HC##name
#elif !defined(__pfx) || !defined(__PFX)
# error "Must define __pfx() and __PFX() macros, or define HAVE_HCCL"
#endif

/* typedef hcError_t	cudaError_t; */
#define cudaError_t	__pfx(Error_t)
#define cudaSuccess	__pfx(Success)
#define cudaErrorInvalidValue	__pfx(ErrorInvalidValue)
#define cudaErrorMemoryAllocation	__pfx(ErrorMemoryAllocation)

#define cudaGetLastError()	__pfx(GetLastError())
#define cudaGetErrorString(err)	__pfx(GetErrorString(err))

#define cudaDeviceSetLimit(limit, value)	__pfx(DeviceSetLimit(limit, value))
#define cudaLimitPrintfFifoSize	__pfx(LimitPrintfFifoSize)

/**
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html
 */
#define cudaMalloc(pp, sz)	__pfx(Malloc(pp, sz))
#define cudaFree(ptr)	__pfx(Free(ptr))
#define cudaMemset(ptr, v, size)	__pfx(Memset(ptr, v, size))
#define cudaMemcpy(dev, host, size, flag)	__pfx(Memcpy(dev, host, size, flag))
#define cudaMemcpyHostToDevice	__pfx(MemcpyHostToDevice)
#define cudaMemcpyDeviceToHost	__pfx(MemcpyDeviceToHost)
#define cudaMallocManaged(pp, sz)	__pfx(MallocManaged(pp, sz))
#define cudaMallocAsync(pp, sz, stream)	__pfx(MallocAsync(pp, sz, stream))
#define cudaFreeAsync(ptr, stream)	__pfx(FreeAsync(ptr, stream))

#define cudaEvent_t	__pfx(Event_t)
#define cudaEventCreate(pe)	__pfx(EventCreate(pe))
#define cudaEventDestroy(ev)	__pfx(EventDestroy(ev))
#define cudaEventRecord(ev)	__pfx(EventRecord(ev))
#define cudaEventElapsedTime(pt, start, stop)	__pfx(EventElapsedTime(pt, start, stop))
/**
 * cudaEventSynchronize() will block the CPU until the CPU waits for the GPU
 * calculation to complete the event 'ev'.
 */
#define cudaEventSynchronize(ev)	__pfx(EventSynchronize(ev))

#define cudaLaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, stream) \
	__pfx(LaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, stream))

/**
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
#define cudaStream_t	__pfx(Stream_t)
#define cudaStreamCreate(pstream)	__pfx(StreamCreate(pstream))
#define cudaStreamSynchronize(stream)	__pfx(StreamSynchronize(stream))
#define cudaStreamDestroy(stream)	__pfx(StreamDestroy(stream))

#define cudaGetDeviceCount(pgpus)	__pfx(GetDeviceCount(pgpus))
#define cudaGetDevice(p_id)	__pfx(GetDevice(p_id))
#define cudaSetDevice(dev_id)	__pfx(SetDevice(dev_id))

#define cudaDeviceProp	__pfx(DeviceProp_t)
#define cudaGetDeviceProperties(prop, devid)	__pfx(GetDeviceProperties(prop, devid))

#define cudaDeviceGetAttribute(pval, attr, dev_id)	__pfx(DeviceGetAttribute(pval, attr, dev_id))
#if defined(HAVE_HCCL)
/* WARNING: different name */
#define cudaDevAttrMaxThreadsPerBlock	__pfx(DeviceAttributeMaxThreadsPerBlock)
#define cudaDevAttrMaxBlockDimX	__pfx(DeviceAttributeMaxBlockDimX)
#define cudaDevAttrMaxBlockDimY	__pfx(DeviceAttributeMaxBlockDimY)
#define cudaDevAttrMaxBlockDimZ	__pfx(DeviceAttributeMaxBlockDimZ)
#define cudaDevAttrMaxGridDimX	__pfx(DeviceAttributeMaxGridDimX)
#define cudaDevAttrMaxGridDimY	__pfx(DeviceAttributeMaxGridDimY)
#define cudaDevAttrMaxGridDimZ	__pfx(DeviceAttributeMaxGridDimZ)
#define cudaDevAttrMaxSharedMemoryPerBlock	__pfx(DeviceAttributeMaxSharedMemoryPerBlock)
#define cudaDevAttrTotalConstantMemory	__pfx(DeviceAttributeTotalConstantMemory)
#define cudaDevAttrWarpSize	__pfx(DeviceAttributeWarpSize)
#define cudaDevAttrMaxPitch	__pfx(DeviceAttributeMaxPitch)
#define cudaDevAttrMaxRegistersPerBlock	__pfx(DeviceAttributeMaxRegistersPerBlock)
#define cudaDevAttrClockRate	__pfx(DeviceAttributeClockRate)
#define cudaDevAttrTextureAlignment	__pfx(DeviceAttributeTextureAlignment)
#define cudaDevAttrGpuOverlap	__pfx(DeviceAttributeGpuOverlap)
#define cudaDevAttrMultiProcessorCount	__pfx(DeviceAttributeMultiProcessorCount)
#define cudaDevAttrKernelExecTimeout	__pfx(DeviceAttributeKernelExecTimeout)
#define cudaDevAttrIntegrated	__pfx(DeviceAttributeIntegrated)
#define cudaDevAttrCanMapHostMemory	__pfx(DeviceAttributeCanMapHostMemory)
#define cudaDevAttrComputeMode	__pfx(DeviceAttributeComputeMode)
#define cudaDevAttrMaxTexture1DWidth	__pfx(DeviceAttributeMaxTexture1DWidth)
#define cudaDevAttrMaxTexture2DWidth	__pfx(DeviceAttributeMaxTexture2DWidth)
#define cudaDevAttrMaxTexture2DHeight	__pfx(DeviceAttributeMaxTexture2DHeight)
#define cudaDevAttrMaxTexture3DWidth	__pfx(DeviceAttributeMaxTexture3DWidth)
#define cudaDevAttrMaxTexture3DHeight	__pfx(DeviceAttributeMaxTexture3DHeight)
#define cudaDevAttrMaxTexture3DDepth	__pfx(DeviceAttributeMaxTexture3DDepth)
#define cudaDevAttrMaxTexture2DLayeredWidth	__pfx(DeviceAttributeMaxTexture2DLayeredWidth)
#define cudaDevAttrMaxTexture2DLayeredHeight	__pfx(DeviceAttributeMaxTexture2DLayeredHeight)
#define cudaDevAttrMaxTexture2DLayeredLayers	__pfx(DeviceAttributeMaxTexture2DLayeredLayers)
#define cudaDevAttrSurfaceAligement	__pfx(DeviceAttributeSurfaceAligement)
#define cudaDevAttrConcurrentKernels	__pfx(DeviceAttributeConcurrentKernels)
#define cudaDevAttrEccEnabled	__pfx(DeviceAttributeEccEnabled)
#define cudaDevAttrPciBusId	__pfx(DeviceAttributePciBusId)
#define cudaDevAttrPciDeviceId	__pfx(DeviceAttributePciDeviceId)
#define cudaDevAttrTccDriver	__pfx(DeviceAttributeTccDriver)
#define cudaDevAttrMemoryClockRate	__pfx(DeviceAttributeMemoryClockRate)
#define cudaDevAttrMemoryBusWidth	__pfx(DeviceAttributeMemoryBusWidth)
#define cudaDevAttrL2CacheSize	__pfx(DeviceAttributeL2CacheSize)
#define cudaDevAttrMaxThreadsPerMultiProcessor	__pfx(DeviceAttributeMaxThreadsPerMultiProcessor)
#define cudaDevAttrAsyncEngineCount	__pfx(DeviceAttributeAsyncEngineCount)
#define cudaDevAttrUnifiedAddressing	__pfx(DeviceAttributeUnifiedAddressing)
#define cudaDevAttrMaxTexture1DLayeredWidth	__pfx(DeviceAttributeMaxTexture1DLayeredWidth)
#define cudaDevAttrMaxTexture1DLayeredLayers	__pfx(DeviceAttributeMaxTexture1DLayeredLayers)
#define cudaDevAttrResvered44	__pfx(DeviceAttributeResvered44)
#define cudaDevAttrMaxTexture2DGatherWidth	__pfx(DeviceAttributeMaxTexture2DGatherWidth)
#define cudaDevAttrMaxTexture2DGatherHeight	__pfx(DeviceAttributeMaxTexture2DGatherHeight)
#define cudaDevAttrMaxTexture3DWidthAlt	__pfx(DeviceAttributeMaxTexture3DWidthAlt)
#define cudaDevAttrMaxTexture3DHeightAlt	__pfx(DeviceAttributeMaxTexture3DHeightAlt)
#define cudaDevAttrMaxTexture3DDepthAlt	__pfx(DeviceAttributeMaxTexture3DDepthAlt)
#define cudaDevAttrPciDomainId	__pfx(DeviceAttributePciDomainId)
#define cudaDevAttrTexturePitchAlignment	__pfx(DeviceAttributeTexturePitchAlignment)
#define cudaDevAttrMaxTextureCubemapWidth	__pfx(DeviceAttributeMaxTextureCubemapWidth)
#define cudaDevAttrMaxTextureCubemapLayeredWidth	__pfx(DeviceAttributeMaxTextureCubemapLayeredWidth)
#define cudaDevAttrMaxTextureCubemapLayeredLayers	__pfx(DeviceAttributeMaxTextureCubemapLayeredLayers)
#define cudaDevAttrMaxSurface1DWidth	__pfx(DeviceAttributeMaxSurface1DWidth)
#define cudaDevAttrMaxSurface2DWidth	__pfx(DeviceAttributeMaxSurface2DWidth)
#define cudaDevAttrMaxSurface2DHeight	__pfx(DeviceAttributeMaxSurface2DHeight)
#define cudaDevAttrMaxSurface3DWidth	__pfx(DeviceAttributeMaxSurface3DWidth)
#define cudaDevAttrMaxSurface3DHeight	__pfx(DeviceAttributeMaxSurface3DHeight)
#define cudaDevAttrMaxSurface3DDepth	__pfx(DeviceAttributeMaxSurface3DDepth)
#define cudaDevAttrMaxSurface1DLayeredWidth	__pfx(DeviceAttributeMaxSurface1DLayeredWidth)
#define cudaDevAttrMaxSurface1DLayeredLayers	__pfx(DeviceAttributeMaxSurface1DLayeredLayers)
#define cudaDevAttrMaxSurface2DLayeredWidth	__pfx(DeviceAttributeMaxSurface2DLayeredWidth)
#define cudaDevAttrMaxSurface2DLayeredHeight	__pfx(DeviceAttributeMaxSurface2DLayeredHeight)
#define cudaDevAttrMaxSurface2DLayeredLayers	__pfx(DeviceAttributeMaxSurface2DLayeredLayers)
#define cudaDevAttrMaxSurfaceCubemapWidth	__pfx(DeviceAttributeMaxSurfaceCubemapWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredWidth	__pfx(DeviceAttributeMaxSurfaceCubemapLayeredWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredLayers	__pfx(DeviceAttributeMaxSurfaceCubemapLayeredLayers)
#define cudaDevAttrTexture1DLinearWidth	__pfx(DeviceAttributeTexture1DLinearWidth)
#define cudaDevAttrTexture2DLinearWidth	__pfx(DeviceAttributeTexture2DLinearWidth)
#define cudaDevAttrTexture2DLinearHeight	__pfx(DeviceAttributeTexture2DLinearHeight)
#define cudaDevAttrTexture2DLinearPitch	__pfx(DeviceAttributeTexture2DLinearPitch)
#define cudaDevAttrMaxTexture2DMipmappedWidth	__pfx(DeviceAttributeMaxTexture2DMipmappedWidth)
#define cudaDevAttrMaxTexture2DMipmappedHeight	__pfx(DeviceAttributeMaxTexture2DMipmappedHeight)
#define cudaDevAttrComputeCapabilityMajor	__pfx(DeviceAttributeComputeCapabilityMajor)
#define cudaDevAttrComputeCapabilityMinor	__pfx(DeviceAttributeComputeCapabilityMinor)
#define cudaDevAttrStreamPrioritiesSupported	__pfx(DeviceAttributeStreamPrioritiesSupported)
#define cudaDevAttrGlobalL1CacheSupported	__pfx(DeviceAttributeGlobalL1CacheSupported)
#define cudaDevAttrLocalL1CacheSupported	__pfx(DeviceAttributeLocalL1CacheSupported)
#define cudaDevAttrMaxSharedMemoryPerMultiprocessor	__pfx(DeviceAttributeMaxSharedMemoryPerMultiprocessor)
#define cudaDevAttrMaxRegistersPerMultiprocessor	__pfx(DeviceAttributeMaxRegistersPerMultiprocessor)
#define cudaDevAttrManagedMemory	__pfx(DeviceAttributeManagedMemory)
#define cudaDevAttrIsMultiGpuBoard	__pfx(DeviceAttributeIsMultiGpuBoard)
#define cudaDevAttrMultiGpuBoardGroupID	__pfx(DeviceAttributeMultiGpuBoardGroupID)
#define cudaDevAttrHostNativeAtomicSupported	__pfx(DeviceAttributeHostNativeAtomicSupported)
#define cudaDevAttrSingleToDoublePrecisionPerfRatio	__pfx(DeviceAttributeSingleToDoublePrecisionPerfRatio)
#define cudaDevAttrPageableMemoryAccess	__pfx(DeviceAttributePageableMemoryAccess)
#define cudaDevAttrConcurrentManagedAccess	__pfx(DeviceAttributeConcurrentManagedAccess)
#define cudaDevAttrComputePreemptionSupported	__pfx(DeviceAttributeComputePreemptionSupported)
#define cudaDevAttrCanUseHostPointerForRegisteredMem	__pfx(DeviceAttributeCanUseHostPointerForRegisteredMem)
#define cudaDevAttrReserved92	__pfx(DeviceAttributeReserved92)
#define cudaDevAttrReserved93	__pfx(DeviceAttributeReserved93)
#define cudaDevAttrReserved94	__pfx(DeviceAttributeReserved94)
#define cudaDevAttrCooperativeLaunch	__pfx(DeviceAttributeCooperativeLaunch)
#define cudaDevAttrCooperativeMultiDeviceLaunch	__pfx(DeviceAttributeCooperativeMultiDeviceLaunch)
#define cudaDevAttrMaxSharedMemoryPerBlockOptin	__pfx(DeviceAttributeMaxSharedMemoryPerBlockOptin)
#define cudaDevAttrCanFlushRemoteWrites	__pfx(DeviceAttributeCanFlushRemoteWrites)
#define cudaDevAttrHostRegisterSupported	__pfx(DeviceAttributeHostRegisterSupported)
#define cudaDevAttrPageableMemoryAccessUsesHostPageTables	__pfx(DeviceAttributePageableMemoryAccessUsesHostPageTables)
#define cudaDevAttrDirectManagedMemAccessFromHost	__pfx(DeviceAttributeDirectManagedMemAccessFromHost)
#define cudaDevAttrReserved102	__pfx(DeviceAttributeReserved102)
#define cudaDevAttrReserved103	__pfx(DeviceAttributeReserved103)
#define cudaDevAttrReserved104	__pfx(DeviceAttributeReserved104)
#define cudaDevAttrReserved105	__pfx(DeviceAttributeReserved105)
#define cudaDevAttrReserved107	__pfx(DeviceAttributeReserved107)
#define cudaDevAttrMaxPersistingL2CacheSize	__pfx(DeviceAttributeMaxPersistingL2CacheSize)
#define cudaDevAttrMaxAccessPolicyWindowSize	__pfx(DeviceAttributeMaxAccessPolicyWindowSize)
#define cudaDevAttrReserved110	__pfx(DeviceAttributeReserved110)
#define cudaDevAttrReservedSharedMemoryPerBlock	__pfx(DeviceAttributeReservedSharedMemoryPerBlock)
#define cudaDevAttrSparseHpccArraySupported	__pfx(DeviceAttributeSparseHpccArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported	__pfx(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported	__pfx(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported	__pfx(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported	__pfx(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions	__pfx(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering	__pfx(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes	__pfx(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch	__pfx(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingHpccArraySupported	__pfx(DeviceAttributeDeferredMappingHpccArraySupported)
#define cudaDevAttrReserved122	__pfx(DeviceAttributeReserved122)
#define cudaDevAttrReserved123	__pfx(DeviceAttributeReserved123)
#define cudaDevAttrReserved124	__pfx(DeviceAttributeReserved124)
#define cudaDevAttrIpcEventSupport	__pfx(DeviceAttributeIpcEventSupport)
#define cudaDevAttrMemSyncDomainCount	__pfx(DeviceAttributeMemSyncDomainCount)
#define cudaDevAttrReserved127	__pfx(DeviceAttributeReserved127)
#define cudaDevAttrReserved128	__pfx(DeviceAttributeReserved128)
#define cudaDevAttrReserved129	__pfx(DeviceAttributeReserved129)
#define cudaDevAttrNumaConfig	__pfx(DeviceAttributeNumaConfig)
#define cudaDevAttrNumaId	__pfx(DeviceAttributeNumaId)
#define cudaDevAttrReserved132	__pfx(DeviceAttributeReserved132)
#define cudaDevAttrMpsEnabled	__pfx(DeviceAttributeMpsEnabled)
#define cudaDevAttrHostNumaId	__pfx(DeviceAttributeHostNumaId)
#define cudaDevAttrWaveSize	__pfx(DeviceAttributeWaveSize)
#define cudaDevAttrHdpMemFlushCntl	__pfx(DeviceAttributeHdpMemFlushCntl)
#define cudaDevAttrHdpRegFlushCntl	__pfx(DeviceAttributeHdpRegFlushCntl)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedFunc	__pfx(DeviceAttributeCooperativeMultiDeviceUnmatchedFunc)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim	__pfx(DeviceAttributeCooperativeMultiDeviceUnmatchedGridDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim	__pfx(DeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem	__pfx(DeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem)
#define cudaDevAttrAsicRevision	__pfx(DeviceAttributeAsicRevision)
#define cudaDevAttrVirtualMemoryManagementSupported	__pfx(DeviceAttributeVirtualMemoryManagementSupported)
#define cudaDevAttrHandleTypePosixFileDescriptorSupported	__pfx(DeviceAttributeHandleTypePosixFileDescriptorSupported)
#define cudaDevAttrHandleTypeWin32HandleSupported	__pfx(DeviceAttributeHandleTypeWin32HandleSupported)
#define cudaDevAttrGenericCompressionSupported	__pfx(DeviceAttributeGenericCompressionSupported)
#define cudaDevAttrCanUseStreamWaitValue	__pfx(DeviceAttributeCanUseStreamWaitValue)
#define cudaDevAttrCanUseStreamMemOps	__pfx(DeviceAttributeCanUseStreamMemOps)
#define cudaDevAttrCanUseStreamWaitWaitValueNor	__pfx(DeviceAttributeCanUseStreamWaitWaitValueNor)
#define cudaDevAttrLocalSocketId	__pfx(DeviceAttributeLocalSocketId)
#define cudaDevAttrSocketId	__pfx(DeviceAttributeSocketId)
#define cudaDevAttrPeerSocketId	__pfx(DeviceAttributePeerSocketId)
#define cudaDevAttrMulticastSupported	__pfx(DeviceAttributeMulticastSupported)
#endif	/* HAVE_HCCL */

#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	__pfx(DeviceGetP2PAttribute(v, attr, src, dst))
#define cudaDevP2PAttrPerformanceRank	__pfx(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported	__pfx(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported	__pfx(DevP2PAttrNativeAtomicSupported)

#define cudaDeviceCanAccessPeer(can, devfrom, devto) __pfx(DeviceCanAccessPeer(can, devfrom, devto))
#define cudaDeviceEnablePeerAccess(peerdev, flag)	__pfx(DeviceEnablePeerAccess(peerdev, flag))
#define cudaDeviceDisablePeerAccess(dev)	__pfx(DeviceDisablePeerAccess(dev))

#define cudaDeviceSynchronize()	__pfx(DeviceSynchronize())

/**
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 */
#define cublasGetStatusString(status)	__pfx(blasGetStatusString(status))
#define cublasStatus_t	__pfx(blasStatus_t)
#define CUBLAS_STATUS_SUCCESS	__PFX(BLAS_STATUS_SUCCESS)
#define CUBLAS_STATUS_NOT_INITIALIZED	__PFX(BLAS_STATUS_NOT_INITIALIZED)
#define CUBLAS_STATUS_ALLOC_FAILED	__PFX(BLAS_STATUS_ALLOC_FAILED)
#define CUBLAS_STATUS_INVALID_VALUE	__PFX(BLAS_STATUS_INVALID_VALUE)
#define CUBLAS_STATUS_ARCH_MISMATCH	__PFX(BLAS_STATUS_ARCH_MISMATCH)
#define CUBLAS_STATUS_MAPPING_ERROR	__PFX(BLAS_STATUS_MAPPING_ERROR)
#define CUBLAS_STATUS_EXECUTION_FAILED	__PFX(BLAS_STATUS_EXECUTION_FAILED)
#define CUBLAS_STATUS_INTERNAL_ERROR	__PFX(BLAS_STATUS_INTERNAL_ERROR)
#define CUBLAS_STATUS_NOT_SUPPORTED	__PFX(BLAS_STATUS_NOT_SUPPORTED)

#define cublasHandle_t	__pfx(blasHandle_t)
#define cublasCreate(handle)	__pfx(blasCreate(handle))
#define cublasDestroy(handle)	__pfx(blasDestroy(handle))

#define cublasGetVersion(handle, pversion)	__pfx(blasGetVersion(handle, pversion))
#define cublasLtGetVersion()	__pfx(blasLtGetVersion())
#define cublasGetProperty(type, pvalue)	__pfx(blasGetProperty(type, pvalue))

/**
 * The cublasOperation_t type indicates which operation needs to be performed
 * with the dense matrix.
 */
#define cublasOperation_t	__pfx(blasOperation_t)
/* The non-transpose operation is selected. */
#define CUBLAS_OP_N	__PFX(BLAS_OP_N)
/* The transpose operation is selected. */
#define CUBLAS_OP_T	__PFX(BLAS_OP_T)
/* The conjugate transpose operation is selected. */
#define CUBLAS_OP_C	__PFX(BLAS_OP_C)
#define CUBLAS_OP_HERMITAN	__PFX(BLAS_OP_HERMITAN)
#define CUBLAS_OP_CONJG	__PFX(BLAS_OP_CONJG)

#define cublasFillMode_t	__pfx(blasFillMode_t)
#define CUBLAS_FILL_MODE_LOWER	__PFX(BLAS_FILL_MODE_LOWER)
#define CUBLAS_FILL_MODE_UPPER	__PFX(BLAS_FILL_MODE_UPPER)
#define CUBLAS_FILL_MODE_FULL	__PFX(BLAS_FILL_MODE_FULL)

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	__pfx(blasSetMatrix(rows, cols, elemsize, A, ola, B, ldb))
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	__pfx(blasGetMatrix(rows, cols, elemsize, A, ola, B, ldb))

#define cublasSetVector(n, elemSize, x, incx, y, incy) \
	__pfx(blasSetVector(n, elemSize, x, incx, y, incy))
#define cublasGetVector(n, elemSize, x, incx, y, incy) \
	__pfx(blasGetVector(n, elemSize, x, incx, y, incy))

/**
 * The cublasPointerMode_t type indicates whether the scalar values are passed
 * by reference on the host or device.
 */
#define cublasPointerMode_t	__pfx(blasPointerMode_t)
#define CUBLAS_POINTER_MODE_HOST	__PFX(BLAS_POINTER_MODE_HOST)
#define CUBLAS_POINTER_MODE_DEVICE	__PFX(BLAS_POINTER_MODE_DEVICE)

#define cublasGetPointerMode(handle, mode)	__pfx(blasGetPointerMode(handle, mode))
#define cublasSetPointerMode(handle, mode)	__pfx(blasSetPointerMode(handle, mode))

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx)	__pfx(blasSscal(handle, n, alpha, x, incx))
#define cublasDscal(handle, n, alpha, x, incx)	__pfx(blasDscal(handle, n, alpha, x, incx))
#define cublasCscal(handle, n, alpha, x, incx)	__pfx(blasCscal(handle, n, alpha, x, incx))
#define cublasCsscal(handle, n, alpha, x, incx)	__pfx(blasCsscal(handle, n, alpha, x, incx))
#define cublasZscal(handle, n, alpha, x, incx)	__pfx(blasZscal(handle, n, alpha, x, incx))
#define cublasZdscal(handle, n, alpha, x, incx)	__pfx(blasZdscal(handle, n, alpha, x, incx))

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult)	__pfx(blasIsamax(handle, n, x, incx, presult))
#define cublasIdamax(handle, n, x, incx, presult)	__pfx(blasIdamax(handle, n, x, incx, presult))
#define cublasIcamax(handle, n, x, incx, presult)	__pfx(blasIcamax(handle, n, x, incx, presult))
#define cublasIzamax(handle, n, x, incx, presult)	__pfx(blasIzamax(handle, n, x, incx, presult))

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult)	__pfx(blasIsamin(handle, n, x, incx, presult))
#define cublasIdamin(handle, n, x, incx, presult)	__pfx(blasIdamin(handle, n, x, incx, presult))
#define cublasIcamin(handle, n, x, incx, presult)	__pfx(blasIcamin(handle, n, x, incx, presult))
#define cublasIzamin(handle, n, x, incx, presult)	__pfx(blasIzamin(handle, n, x, incx, presult))

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult)	__pfx(blasSasum(handle, n, x, incx, presult))
#define cublasDasum(handle, n, x, incx, presult)	__pfx(blasDasum(handle, n, x, incx, presult))
#define cublasScasum(handle, n, x, incx, presult)	__pfx(blasScasum(handle, n, x, incx, presult))
#define cublasDzasum(handle, n, x, incx, presult)	__pfx(blasDzasum(handle, n, x, incx, presult))

/**
 * This function multiplies the vector x by the scalar alpha and adds it to
 * the vector y overwriting the latest vector with the result.
 *
 * y[j] = alpha x x[k] + y[j]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasSaxpy(handle, n, alpha, x, incx, y, incy)	__pfx(blasSaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasDaxpy(handle, n, alpha, x, incx, y, incy)	__pfx(blasDaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasCaxpy(handle, n, alpha, x, incx, y, incy)	__pfx(blasCaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasZaxpy(handle, n, alpha, x, incx, y, incy)	__pfx(blasZaxpy(handle, n, alpha, x, incx, y, incy))

/**
 * This function copies the vector x into the vector y.
 *
 * y[j] = x[k]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasScopy(handle, n, x, incx, y, incy)	__pfx(blasScopy(handle, n, x, incx, y, incy))
#define cublasDcopy(handle, n, x, incx, y, incy)	__pfx(blasDcopy(handle, n, x, incx, y, incy))
#define cublasCcopy(handle, n, x, incx, y, incy)	__pfx(blasCcopy(handle, n, x, incx, y, incy))
#define cublasZcopy(handle, n, x, incx, y, incy)	__pfx(blasZcopy(handle, n, x, incx, y, incy))

/**
 * This function computes the dot product of vectors x and y.
 */
#define cublasSdot(handle, n, x, incx, y, incy, presult)	__pfx(blasSdot(handle, n, x, incx, y, incy, presult))
#define cublasDdot(handle, n, x, incx, y, incy, presult)	__pfx(blasDdot(handle, n, x, incx, y, incy, presult))
#define cublasCdotu(handle, n, x, incx, y, incy, presult)	__pfx(blasCdotu(handle, n, x, incx, y, incy, presult))
#define cublasCdotc(handle, n, x, incx, y, incy, presult)	__pfx(blasCdotc(handle, n, x, incx, y, incy, presult))
#define cublasZdotu(handle, n, x, incx, y, incy, presult)	__pfx(blasZdotu(handle, n, x, incx, y, incy, presult))
#define cublasZdotc(handle, n, x, incx, y, incy, presult)	__pfx(blasZdotc(handle, n, x, incx, y, incy, presult))

/**
 * This function computes the Euclidean norm of the vector x.
 */
#define cublasSnrm2(handle, n, x, incx, presult)	__pfx(blasSnrm2(handle, n, x, incx, presult))
#define cublasDnrm2(handle, n, x, incx, presult)	__pfx(blasDnrm2(handle, n, x, incx, presult))
#define cublasScnrm2(handle, n, x, incx, presult)	__pfx(blasScnrm2(handle, n, x, incx, presult))
#define cublasDznrm2(handle, n, x, incx, presult)	__pfx(blasDznrm2(handle, n, x, incx, presult))

/**
 * This function applies Givens rotation matrix.
 */
#define cublasSrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasSrot(handle, n, x, incx, y, incy, c, s))
#define cublasDrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasDrot(handle, n, x, incx, y, incy, c, s))
#define cublasCrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasCrot(handle, n, x, incx, y, incy, c, s))
#define cublasCsrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasCsrot(handle, n, x, incx, y, incy, c, s))
#define cublasZrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasZrot(handle, n, x, incx, y, incy, c, s))
#define cublasZdrot(handle, n, x, incx, y, incy, c, s)	__pfx(blasZdrot(handle, n, x, incx, y, incy, c, s))

/**
 * This function constructs the Givens rotation matrix.
 */
#define cublasSrotg(handle, a, b, c, s)	__pfx(blasSrotg(handle, a, b, c, s))
#define cublasDrotg(handle, a, b, c, s)	__pfx(blasDrotg(handle, a, b, c, s))
#define cublasCrotg(handle, a, b, c, s)	__pfx(blasCrotg(handle, a, b, c, s))
#define cublasZrotg(handle, a, b, c, s)	__pfx(blasZrotg(handle, a, b, c, s))

#define cublasSrotm(handle, n, x, incx, y, incy, param)	__pfx(blasSrotm(handle, n, x, incx, y, incy, param))
#define cublasDrotm(handle, n, x, incx, y, incy, param)	__pfx(blasDrotm(handle, n, x, incx, y, incy, param))

/**
 * This function performs the matrix-matrix multiplication.
 *
 * C = alpha op(A) op(B) + beta C
 */
/**
 * cublasStatus_t cublasSgemm(cublasHandle_t handle,
 *                          cublasOperation_t transa, cublasOperation_t transb,
 *                          int m, int n, int k,
 *                          const float           *alpha,
 *                          const float           *A, int lda,
 *                          const float           *B, int ldb,
 *                          const float           *beta,
 *                          float           *C, int ldc)
 */
#define cublasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__pfx(blasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__pfx(blasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__pfx(blasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__pfx(blasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__pfx(blasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))

#define cublasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy) \
	__pfx(blasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy))

/**
 * cublasStatus_t cublasGemmEx(cublasHandle_t handle,
 *                          cublasOperation_t transa,
 *                          cublasOperation_t transb,
 *                          int m,
 *                          int n,
 *                          int k,
 *                          const void    *alpha,
 *                          const void     *A,
 *                          cudaDataType_t Atype,
 *                          int lda,
 *                          const void     *B,
 *                          cudaDataType_t Btype,
 *                          int ldb,
 *                          const void    *beta,
 *                          void           *C,
 *                          cudaDataType_t Ctype,
 *                          int ldc,
 *                          cublasComputeType_t computeType,
 *                          cublasGemmAlgo_t algo)
 */
#define cublasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
		     B, Btype, ldb, beta, C, Ctype, ldc, computeType, algo) \
	__pfx(blasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
		     B, Btype, ldb, beta, C, Ctype, ldc, computeType, algo))

/**
 * cublasStatus_t cublasSgemmEx(cublasHandle_t handle,
 *                          cublasOperation_t transa,
 *                          cublasOperation_t transb,
 *                          int m,
 *                          int n,
 *                          int k,
 *                          const float    *alpha,
 *                          const void     *A,
 *                          cudaDataType_t Atype,
 *                          int lda,
 *                          const void     *B,
 *                          cudaDataType_t Btype,
 *                          int ldb,
 *                          const float    *beta,
 *                          void           *C,
 *                          cudaDataType_t Ctype,
 *                          int ldc)
 */
#define cublasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
		      B, Btype, ldb, beta, C, Ctype, ldc) \
	__pfx(blasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
		      B, Btype, ldb, beta, C, Ctype, ldc))

#define cublasLtHandle_t	__pfx(blasLtHandle_t)
#define cublasLtCreate(phandle)	__pfx(blasLtCreate(phandle))
#define cublasLtDestroy(handle)	__pfx(blasLtDestroy(handle))

#define cublasLtMatmulDesc_t	__pfx(blasLtMatmulDesc_t)
/**
 * cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
 *                                         cublasComputeType_t computeType,
 *                                         cudaDataType_t scaleType);
 *
 * This function creates a matrix multiply descriptor by allocating the memory
 * needed to hold its opaque structure.
 */
#define cublasLtMatmulDescCreate(pdesc, computeType, scaleType) \
	__pfx(blasLtMatmulDescCreate(pdesc, computeType, scaleType))
#define cublasLtMatmulDescDestroy(desc)	__pfx(blasLtMatmulDescDestroy(desc))

#define cublasLtMatmulDescAttributes_t	__pfx(blasLtMatmulDescAttributes_t)
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE	__PFX(BLASLT_MATMUL_DESC_COMPUTE_TYPE)
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE		__PFX(BLASLT_MATMUL_DESC_SCALE_TYPE)
#define CUBLASLT_MATMUL_DESC_POINTER_MODE	__PFX(BLASLT_MATMUL_DESC_POINTER_MODE)
/* more ... */

#define cublasLtMatmulHeuristicResult_t	__pfx(blasLtMatmulHeuristicResult_t)

#define cublasLtMatrixLayout_t	__pfx(blasLtMatrixLayout_t)
#define cublasLtMatrixLayoutCreate(playout, type, rows, cols, ld) \
	__pfx(blasLtMatrixLayoutCreate(playout, type, rows, cols, ld))
#define cublasLtMatrixLayoutDestroy(layout)	__pfx(blasLtMatrixLayoutDestroy(layout))

#define cublasLtMatrixLayoutAttribute_t	__pfx(blasLtMatrixLayoutAttribute_t)

#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
	__pfx(blasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten))

#define CUBLASLT_MATRIX_LAYOUT_ROWS	__PFX(BLASLT_MATRIX_LAYOUT_ROWS)
#define CUBLASLT_MATRIX_LAYOUT_COLS	__PFX(BLASLT_MATRIX_LAYOUT_COLS)
#define CUBLASLT_MATRIX_LAYOUT_LD	__PFX(BLASLT_MATRIX_LAYOUT_LD)
#define CUBLASLT_MATRIX_LAYOUT_TYPE	__PFX(BLASLT_MATRIX_LAYOUT_TYPE)

#define cublasLtMatmulAlgo_t	__pfx(blasLtMatmulAlgo_t)
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT	__PFX(BLASLT_ALGO_CAP_SPLITK_SUPPORT)
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK	__PFX(BLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK)
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT	__PFX(BLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT)
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT	__PFX(BLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT)
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT	__PFX(BLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT)
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT	__PFX(BLASLT_ALGO_CAP_UPLO_SUPPORT)
#define CUBLASLT_ALGO_CAP_TILE_IDS	__PFX(BLASLT_ALGO_CAP_TILE_IDS)
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX	__PFX(BLASLT_ALGO_CAP_CUSTOM_OPTION_MAX)
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER	__PFX(BLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER)
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK	__PFX(BLASLT_ALGO_CAP_POINTER_MODE_MASK)
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK	__PFX(BLASLT_ALGO_CAP_EPILOGUE_MASK)
#define CUBLASLT_ALGO_CAP_STAGES_IDS	__PFX(BLASLT_ALGO_CAP_STAGES_IDS)
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE	__PFX(BLASLT_ALGO_CAP_LD_NEGATIVE)
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS	__PFX(BLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES	__PFX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES	__PFX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES	__PFX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES	__PFX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES)
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC	__PFX(BLASLT_ALGO_CAP_ATOMIC_SYNC)

#define cublasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt) \
	__pfx(blasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt))
#define cublasLtMatmulPreferenceDestroy(pref)	__pfx(blasLtMatmulPreferenceDestroy(pref))

#define cublasLtMatmulPreference_t	__pfx(blasLtMatmulPreference_t)
#define cublasLtMatmulPreferenceCreate(preference)	__pfx(blasLtMatmulPreferenceCreate(preference))

#define cublasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size) \
	__pfx(blasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size))

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES	__PFX(BLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES)

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream) \
	__pfx(blasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream))

/**
 * cublasGemmAlgo_t type is an enumerant to specify the algorithm for
 * matrix-matrix multiplication.
 */
#define cublasGemmAlgo_t	__pfx(blasGemmAlgo_t)
#define CUBLAS_GEMM_DEFAULT	__PFX(BLAS_GEMM_DEFAULT)
#define CUBLAS_GEMM_ALGO0	__PFX(BLAS_GEMM_ALGO0)
#define CUBLAS_GEMM_ALGO1	__PFX(BLAS_GEMM_ALGO1)
#define CUBLAS_GEMM_ALGO2	__PFX(BLAS_GEMM_ALGO2)
#define CUBLAS_GEMM_ALGO3	__PFX(BLAS_GEMM_ALGO3)
#define CUBLAS_GEMM_ALGO4	__PFX(BLAS_GEMM_ALGO4)
#define CUBLAS_GEMM_ALGO5	__PFX(BLAS_GEMM_ALGO5)
#define CUBLAS_GEMM_ALGO6	__PFX(BLAS_GEMM_ALGO6)
#define CUBLAS_GEMM_ALGO7	__PFX(BLAS_GEMM_ALGO7)
#define CUBLAS_GEMM_ALGO8	__PFX(BLAS_GEMM_ALGO8)
#define CUBLAS_GEMM_ALGO9	__PFX(BLAS_GEMM_ALGO9)
#define CUBLAS_GEMM_ALGO10	__PFX(BLAS_GEMM_ALGO10)
#define CUBLAS_GEMM_ALGO11	__PFX(BLAS_GEMM_ALGO11)
#define CUBLAS_GEMM_ALGO12	__PFX(BLAS_GEMM_ALGO12)
#define CUBLAS_GEMM_ALGO13	__PFX(BLAS_GEMM_ALGO13)
#define CUBLAS_GEMM_ALGO14	__PFX(BLAS_GEMM_ALGO14)
#define CUBLAS_GEMM_ALGO15	__PFX(BLAS_GEMM_ALGO15)
#define CUBLAS_GEMM_ALGO16	__PFX(BLAS_GEMM_ALGO16)
#define CUBLAS_GEMM_ALGO17	__PFX(BLAS_GEMM_ALGO17)
#define CUBLAS_GEMM_ALGO18	__PFX(BLAS_GEMM_ALGO18)
#define CUBLAS_GEMM_ALGO19	__PFX(BLAS_GEMM_ALGO19)
#define CUBLAS_GEMM_ALGO20	__PFX(BLAS_GEMM_ALGO20)
#define CUBLAS_GEMM_ALGO21	__PFX(BLAS_GEMM_ALGO21)
#define CUBLAS_GEMM_ALGO22	__PFX(BLAS_GEMM_ALGO22)
#define CUBLAS_GEMM_ALGO23	__PFX(BLAS_GEMM_ALGO23)
#define CUBLAS_GEMM_DEFAULT_TENSOR_OP	__PFX(BLAS_GEMM_DEFAULT_TENSOR_OP)
#define CUBLAS_GEMM_ALGO0_TENSOR_OP	__PFX(BLAS_GEMM_ALGO0_TENSOR_OP)
#define CUBLAS_GEMM_ALGO1_TENSOR_OP	__PFX(BLAS_GEMM_ALGO1_TENSOR_OP)
#define CUBLAS_GEMM_ALGO2_TENSOR_OP	__PFX(BLAS_GEMM_ALGO2_TENSOR_OP)
#define CUBLAS_GEMM_ALGO3_TENSOR_OP	__PFX(BLAS_GEMM_ALGO3_TENSOR_OP)
#define CUBLAS_GEMM_ALGO4_TENSOR_OP	__PFX(BLAS_GEMM_ALGO4_TENSOR_OP)
#define CUBLAS_GEMM_ALGO5_TENSOR_OP	__PFX(BLAS_GEMM_ALGO5_TENSOR_OP)
#define CUBLAS_GEMM_ALGO6_TENSOR_OP	__PFX(BLAS_GEMM_ALGO6_TENSOR_OP)
#define CUBLAS_GEMM_ALGO7_TENSOR_OP	__PFX(BLAS_GEMM_ALGO7_TENSOR_OP)
#define CUBLAS_GEMM_ALGO8_TENSOR_OP	__PFX(BLAS_GEMM_ALGO8_TENSOR_OP)
#define CUBLAS_GEMM_ALGO9_TENSOR_OP	__PFX(BLAS_GEMM_ALGO9_TENSOR_OP)
#define CUBLAS_GEMM_ALGO10_TENSOR_OP	__PFX(BLAS_GEMM_ALGO10_TENSOR_OP)
#define CUBLAS_GEMM_ALGO11_TENSOR_OP	__PFX(BLAS_GEMM_ALGO11_TENSOR_OP)
#define CUBLAS_GEMM_ALGO12_TENSOR_OP	__PFX(BLAS_GEMM_ALGO12_TENSOR_OP)
#define CUBLAS_GEMM_ALGO13_TENSOR_OP	__PFX(BLAS_GEMM_ALGO13_TENSOR_OP)
#define CUBLAS_GEMM_ALGO14_TENSOR_OP	__PFX(BLAS_GEMM_ALGO14_TENSOR_OP)
#define CUBLAS_GEMM_ALGO15_TENSOR_OP	__PFX(BLAS_GEMM_ALGO15_TENSOR_OP)
#define CUBLAS_GEMM_AUTOTUNE	__PFX(BLAS_GEMM_AUTOTUNE)

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t	__pfx(blasComputeType_t)
/**
 * This is the default and highest-performance mode for 16-bit half precision
 * floating point and all compute and intermediate storage precisions with at
 * least 16-bit half precision. Tensor Cores will be used whenever possible.
 */
#define CUBLAS_COMPUTE_16F	__PFX(BLAS_COMPUTE_16F)
/**
 * This mode uses 16-bit half precision floating point standardized arithmetic
 * for all phases of calculations and is primarily intended for numerical
 * robustness studies, testing, and debugging. This mode might not be as
 * performant as the other modes since it disables use of tensor cores.
 */
#define CUBLAS_COMPUTE_16F_PEDANTIC	__PFX(BLAS_COMPUTE_16F_PEDANTIC)
/**
 * This is the default 32-bit single precision floating point and uses compute
 * and intermediate storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32F	__PFX(BLAS_COMPUTE_32F)
#define CUBLAS_COMPUTE_32F_PEDANTIC	__PFX(BLAS_COMPUTE_32F_PEDANTIC)
/**
 * Allows the library to use Tensor Cores with automatic down-conversion and
 * 16-bit half-precision compute for 32-bit input and output matrices.
 */
#define CUBLAS_COMPUTE_32F_FAST_16F	__PFX(BLAS_COMPUTE_32F_FAST_16F)
#define CUBLAS_COMPUTE_32F_FAST_16BF	__PFX(BLAS_COMPUTE_32F_FAST_16BF)
#define CUBLAS_COMPUTE_32F_FAST_TF32	__PFX(BLAS_COMPUTE_32F_FAST_TF32)
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9	__PFX(BLAS_COMPUTE_32F_EMULATED_16BFX9)
/**
 * This is the default 64-bit double precision floating point and uses compute
 * and intermediate storage precisions of at least 64-bits.
 */
#define CUBLAS_COMPUTE_64F	__PFX(BLAS_COMPUTE_64F)
#define CUBLAS_COMPUTE_64F_PEDANTIC	__PFX(BLAS_COMPUTE_64F_PEDANTIC)
/**
 * This is the default 32-bit integer mode and uses compute and intermediate
 * storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32I	__PFX(BLAS_COMPUTE_32I)
#define CUBLAS_COMPUTE_32I_PEDANTIC	__PFX(BLAS_COMPUTE_32I_PEDANTIC)

/**
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/library_types.h
 */
#define cudaDataType_t	hpccDataType_t
#define cudaDataType	hpccDataType
/* The data type is a 16-bit real half precision floating-point */
#define CUDA_R_16F	HPCC_R_16F
/* The data type is a 32-bit structure comprised of two half precision
 * floating-points representing a complex number. */
#define CUDA_C_16F	HPCC_C_16F
/* The data type is a 16-bit real bfloat16 floating-point */
#define CUDA_R_16BF	HPCC_R_16BF
#define CUDA_C_16BF	HPCC_C_16BF
#define CUDA_R_32F	HPCC_R_32F
#define CUDA_C_32F	HPCC_C_32F
#define CUDA_R_64F	HPCC_R_64F
#define CUDA_C_64F	HPCC_C_64F
/* The data type is a 8-bit real signed integer */
#define CUDA_R_4I	HPCC_R_4I
#define CUDA_C_4I	HPCC_C_4I
#define CUDA_R_4U	HPCC_R_4U
#define CUDA_C_4U	HPCC_C_4U
#define CUDA_R_8I	HPCC_R_8I
#define CUDA_C_8I	HPCC_C_8I
#define CUDA_R_8U	HPCC_R_8U
#define CUDA_C_8U	HPCC_C_8U
#define CUDA_R_16I	HPCC_R_16I
#define CUDA_C_16I	HPCC_C_16I
#define CUDA_R_16U	HPCC_R_16U
#define CUDA_C_16U	HPCC_C_16U
#define CUDA_R_32I	HPCC_R_32I
#define CUDA_C_32I	HPCC_C_32I
#define CUDA_R_32U	HPCC_R_32U
#define CUDA_C_32U	HPCC_C_32U
#define CUDA_R_64I	HPCC_R_64I
#define CUDA_C_64I	HPCC_C_64I
#define CUDA_R_64U	HPCC_R_64U
#define CUDA_C_64U	HPCC_C_64U
#define CUDA_R_8F_E4M3	HPCC_R_8F_E4M3
#define CUDA_R_8F_UE4M3	HPCC_R_8F_UE4M3
#define CUDA_R_8F_E5M2	HPCC_R_8F_E5M2
#define CUDA_R_8F_UE8M0	HPCC_R_8F_UE8M0
#define CUDA_R_6F_E2M3	HPCC_R_6F_E2M3
#define CUDA_R_6F_E3M2	HPCC_R_6F_E3M2
#define CUDA_R_4F_E2M1	HPCC_R_4F_E2M1

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */
#define cuComplex	__pfx(Complex)
#define cuDoubleComplex	__pfx(DoubleComplex)

/**
 * refs
 * - https://docs.nvidia.com/cuda/curand/group__HOST.html
 */
#define curandStatus_t	__pfx(randStatus_t)
#define CURAND_STATUS_SUCCESS	__PFX(RAND_STATUS_SUCCESS)
#define CURAND_STATUS_SUCCESS	__PFX(RAND_STATUS_SUCCESS)
#define CURAND_STATUS_VERSION_MISMATCH	__PFX(RAND_STATUS_VERSION_MISMATCH)
#define CURAND_STATUS_NOT_INITIALIZED	__PFX(RAND_STATUS_NOT_INITIALIZED)
#define CURAND_STATUS_ALLOCATION_FAILED	__PFX(RAND_STATUS_ALLOCATION_FAILED)
#define CURAND_STATUS_TYPE_ERROR	__PFX(RAND_STATUS_TYPE_ERROR)
#define CURAND_STATUS_OUT_OF_RANGE	__PFX(RAND_STATUS_OUT_OF_RANGE)
#define CURAND_STATUS_LENGTH_NOT_MULTIPLE	__PFX(RAND_STATUS_LENGTH_NOT_MULTIPLE)
#define CURAND_STATUS_DOUBLE_PRECISION_REQUIRED	__PFX(RAND_STATUS_DOUBLE_PRECISION_REQUIRED)
#define CURAND_STATUS_LAUNCH_FAILURE	__PFX(RAND_STATUS_LAUNCH_FAILURE)
#define CURAND_STATUS_PREEXISTING_FAILURE	__PFX(RAND_STATUS_PREEXISTING_FAILURE)
#define CURAND_STATUS_INITIALIZATION_FAILED	__PFX(RAND_STATUS_INITIALIZATION_FAILED)
#define CURAND_STATUS_ARCH_MISMATCH	__PFX(RAND_STATUS_ARCH_MISMATCH)
#define CURAND_STATUS_INTERNAL_ERROR	__PFX(RAND_STATUS_INTERNAL_ERROR)
#define CURAND_STATUS_NOT_IMPLEMENTED	__PFX(RAND_STATUS_NOT_IMPLEMENTED)

#define curandGetVersion(version)	__pfx(randGetVersion(version))
