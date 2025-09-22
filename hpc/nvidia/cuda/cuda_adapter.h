// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#if defined(HAVE_HCCL)
/* Metax has CUDA-compatible APIs */
# define __cu(name)	hc##name
# define __cuda(name)	hc##name
# define __CU(name)	HC##name
# define __CUDA(name)	HC_##name
# define __CUDA_ERROR(name)	HCC_STATUS_##name
# define __nv(name)	hc##name
# define __NV(name)	HC##name
#elif defined(HAVE_HIP)
# define __cu(name)	hip##name
# define __cuda(name)	hip##name
# define __CU(name)	HIP##name
# define __CUDA(name)	HIP_##name
# define __CUDA_ERROR(name)	HIP_##name
# define __nv(name)	hip##name
# define __NV(name)	HIP##name
#elif !defined(__cu) || !defined(__CU) || !defined(__CUDA)
# error "Must define __cu(), __cuda(), __CU(), __CUDA(), __CUDA_ERROR(), __nv(), __NV() macros, or define HAVE_HCCL, HAVE_HIP"
#endif

/* typedef hcError_t	cudaError_t; */
#define cudaError_t	__cuda(Error_t)
#define cudaSuccess	__cuda(Success)
#define cudaErrorInvalidValue	__cuda(ErrorInvalidValue)
#define cudaErrorMemoryAllocation	__cuda(ErrorMemoryAllocation)

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
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html
 */
#define cudaMalloc(pp, sz)	__cuda(Malloc(pp, sz))
#define cudaFree(ptr)	__cuda(Free(ptr))
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
#define cudaMemcpy(dev, host, size, flag)	__cuda(Memcpy(dev, host, size, flag))
#define cudaMemcpyKind	__cuda(MemcpyKind)
#define cudaMemcpyHostToDevice	__cuda(MemcpyHostToDevice)
#define cudaMemcpyDeviceToHost	__cuda(MemcpyDeviceToHost)
#define cudaMemcpyDeviceToDevice	__cuda(MemcpyDeviceToDevice)

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

/**
 * CUDA 13
 * cudaError_t cudaMemcpyPeer(void *dst, int dstDevice, const void *src, int srcDevice,
 *                            size_t count);
 *
 * HIP
 * hipError_t hipMemcpyPeer(void* dst, int dstDeviceId, const void* src, int srcDeviceId,
 *                          size_t sizeBytes);
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

#ifdef HAVE_HIP
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

/**
 * CUDA: typedef __attribute__((device_builtin)) struct CUevent_st *cudaEvent_t;
 * HPCC: typedef struct HCevent_st *hcEvent_t;
 * HIP: typedef struct ihipEvent_t* hipEvent_t;
 */
#ifdef HAVE_HIP
#define CUevent_st	ihipEvent_t
#else
#define CUevent_st	__CU(event_st)
#endif
#define cudaEvent_t	__cuda(Event_t)
#define cudaEventCreate(pe)	__cuda(EventCreate(pe))
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
 * cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim,
 *                              void **args, size_t sharedMem, cudaStream_t stream);
 * hcError_t hcLaunchKernel(const void *function_address, dim3 numBlocks, dim3 dimBlocks,
 *                          void **args, size_t sharedMemBytes), hcStream_t stream);
 */
#define cudaLaunchKernel(func, g, b, args, mem, stream) \
	__cuda(LaunchKernel(func, g, b, args, mem, stream))

/**
 * CUDA 12:
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
 */

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
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
#define CUstream_st	__CU(stream_st)
#define cudaStream_t	__cuda(Stream_t)
#define cudaStreamCreate(pstream)	__cuda(StreamCreate(pstream))
#define cudaStreamSynchronize(stream)	__cuda(StreamSynchronize(stream))
#define cudaStreamDestroy(stream)	__cuda(StreamDestroy(stream))

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

#define cudaStreamCaptureStatus	__cuda(StreamCaptureStatus)

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
#if defined(HAVE_HCCL) || defined(HAVE_HIP)
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
#if defined(HAVE_HCCL) || defined(HAVE_HIP)
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
#define cudaDevAttrSparseHpccArraySupported	__cuda(DeviceAttributeSparseHpccArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported	__cuda(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported	__cuda(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported	__cuda(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported	__cuda(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions	__cuda(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering	__cuda(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes	__cuda(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch	__cuda(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingHpccArraySupported	__cuda(DeviceAttributeDeferredMappingHpccArraySupported)
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
#endif	/* HAVE_HCCL */

#define cudaDeviceP2PAttr	__cuda(DeviceP2PAttr)
/**
 * cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr,
 *                                       int srcDevice, int dstDevice);
 */
#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	__cuda(DeviceGetP2PAttribute(v, attr, src, dst))
#define cudaDevP2PAttrPerformanceRank	__cuda(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported	__cuda(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported	__cuda(DevP2PAttrNativeAtomicSupported)

/**
 * cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice);
 */
#define cudaDeviceCanAccessPeer(can, devfrom, devto) __cuda(DeviceCanAccessPeer(can, devfrom, devto))
#define cudaDeviceEnablePeerAccess(peerdev, flag)	__cuda(DeviceEnablePeerAccess(peerdev, flag))
/**
 * cudaError_t cudaDeviceDisablePeerAccess(int peerDevice);
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

/**
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 *
 * CUDA V12.2.140
 * const char* cublasGetStatusString(cublasStatus_t status);
 *
 * HIP:
 * const char* hipblasStatusToString(hipblasStatus_t status);
 */
#ifdef HAVE_HIP
#define cublasGetStatusString(status)	hipblasStatusToString(status)
#else
#define cublasGetStatusString(status)	__cu(blasGetStatusString(status))
#endif
#define cublasStatus_t	__cu(blasStatus_t)
#define CUBLAS_STATUS_SUCCESS	__CU(BLAS_STATUS_SUCCESS)
#define CUBLAS_STATUS_NOT_INITIALIZED	__CU(BLAS_STATUS_NOT_INITIALIZED)
#define CUBLAS_STATUS_ALLOC_FAILED	__CU(BLAS_STATUS_ALLOC_FAILED)
#define CUBLAS_STATUS_INVALID_VALUE	__CU(BLAS_STATUS_INVALID_VALUE)
#define CUBLAS_STATUS_ARCH_MISMATCH	__CU(BLAS_STATUS_ARCH_MISMATCH)
#define CUBLAS_STATUS_MAPPING_ERROR	__CU(BLAS_STATUS_MAPPING_ERROR)
#define CUBLAS_STATUS_EXECUTION_FAILED	__CU(BLAS_STATUS_EXECUTION_FAILED)
#define CUBLAS_STATUS_INTERNAL_ERROR	__CU(BLAS_STATUS_INTERNAL_ERROR)
#define CUBLAS_STATUS_NOT_SUPPORTED	__CU(BLAS_STATUS_NOT_SUPPORTED)

#define cublasHandle_t	__cu(blasHandle_t)
#define cublasCreate(handle)	__cu(blasCreate(handle))
#define cublasDestroy(handle)	__cu(blasDestroy(handle))

#define cublasGetVersion(handle, pversion)	__cu(blasGetVersion(handle, pversion))
#define cublasLtGetVersion()	__cu(blasLtGetVersion())
#define cublasGetProperty(type, pvalue)	__cu(blasGetProperty(type, pvalue))

/**
 * The cublasOperation_t type indicates which operation needs to be performed
 * with the dense matrix.
 */
#define cublasOperation_t	__cu(blasOperation_t)
/* The non-transpose operation is selected. */
#define CUBLAS_OP_N	__CU(BLAS_OP_N)
/* The transpose operation is selected. */
#define CUBLAS_OP_T	__CU(BLAS_OP_T)
/* The conjugate transpose operation is selected. */
#define CUBLAS_OP_C	__CU(BLAS_OP_C)
#define CUBLAS_OP_HERMITAN	__CU(BLAS_OP_HERMITAN)
#define CUBLAS_OP_CONJG	__CU(BLAS_OP_CONJG)

#define cublasFillMode_t	__cu(blasFillMode_t)
#define CUBLAS_FILL_MODE_LOWER	__CU(BLAS_FILL_MODE_LOWER)
#define CUBLAS_FILL_MODE_UPPER	__CU(BLAS_FILL_MODE_UPPER)
#define CUBLAS_FILL_MODE_FULL	__CU(BLAS_FILL_MODE_FULL)

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	__cu(blasSetMatrix(rows, cols, elemsize, A, ola, B, ldb))
/**
 * cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize,
 *                                const void *devicePtr, int ldDevice,
 *                                void *hostPtr, int ldHost);
 */
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	__cu(blasGetMatrix(rows, cols, elemsize, A, ola, B, ldb))

#define cublasSetVector(n, elemSize, x, incx, y, incy) \
	__cu(blasSetVector(n, elemSize, x, incx, y, incy))
#define cublasGetVector(n, elemSize, x, incx, y, incy) \
	__cu(blasGetVector(n, elemSize, x, incx, y, incy))

/**
 * The cublasPointerMode_t type indicates whether the scalar values are passed
 * by reference on the host or device.
 */
#define cublasPointerMode_t	__cu(blasPointerMode_t)
#define CUBLAS_POINTER_MODE_HOST	__CU(BLAS_POINTER_MODE_HOST)
#define CUBLAS_POINTER_MODE_DEVICE	__CU(BLAS_POINTER_MODE_DEVICE)

#define cublasGetPointerMode(handle, mode)	__cu(blasGetPointerMode(handle, mode))
#define cublasSetPointerMode(handle, mode)	__cu(blasSetPointerMode(handle, mode))

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx)	__cu(blasSscal(handle, n, alpha, x, incx))
#define cublasDscal(handle, n, alpha, x, incx)	__cu(blasDscal(handle, n, alpha, x, incx))
#define cublasCscal(handle, n, alpha, x, incx)	__cu(blasCscal(handle, n, alpha, x, incx))
#define cublasCsscal(handle, n, alpha, x, incx)	__cu(blasCsscal(handle, n, alpha, x, incx))
#define cublasZscal(handle, n, alpha, x, incx)	__cu(blasZscal(handle, n, alpha, x, incx))
#define cublasZdscal(handle, n, alpha, x, incx)	__cu(blasZdscal(handle, n, alpha, x, incx))

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult)	__cu(blasIsamax(handle, n, x, incx, presult))
#define cublasIdamax(handle, n, x, incx, presult)	__cu(blasIdamax(handle, n, x, incx, presult))
#define cublasIcamax(handle, n, x, incx, presult)	__cu(blasIcamax(handle, n, x, incx, presult))
#define cublasIzamax(handle, n, x, incx, presult)	__cu(blasIzamax(handle, n, x, incx, presult))

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult)	__cu(blasIsamin(handle, n, x, incx, presult))
#define cublasIdamin(handle, n, x, incx, presult)	__cu(blasIdamin(handle, n, x, incx, presult))
#define cublasIcamin(handle, n, x, incx, presult)	__cu(blasIcamin(handle, n, x, incx, presult))
#define cublasIzamin(handle, n, x, incx, presult)	__cu(blasIzamin(handle, n, x, incx, presult))

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult)	__cu(blasSasum(handle, n, x, incx, presult))
#define cublasDasum(handle, n, x, incx, presult)	__cu(blasDasum(handle, n, x, incx, presult))
#define cublasScasum(handle, n, x, incx, presult)	__cu(blasScasum(handle, n, x, incx, presult))
#define cublasDzasum(handle, n, x, incx, presult)	__cu(blasDzasum(handle, n, x, incx, presult))

/**
 * This function multiplies the vector x by the scalar alpha and adds it to
 * the vector y overwriting the latest vector with the result.
 *
 * y[j] = alpha x x[k] + y[j]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasSaxpy(handle, n, alpha, x, incx, y, incy)	__cu(blasSaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasDaxpy(handle, n, alpha, x, incx, y, incy)	__cu(blasDaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasCaxpy(handle, n, alpha, x, incx, y, incy)	__cu(blasCaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasZaxpy(handle, n, alpha, x, incx, y, incy)	__cu(blasZaxpy(handle, n, alpha, x, incx, y, incy))

/**
 * This function copies the vector x into the vector y.
 *
 * y[j] = x[k]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasScopy(handle, n, x, incx, y, incy)	__cu(blasScopy(handle, n, x, incx, y, incy))
#define cublasDcopy(handle, n, x, incx, y, incy)	__cu(blasDcopy(handle, n, x, incx, y, incy))
#define cublasCcopy(handle, n, x, incx, y, incy)	__cu(blasCcopy(handle, n, x, incx, y, incy))
#define cublasZcopy(handle, n, x, incx, y, incy)	__cu(blasZcopy(handle, n, x, incx, y, incy))

/**
 * This function computes the dot product of vectors x and y.
 */
#define cublasSdot(handle, n, x, incx, y, incy, presult)	__cu(blasSdot(handle, n, x, incx, y, incy, presult))
#define cublasDdot(handle, n, x, incx, y, incy, presult)	__cu(blasDdot(handle, n, x, incx, y, incy, presult))
#define cublasCdotu(handle, n, x, incx, y, incy, presult)	__cu(blasCdotu(handle, n, x, incx, y, incy, presult))
#define cublasCdotc(handle, n, x, incx, y, incy, presult)	__cu(blasCdotc(handle, n, x, incx, y, incy, presult))
#define cublasZdotu(handle, n, x, incx, y, incy, presult)	__cu(blasZdotu(handle, n, x, incx, y, incy, presult))
#define cublasZdotc(handle, n, x, incx, y, incy, presult)	__cu(blasZdotc(handle, n, x, incx, y, incy, presult))

/**
 * This function computes the Euclidean norm of the vector x.
 */
#define cublasSnrm2(handle, n, x, incx, presult)	__cu(blasSnrm2(handle, n, x, incx, presult))
#define cublasDnrm2(handle, n, x, incx, presult)	__cu(blasDnrm2(handle, n, x, incx, presult))
#define cublasScnrm2(handle, n, x, incx, presult)	__cu(blasScnrm2(handle, n, x, incx, presult))
#define cublasDznrm2(handle, n, x, incx, presult)	__cu(blasDznrm2(handle, n, x, incx, presult))

/**
 * This function applies Givens rotation matrix.
 */
#define cublasSrot(handle, n, x, incx, y, incy, c, s)	__cu(blasSrot(handle, n, x, incx, y, incy, c, s))
#define cublasDrot(handle, n, x, incx, y, incy, c, s)	__cu(blasDrot(handle, n, x, incx, y, incy, c, s))
#define cublasCrot(handle, n, x, incx, y, incy, c, s)	__cu(blasCrot(handle, n, x, incx, y, incy, c, s))
#define cublasCsrot(handle, n, x, incx, y, incy, c, s)	__cu(blasCsrot(handle, n, x, incx, y, incy, c, s))
#define cublasZrot(handle, n, x, incx, y, incy, c, s)	__cu(blasZrot(handle, n, x, incx, y, incy, c, s))
#define cublasZdrot(handle, n, x, incx, y, incy, c, s)	__cu(blasZdrot(handle, n, x, incx, y, incy, c, s))

/**
 * This function constructs the Givens rotation matrix.
 */
#define cublasSrotg(handle, a, b, c, s)	__cu(blasSrotg(handle, a, b, c, s))
#define cublasDrotg(handle, a, b, c, s)	__cu(blasDrotg(handle, a, b, c, s))
#define cublasCrotg(handle, a, b, c, s)	__cu(blasCrotg(handle, a, b, c, s))
#define cublasZrotg(handle, a, b, c, s)	__cu(blasZrotg(handle, a, b, c, s))

#define cublasSrotm(handle, n, x, incx, y, incy, param)	__cu(blasSrotm(handle, n, x, incx, y, incy, param))
#define cublasDrotm(handle, n, x, incx, y, incy, param)	__cu(blasDrotm(handle, n, x, incx, y, incy, param))

/**
 * This function performs the matrix-matrix multiplication.
 *
 * C = alpha op(A) op(B) + beta C
 */
/**
 * CUDA:
 * cublasStatus_t cublasSgemm(cublasHandle_t handle,
 *                          cublasOperation_t transa, cublasOperation_t transb,
 *                          int m, int n, int k,
 *                          const float           *alpha,
 *                          const float           *A, int lda,
 *                          const float           *B, int ldb,
 *                          const float           *beta,
 *                          float           *C, int ldc)
 * HIP:
 * hipblasStatus_t hipblasSgemm(hipblasHandle_t    handle,
 *                              hipblasOperation_t transA,
 *                              hipblasOperation_t transB,
 *                              int                m,
 *                              int                n,
 *                              int                k,
 *                              const float*       alpha,
 *                              const float*       AP,
 *                              int                lda,
 *                              const float*       BP,
 *                              int                ldb,
 *                              const float*       beta,
 *                              float*             CP,
 *                              int                ldc);
 */
#define cublasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
/**
 * CUDA:
 * cublasStatus_t cublasHgemm(cublasHandle_t handle,
 *                            cublasOperation_t transa,
 *                            cublasOperation_t transb,
 *                            int m,
 *                            int n,
 *                            int k,
 *                            const __half* alpha,
 *                            const __half* A,
 *                            int lda,
 *                            const __half* B,
 *                            int ldb,
 *                            const __half* beta,
 *                            __half* C,
 *                            int ldc);
 *
 * HIP:
 * hipblasStatus_t hipblasHgemm(hipblasHandle_t    handle,
 *                              hipblasOperation_t transA,
 *                              hipblasOperation_t transB,
 *                              int                m,
 *                              int                n,
 *                              int                k,
 *                              const hipblasHalf* alpha,
 *                              const hipblasHalf* AP,
 *                              int                lda,
 *                              const hipblasHalf* BP,
 *                              int                ldb,
 *                              const hipblasHalf* beta,
 *                              hipblasHalf*       CP,
 *                              int                ldc);
 */
#define cublasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))

#define cublasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy) \
	__cu(blasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy))

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
	__cu(blasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
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
	__cu(blasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
		      B, Btype, ldb, beta, C, Ctype, ldc))

#define cublasLtHandle_t	__cu(blasLtHandle_t)
#define cublasLtCreate(phandle)	__cu(blasLtCreate(phandle))
#define cublasLtDestroy(handle)	__cu(blasLtDestroy(handle))

#define cublasLtMatmulDesc_t	__cu(blasLtMatmulDesc_t)
/**
 * cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
 *                                         cublasComputeType_t computeType,
 *                                         cudaDataType_t scaleType);
 *
 * This function creates a matrix multiply descriptor by allocating the memory
 * needed to hold its opaque structure.
 */
#define cublasLtMatmulDescCreate(pdesc, computeType, scaleType) \
	__cu(blasLtMatmulDescCreate(pdesc, computeType, scaleType))
#define cublasLtMatmulDescDestroy(desc)	__cu(blasLtMatmulDescDestroy(desc))

#define cublasLtMatmulDescAttributes_t	__cu(blasLtMatmulDescAttributes_t)
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE	__CU(BLASLT_MATMUL_DESC_COMPUTE_TYPE)
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE		__CU(BLASLT_MATMUL_DESC_SCALE_TYPE)
#define CUBLASLT_MATMUL_DESC_POINTER_MODE	__CU(BLASLT_MATMUL_DESC_POINTER_MODE)
/* more ... */

#define cublasLtMatmulHeuristicResult_t	__cu(blasLtMatmulHeuristicResult_t)

#define cublasLtMatrixLayout_t	__cu(blasLtMatrixLayout_t)
#define cublasLtMatrixLayoutCreate(playout, type, rows, cols, ld) \
	__cu(blasLtMatrixLayoutCreate(playout, type, rows, cols, ld))
#define cublasLtMatrixLayoutDestroy(layout)	__cu(blasLtMatrixLayoutDestroy(layout))

#define cublasLtMatrixLayoutAttribute_t	__cu(blasLtMatrixLayoutAttribute_t)

/**
 * cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout,
 *                                                 cublasLtMatrixLayoutAttribute_t attr,
 *                                                 void* buf,
 *                                                 size_t sizeInBytes,
 *                                                 size_t* sizeWritten);
 */
#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
	__cu(blasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten))

#define CUBLASLT_MATRIX_LAYOUT_ROWS	__CU(BLASLT_MATRIX_LAYOUT_ROWS)
#define CUBLASLT_MATRIX_LAYOUT_COLS	__CU(BLASLT_MATRIX_LAYOUT_COLS)
#define CUBLASLT_MATRIX_LAYOUT_LD	__CU(BLASLT_MATRIX_LAYOUT_LD)
#define CUBLASLT_MATRIX_LAYOUT_TYPE	__CU(BLASLT_MATRIX_LAYOUT_TYPE)

#define cublasLtMatmulAlgo_t	__cu(blasLtMatmulAlgo_t)
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT	__CU(BLASLT_ALGO_CAP_SPLITK_SUPPORT)
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK	__CU(BLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK)
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT	__CU(BLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT)
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT	__CU(BLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT)
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT	__CU(BLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT)
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT	__CU(BLASLT_ALGO_CAP_UPLO_SUPPORT)
#define CUBLASLT_ALGO_CAP_TILE_IDS	__CU(BLASLT_ALGO_CAP_TILE_IDS)
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX	__CU(BLASLT_ALGO_CAP_CUSTOM_OPTION_MAX)
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER	__CU(BLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER)
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK	__CU(BLASLT_ALGO_CAP_POINTER_MODE_MASK)
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK	__CU(BLASLT_ALGO_CAP_EPILOGUE_MASK)
#define CUBLASLT_ALGO_CAP_STAGES_IDS	__CU(BLASLT_ALGO_CAP_STAGES_IDS)
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE	__CU(BLASLT_ALGO_CAP_LD_NEGATIVE)
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS	__CU(BLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES	__CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES	__CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES	__CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES	__CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES)
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC	__CU(BLASLT_ALGO_CAP_ATOMIC_SYNC)

#define cublasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt) \
	__cu(blasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt))
#define cublasLtMatmulPreferenceDestroy(pref)	__cu(blasLtMatmulPreferenceDestroy(pref))

#define cublasLtMatmulPreference_t	__cu(blasLtMatmulPreference_t)
#define cublasLtMatmulPreferenceCreate(preference)	__cu(blasLtMatmulPreferenceCreate(preference))

#define cublasLtMatmulPreferenceAttributes_t	__cu(blasLtMatmulPreferenceAttributes_t)
#define cublasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size) \
	__cu(blasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size))

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES	__CU(BLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES)

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream) \
	__cu(blasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream))

/**
 * cublasGemmAlgo_t type is an enumerant to specify the algorithm for
 * matrix-matrix multiplication.
 */
#define cublasGemmAlgo_t	__cu(blasGemmAlgo_t)
#define CUBLAS_GEMM_DEFAULT	__CU(BLAS_GEMM_DEFAULT)
#define CUBLAS_GEMM_ALGO0	__CU(BLAS_GEMM_ALGO0)
#define CUBLAS_GEMM_ALGO1	__CU(BLAS_GEMM_ALGO1)
#define CUBLAS_GEMM_ALGO2	__CU(BLAS_GEMM_ALGO2)
#define CUBLAS_GEMM_ALGO3	__CU(BLAS_GEMM_ALGO3)
#define CUBLAS_GEMM_ALGO4	__CU(BLAS_GEMM_ALGO4)
#define CUBLAS_GEMM_ALGO5	__CU(BLAS_GEMM_ALGO5)
#define CUBLAS_GEMM_ALGO6	__CU(BLAS_GEMM_ALGO6)
#define CUBLAS_GEMM_ALGO7	__CU(BLAS_GEMM_ALGO7)
#define CUBLAS_GEMM_ALGO8	__CU(BLAS_GEMM_ALGO8)
#define CUBLAS_GEMM_ALGO9	__CU(BLAS_GEMM_ALGO9)
#define CUBLAS_GEMM_ALGO10	__CU(BLAS_GEMM_ALGO10)
#define CUBLAS_GEMM_ALGO11	__CU(BLAS_GEMM_ALGO11)
#define CUBLAS_GEMM_ALGO12	__CU(BLAS_GEMM_ALGO12)
#define CUBLAS_GEMM_ALGO13	__CU(BLAS_GEMM_ALGO13)
#define CUBLAS_GEMM_ALGO14	__CU(BLAS_GEMM_ALGO14)
#define CUBLAS_GEMM_ALGO15	__CU(BLAS_GEMM_ALGO15)
#define CUBLAS_GEMM_ALGO16	__CU(BLAS_GEMM_ALGO16)
#define CUBLAS_GEMM_ALGO17	__CU(BLAS_GEMM_ALGO17)
#define CUBLAS_GEMM_ALGO18	__CU(BLAS_GEMM_ALGO18)
#define CUBLAS_GEMM_ALGO19	__CU(BLAS_GEMM_ALGO19)
#define CUBLAS_GEMM_ALGO20	__CU(BLAS_GEMM_ALGO20)
#define CUBLAS_GEMM_ALGO21	__CU(BLAS_GEMM_ALGO21)
#define CUBLAS_GEMM_ALGO22	__CU(BLAS_GEMM_ALGO22)
#define CUBLAS_GEMM_ALGO23	__CU(BLAS_GEMM_ALGO23)
#define CUBLAS_GEMM_DEFAULT_TENSOR_OP	__CU(BLAS_GEMM_DEFAULT_TENSOR_OP)
#define CUBLAS_GEMM_ALGO0_TENSOR_OP	__CU(BLAS_GEMM_ALGO0_TENSOR_OP)
#define CUBLAS_GEMM_ALGO1_TENSOR_OP	__CU(BLAS_GEMM_ALGO1_TENSOR_OP)
#define CUBLAS_GEMM_ALGO2_TENSOR_OP	__CU(BLAS_GEMM_ALGO2_TENSOR_OP)
#define CUBLAS_GEMM_ALGO3_TENSOR_OP	__CU(BLAS_GEMM_ALGO3_TENSOR_OP)
#define CUBLAS_GEMM_ALGO4_TENSOR_OP	__CU(BLAS_GEMM_ALGO4_TENSOR_OP)
#define CUBLAS_GEMM_ALGO5_TENSOR_OP	__CU(BLAS_GEMM_ALGO5_TENSOR_OP)
#define CUBLAS_GEMM_ALGO6_TENSOR_OP	__CU(BLAS_GEMM_ALGO6_TENSOR_OP)
#define CUBLAS_GEMM_ALGO7_TENSOR_OP	__CU(BLAS_GEMM_ALGO7_TENSOR_OP)
#define CUBLAS_GEMM_ALGO8_TENSOR_OP	__CU(BLAS_GEMM_ALGO8_TENSOR_OP)
#define CUBLAS_GEMM_ALGO9_TENSOR_OP	__CU(BLAS_GEMM_ALGO9_TENSOR_OP)
#define CUBLAS_GEMM_ALGO10_TENSOR_OP	__CU(BLAS_GEMM_ALGO10_TENSOR_OP)
#define CUBLAS_GEMM_ALGO11_TENSOR_OP	__CU(BLAS_GEMM_ALGO11_TENSOR_OP)
#define CUBLAS_GEMM_ALGO12_TENSOR_OP	__CU(BLAS_GEMM_ALGO12_TENSOR_OP)
#define CUBLAS_GEMM_ALGO13_TENSOR_OP	__CU(BLAS_GEMM_ALGO13_TENSOR_OP)
#define CUBLAS_GEMM_ALGO14_TENSOR_OP	__CU(BLAS_GEMM_ALGO14_TENSOR_OP)
#define CUBLAS_GEMM_ALGO15_TENSOR_OP	__CU(BLAS_GEMM_ALGO15_TENSOR_OP)
#define CUBLAS_GEMM_AUTOTUNE	__CU(BLAS_GEMM_AUTOTUNE)

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t	__cu(blasComputeType_t)
/**
 * This is the default and highest-performance mode for 16-bit half precision
 * floating point and all compute and intermediate storage precisions with at
 * least 16-bit half precision. Tensor Cores will be used whenever possible.
 */
#define CUBLAS_COMPUTE_16F	__CU(BLAS_COMPUTE_16F)
/**
 * This mode uses 16-bit half precision floating point standardized arithmetic
 * for all phases of calculations and is primarily intended for numerical
 * robustness studies, testing, and debugging. This mode might not be as
 * performant as the other modes since it disables use of tensor cores.
 */
#define CUBLAS_COMPUTE_16F_PEDANTIC	__CU(BLAS_COMPUTE_16F_PEDANTIC)
/**
 * This is the default 32-bit single precision floating point and uses compute
 * and intermediate storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32F	__CU(BLAS_COMPUTE_32F)
#define CUBLAS_COMPUTE_32F_PEDANTIC	__CU(BLAS_COMPUTE_32F_PEDANTIC)
/**
 * Allows the library to use Tensor Cores with automatic down-conversion and
 * 16-bit half-precision compute for 32-bit input and output matrices.
 */
#define CUBLAS_COMPUTE_32F_FAST_16F	__CU(BLAS_COMPUTE_32F_FAST_16F)
#define CUBLAS_COMPUTE_32F_FAST_16BF	__CU(BLAS_COMPUTE_32F_FAST_16BF)
#define CUBLAS_COMPUTE_32F_FAST_TF32	__CU(BLAS_COMPUTE_32F_FAST_TF32)
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9	__CU(BLAS_COMPUTE_32F_EMULATED_16BFX9)
/**
 * This is the default 64-bit double precision floating point and uses compute
 * and intermediate storage precisions of at least 64-bits.
 */
#define CUBLAS_COMPUTE_64F	__CU(BLAS_COMPUTE_64F)
#define CUBLAS_COMPUTE_64F_PEDANTIC	__CU(BLAS_COMPUTE_64F_PEDANTIC)
/**
 * This is the default 32-bit integer mode and uses compute and intermediate
 * storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32I	__CU(BLAS_COMPUTE_32I)
#define CUBLAS_COMPUTE_32I_PEDANTIC	__CU(BLAS_COMPUTE_32I_PEDANTIC)

#ifdef HAVE_HCCL
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
#define CUDA_R_6F_E3M2	HPCC_R_6F_E3M12
#define CUDA_R_4F_E2M1	HPCC_R_4F_E2M1
#elif defined(HAVE_HIP)
#define cudaDataType	__cuda(DataType)
#define CUDA_R_32F	HIP_R_32F
#define CUDA_R_64F	HIP_R_64F
#define CUDA_R_16F	HIP_R_16F
#define CUDA_R_8I	HIP_R_8I
#define CUDA_C_32F	HIP_C_32F
#define CUDA_C_64F	HIP_C_64F
#define CUDA_C_16F	HIP_C_16F
#define CUDA_C_8I	HIP_C_8I
#define CUDA_R_8U	HIP_R_8U
#define CUDA_C_8U	HIP_C_8U
#define CUDA_R_32I	HIP_R_32I
#define CUDA_C_32I	HIP_C_32I
#define CUDA_R_32U	HIP_R_32U
#define CUDA_C_32U	HIP_C_32U
#define CUDA_R_16BF	HIP_R_16BF
#define CUDA_C_16BF	HIP_C_16BF
#define CUDA_R_4I	HIP_R_4I
#define CUDA_C_4I	HIP_C_4I
#define CUDA_R_4U	HIP_R_4U
#define CUDA_C_4U	HIP_C_4U
#define CUDA_R_16I	HIP_R_16I
#define CUDA_C_16I	HIP_C_16I
#define CUDA_R_16U	HIP_R_16U
#define CUDA_C_16U	HIP_C_16U
#define CUDA_R_64I	HIP_R_64I
#define CUDA_C_64I	HIP_C_64I
#define CUDA_R_64U	HIP_R_64U
#define CUDA_C_64U	HIP_C_64U
#define CUDA_R_8F_E4M3	HIP_R_8F_E4M3
#define CUDA_R_8F_E5M2	HIP_R_8F_E5M2
#define CUDA_R_8F_E4M3_FNUZ	HIP_R_8F_E4M3_FNUZ
#define CUDA_R_8F_E5M2_FNUZ	HIP_R_8F_E5M2_FNUZ
#endif

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */
#define cuComplex	__cu(Complex)
#define cuDoubleComplex	__cu(DoubleComplex)

/**
 * refs
 * - https://docs.nvidia.com/cuda/curand/group__HOST.html
 */
#define curandStatus_t	__cu(randStatus_t)
#define CURAND_STATUS_SUCCESS	__CU(RAND_STATUS_SUCCESS)
#define CURAND_STATUS_SUCCESS	__CU(RAND_STATUS_SUCCESS)
#define CURAND_STATUS_VERSION_MISMATCH	__CU(RAND_STATUS_VERSION_MISMATCH)
#define CURAND_STATUS_NOT_INITIALIZED	__CU(RAND_STATUS_NOT_INITIALIZED)
#define CURAND_STATUS_ALLOCATION_FAILED	__CU(RAND_STATUS_ALLOCATION_FAILED)
#define CURAND_STATUS_TYPE_ERROR	__CU(RAND_STATUS_TYPE_ERROR)
#define CURAND_STATUS_OUT_OF_RANGE	__CU(RAND_STATUS_OUT_OF_RANGE)
#define CURAND_STATUS_LENGTH_NOT_MULTIPLE	__CU(RAND_STATUS_LENGTH_NOT_MULTIPLE)
#define CURAND_STATUS_DOUBLE_PRECISION_REQUIRED	__CU(RAND_STATUS_DOUBLE_PRECISION_REQUIRED)
#define CURAND_STATUS_LAUNCH_FAILURE	__CU(RAND_STATUS_LAUNCH_FAILURE)
#define CURAND_STATUS_PREEXISTING_FAILURE	__CU(RAND_STATUS_PREEXISTING_FAILURE)
#define CURAND_STATUS_INITIALIZATION_FAILED	__CU(RAND_STATUS_INITIALIZATION_FAILED)
#define CURAND_STATUS_ARCH_MISMATCH	__CU(RAND_STATUS_ARCH_MISMATCH)
#define CURAND_STATUS_INTERNAL_ERROR	__CU(RAND_STATUS_INTERNAL_ERROR)
#define CURAND_STATUS_NOT_IMPLEMENTED	__CU(RAND_STATUS_NOT_IMPLEMENTED)

#define curandGetVersion(version)	__cu(randGetVersion(version))

/**
 * FFT
 */
#define cufftResult	__cu(fftResult)
#define CUFFT_SUCCESS	__CU(FFT_SUCCESS)
#define CUFFT_INVALID_PLAN	__CU(FFT_INVALID_PLAN)
#define CUFFT_ALLOC_FAILED	__CU(FFT_ALLOC_FAILED)
#define CUFFT_INVALID_TYPE	__CU(FFT_INVALID_TYPE)
#define CUFFT_INVALID_VALUE	__CU(FFT_INVALID_VALUE)
#define CUFFT_INTERNAL_ERROR	__CU(FFT_INTERNAL_ERROR)
#define CUFFT_EXEC_FAILED	__CU(FFT_EXEC_FAILED)
#define CUFFT_SETUP_FAILED	__CU(FFT_SETUP_FAILED)
#define CUFFT_INVALID_SIZE	__CU(FFT_INVALID_SIZE)
#define CUFFT_UNALIGNED_DATA	__CU(FFT_UNALIGNED_DATA)
#define CUFFT_INCOMPLETE_PARAMETER_LIST	__CU(FFT_INCOMPLETE_PARAMETER_LIST)
#define CUFFT_INVALID_DEVICE	__CU(FFT_INVALID_DEVICE)
#define CUFFT_PARSE_ERROR	__CU(FFT_PARSE_ERROR)
#define CUFFT_NO_WORKSPACE	__CU(FFT_NO_WORKSPACE)
#define CUFFT_NOT_IMPLEMENTED	__CU(FFT_NOT_IMPLEMENTED)
#define CUFFT_LICENSE_ERROR	__CU(FFT_LICENSE_ERROR)
#define CUFFT_NOT_SUPPORTED	__CU(FFT_NOT_SUPPORTED)

/**
 * CUDA:
 * typedef enum libraryPropertyType_t {
 *     MAJOR_VERSION,
 *     MINOR_VERSION,
 *     PATCH_LEVEL
 * } libraryPropertyType;
 * hipfftResult hipfftGetProperty(hipfftLibraryPropertyType type, int* value);
 *
 * HIP:
 * typedef enum hipLibraryPropertyType {
 *     HIP_LIBRARY_MAJOR_VERSION,
 *     HIP_LIBRARY_MINOR_VERSION,
 *     HIP_LIBRARY_PATCH_LEVEL
 * } hipLibraryPropertyType;
 *
 * typedef enum hipfftLibraryPropertyType_t {
 *     HIPFFT_MAJOR_VERSION,
 *     HIPFFT_MINOR_VERSION,
 *     HIPFFT_PATCH_LEVEL
 * } hipfftLibraryPropertyType;
 *
 * cufftResult CUFFTAPI cufftGetProperty(libraryPropertyType type, int *value);
 */
#define cufftGetProperty(v, pval)	__cu(fftGetProperty(v, pval))


/**
 * SPARSE
 */
#define cusparseStatus_t	__cu(sparseStatus_t)
/**
 * HIP 5.7.1 has no hipsparseGetProperty()
 */
#define cusparseGetProperty(v, pval)	__cu(sparseGetProperty(v, pval))
#define CUSPARSE_STATUS_SUCCESS	__CU(SPARSE_STATUS_SUCCESS)
#define CUSPARSE_STATUS_NOT_INITIALIZED	__CU(SPARSE_STATUS_NOT_INITIALIZED)
#define CUSPARSE_STATUS_ALLOC_FAILED	__CU(SPARSE_STATUS_ALLOC_FAILED)
#define CUSPARSE_STATUS_INVALID_VALUE	__CU(SPARSE_STATUS_INVALID_VALUE)
#define CUSPARSE_STATUS_ARCH_MISMATCH	__CU(SPARSE_STATUS_ARCH_MISMATCH)
#define CUSPARSE_STATUS_MAPPING_ERROR	__CU(SPARSE_STATUS_MAPPING_ERROR)
#define CUSPARSE_STATUS_EXECUTION_FAILED	__CU(SPARSE_STATUS_EXECUTION_FAILED)
#define CUSPARSE_STATUS_INTERNAL_ERROR	__CU(SPARSE_STATUS_INTERNAL_ERROR)
#define CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED	__CU(SPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED)
#define CUSPARSE_STATUS_ZERO_PIVOT	__CU(SPARSE_STATUS_ZERO_PIVOT)
#define CUSPARSE_STATUS_NOT_SUPPORTED	__CU(SPARSE_STATUS_NOT_SUPPORTED)
#define CUSPARSE_STATUS_INSUFFICIENT_RESOURCES	__CU(SPARSE_STATUS_INSUFFICIENT_RESOURCES)

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
 * CUresult CUDAAPI cuModuleLoadData(CUmodule *module, const void *image);
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

/**
 * NV RTC
 */
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

#define nvrtcProgram	__nv(rtcProgram)

/**
 * CUDA 12:
 * nvrtcResult nvrtcDestroyProgram(nvrtcProgram *prog);
 *
 * HIP:
 * hiprtcResult hiprtcDestroyProgram(hiprtcProgram* prog);
 */
#define nvrtcDestroyProgram(prog)	__nv(rtcDestroyProgram(prog))

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
#define nvrtcCreateProgram	__nv(rtcCreateProgram)

/**
 * CUDA 13
 * nvrtcResult nvrtcGetProgramLogSize(nvrtcProgram prog, size_t *logSizeRet);
 *
 * HIP
 * hiprtcResult hiprtcGetProgramLogSize(hiprtcProgram prog, size_t* logSizeRet);
 */
#define nvrtcGetProgramLogSize	__nv(rtcGetProgramLogSize)

/**
 * HIP:
 *
 */

/**
 * There are store some special macros from here.
 */
#if defined(__USE_HPCC__)
# undef CUresult
# undef CUdevice
# undef CUmodule
# undef CUfunction
# undef CUjit_option
# undef CUDA_ERROR_INVALID_VALUE
# undef CUDA_SUCCESS

# define CUresult	hcError_t
# define CUdevice	hcDevice_t
# define CUmodule	hcModule_t
# define CUfunction	hcFunction_t
# define CUjit_option	hcJitOption
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
