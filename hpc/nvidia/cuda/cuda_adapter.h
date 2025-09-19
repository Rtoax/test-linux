// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#if defined(HAVE_HCCL)
/* Metax has CUDA-compatible APIs */
# define __cu(name)	hc##name
# define __CU(name)	HC##name
# define __CUDA(name)	HC_##name
# define __CUDA_ERROR(name)	HCC_STATUS_##name
#elif defined(HAVE_HIP)
# define __cu(name)	hip##name
# define __CU(name)	HIP##name
# define __CUDA(name)	HIP_##name
# define __CUDA_ERROR(name)	HIP_STATUS_##name
#elif !defined(__cu) || !defined(__CU) || !defined(__CUDA)
# error "Must define __cu(), __CU(), __CUDA(), __CUDA_ERROR() macros, or define HAVE_HCCL"
#endif

/* typedef hcError_t	cudaError_t; */
#define cudaError_t	__cu(Error_t)
#define cudaSuccess	__cu(Success)
#define cudaErrorInvalidValue	__cu(ErrorInvalidValue)
#define cudaErrorMemoryAllocation	__cu(ErrorMemoryAllocation)

#define cudaGetLastError()	__cu(GetLastError())
#define cudaGetErrorString(err)	__cu(GetErrorString(err))

#define cudaLimit	__cu(Limit_t)
#define cudaLimitStackSize	__cu(LimitStackSize)
#define cudaLimitPrintfFifoSize	__cu(LimitPrintfFifoSize)
#define cudaLimitMallocHeapSize	__cu(LimitMallocHeapSize)
#define cudaLimitDevRuntimeSyncDepth	__cu(LimitDevRuntimeSyncDepth)
#define cudaLimitDevRuntimePendingLaunchCount	__cu(LimitDevRuntimePendingLaunchCount)
#define cudaLimitMaxL2FetchGranularity	__cu(LimitMaxL2FetchGranularity)
#define cudaLimitPersistingL2CacheSize	__cu(LimitPersistingL2CacheSize)
#define cudaDeviceSetLimit(limit, value)	__cu(DeviceSetLimit(limit, value))
#define cudaDeviceGetLimit(limit, value)	__cu(DeviceGetLimit(limit, value))

/**
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html
 */
#define cudaMalloc(pp, sz)	__cu(Malloc(pp, sz))
#define cudaFree(ptr)	__cu(Free(ptr))
#define cudaMemset(ptr, v, size)	__cu(Memset(ptr, v, size))
#define cudaMemcpy(dev, host, size, flag)	__cu(Memcpy(dev, host, size, flag))
#define cudaMemcpyKind	__cu(MemcpyKind)
#define cudaMemcpyHostToDevice	__cu(MemcpyHostToDevice)
#define cudaMemcpyDeviceToHost	__cu(MemcpyDeviceToHost)
/**
 * cudaError_t cudaMallocManaged(void **devPtr, size_t size,
 *                               unsigned int flags = cudaMemAttachGlobal);
 * hcError_t hcMallocManaged(void **dev_ptr, size_t size,
 *                           unsigned int flags __dparm(hcMemAttachGlobal));
 */
/* flags */
#define cudaMemAttachGlobal	__cu(MemAttachGlobal)
#define cudaMemAttachHost	__cu(MemAttachHost)
#define cudaMemAttachSingle	__cu(MemAttachSingle)
#define cudaMallocManaged(pp, sz, flags)	__cu(MallocManaged(pp, sz, flags))
#define cudaMallocAsync(pp, sz, stream)	__cu(MallocAsync(pp, sz, stream))
#define cudaFreeAsync(ptr, stream)	__cu(FreeAsync(ptr, stream))

/**
 * CUDA V13.0.48
 * cudaError_t cudaMemAdvise(const void* devPtr, size_t count,
 *                           cudaMemoryAdvise advice,
 *                           cudaMemLocation location);
 * HPCC 2.33.1, 3.0.0
 * hcError_t hcMemAdvise(const void *dev_ptr, size_t count,
 *                       hcMemoryAdvise_t advice,
 *                       int device);
 */
#define cudaMemAdvise(ptr, count, advice, location_or_device)	__cu(MemAdvise(ptr, count, advice, location_or_device))
#define cudaMemoryAdvise	__cu(MemoryAdvise_t)	/* enum */
#define cudaMemAdviseSetReadMostly	__cu(MemAdviseSetReadMostly)
#define cudaMemAdviseUnsetReadMostly	__cu(MemAdviseUnsetReadMostly)
#define cudaMemAdviseSetPreferredLocation	__cu(MemAdviseSetPreferredLocation)
#define cudaMemAdviseUnsetPreferredLocation	__cu(MemAdviseUnsetPreferredLocation)
#define cudaMemAdviseSetAccessedBy	__cu(MemAdviseSetAccessedBy)
#define cudaMemAdviseUnsetAccessedBy	__cu(MemAdviseUnsetAccessedBy)
#define cudaMemLocation	__cu(MemLocation)	/* struct */
#define cudaMemLocationType	__cu(MemLocationType)	/* enum */
#define cudaMemLocationTypeInvalid	__cu(MemLocationTypeInvalid)
#define cudaMemLocationTypeNone	__cu(MemLocationTypeNone)
#define cudaMemLocationTypeDevice	__cu(MemLocationTypeDevice)
#define cudaMemLocationTypeHost	__cu(MemLocationTypeHost)
#define cudaMemLocationTypeHostNuma	__cu(MemLocationTypeHostNuma)
#define cudaMemLocationTypeHostNumaCurrent	__cu(MemLocationTypeHostNumaCurrent)

/**
 * CUDA: typedef __attribute__((device_builtin)) struct CUevent_st *cudaEvent_t;
 * HPCC: typedef struct HCevent_st *hcEvent_t;
 */
#define CUevent_st	__CU(event_st)
#define cudaEvent_t	__cu(Event_t)
#define cudaEventCreate(pe)	__cu(EventCreate(pe))
#define cudaEventDestroy(ev)	__cu(EventDestroy(ev))
/**
 * cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
 */
#define cudaEventRecord(ev, stream)	__cu(EventRecord(ev, stream))
#define cudaEventElapsedTime(pt, start, stop)	__cu(EventElapsedTime(pt, start, stop))
/**
 * cudaEventSynchronize() will block the CPU until the CPU waits for the GPU
 * calculation to complete the event 'ev'.
 */
#define cudaEventSynchronize(ev)	__cu(EventSynchronize(ev))

/**
 * cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim,
 *                              void **args, size_t sharedMem, cudaStream_t stream);
 * hcError_t hcLaunchKernel(const void *function_address, dim3 numBlocks, dim3 dimBlocks,
 *                          void **args, size_t sharedMemBytes), hcStream_t stream);
 */
#define cudaLaunchKernel(func, g, b, args, mem, stream) \
	__cu(LaunchKernel(func, g, b, args, mem, stream))

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
	__cu(LaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, stream))

/**
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
#define CUstream_st	__CU(stream_st)
#define cudaStream_t	__cu(Stream_t)
#define cudaStreamCreate(pstream)	__cu(StreamCreate(pstream))
#define cudaStreamSynchronize(stream)	__cu(StreamSynchronize(stream))
#define cudaStreamDestroy(stream)	__cu(StreamDestroy(stream))

/**
 * HPCC 3.0.0
 * hcError_t hcDeviceGet(hcDevice_t *device, int ordinal);
 *
 * CUDA V13.0.48
 * CUresult cuDeviceGet(CUdevice *device, int ordinal);
 */
#define CUdevice	__CU(device)
#define cuDeviceGet(pdevice, dev_id)	__cu(DeviceGet(pdevice, dev_id))
#define cuDeviceComputeCapability(pmajor, pminor, pdev) \
	__cu(DeviceComputeCapability(pmajor, pminor, pdev))

/* CUresult */
#define CUDA_SUCCESS	__CUDA_ERROR(SUCCESS);
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

#define cudaGetDeviceCount(pgpus)	__cu(GetDeviceCount(pgpus))
#define cudaGetDevice(p_id)	__cu(GetDevice(p_id))
#define cudaSetDevice(dev_id)	__cu(SetDevice(dev_id))

#define cudaDeviceProp	__cu(DeviceProp_t)
#define cudaGetDeviceProperties(prop, devid)	__cu(GetDeviceProperties(prop, devid))

#define cudaDeviceGetAttribute(pval, attr, dev_id)	__cu(DeviceGetAttribute(pval, attr, dev_id))
#if defined(HAVE_HCCL)
/* WARNING: different name */
#define cudaDeviceAttr	__cu(DeviceAttribute_t)
#define cudaDevAttrMaxThreadsPerBlock	__cu(DeviceAttributeMaxThreadsPerBlock)
#define cudaDevAttrMaxBlockDimX	__cu(DeviceAttributeMaxBlockDimX)
#define cudaDevAttrMaxBlockDimY	__cu(DeviceAttributeMaxBlockDimY)
#define cudaDevAttrMaxBlockDimZ	__cu(DeviceAttributeMaxBlockDimZ)
#define cudaDevAttrMaxGridDimX	__cu(DeviceAttributeMaxGridDimX)
#define cudaDevAttrMaxGridDimY	__cu(DeviceAttributeMaxGridDimY)
#define cudaDevAttrMaxGridDimZ	__cu(DeviceAttributeMaxGridDimZ)
#define cudaDevAttrMaxSharedMemoryPerBlock	__cu(DeviceAttributeMaxSharedMemoryPerBlock)
#define cudaDevAttrTotalConstantMemory	__cu(DeviceAttributeTotalConstantMemory)
#define cudaDevAttrWarpSize	__cu(DeviceAttributeWarpSize)
#define cudaDevAttrMaxPitch	__cu(DeviceAttributeMaxPitch)
#define cudaDevAttrMaxRegistersPerBlock	__cu(DeviceAttributeMaxRegistersPerBlock)
#define cudaDevAttrClockRate	__cu(DeviceAttributeClockRate)
#define cudaDevAttrTextureAlignment	__cu(DeviceAttributeTextureAlignment)
#define cudaDevAttrGpuOverlap	__cu(DeviceAttributeGpuOverlap)
#define cudaDevAttrMultiProcessorCount	__cu(DeviceAttributeMultiProcessorCount)
#define cudaDevAttrKernelExecTimeout	__cu(DeviceAttributeKernelExecTimeout)
#define cudaDevAttrIntegrated	__cu(DeviceAttributeIntegrated)
#define cudaDevAttrCanMapHostMemory	__cu(DeviceAttributeCanMapHostMemory)
#define cudaDevAttrComputeMode	__cu(DeviceAttributeComputeMode)
#define cudaDevAttrMaxTexture1DWidth	__cu(DeviceAttributeMaxTexture1DWidth)
#define cudaDevAttrMaxTexture2DWidth	__cu(DeviceAttributeMaxTexture2DWidth)
#define cudaDevAttrMaxTexture2DHeight	__cu(DeviceAttributeMaxTexture2DHeight)
#define cudaDevAttrMaxTexture3DWidth	__cu(DeviceAttributeMaxTexture3DWidth)
#define cudaDevAttrMaxTexture3DHeight	__cu(DeviceAttributeMaxTexture3DHeight)
#define cudaDevAttrMaxTexture3DDepth	__cu(DeviceAttributeMaxTexture3DDepth)
#define cudaDevAttrMaxTexture2DLayeredWidth	__cu(DeviceAttributeMaxTexture2DLayeredWidth)
#define cudaDevAttrMaxTexture2DLayeredHeight	__cu(DeviceAttributeMaxTexture2DLayeredHeight)
#define cudaDevAttrMaxTexture2DLayeredLayers	__cu(DeviceAttributeMaxTexture2DLayeredLayers)
#define cudaDevAttrSurfaceAligement	__cu(DeviceAttributeSurfaceAligement)
#define cudaDevAttrConcurrentKernels	__cu(DeviceAttributeConcurrentKernels)
#define cudaDevAttrEccEnabled	__cu(DeviceAttributeEccEnabled)
#define cudaDevAttrPciBusId	__cu(DeviceAttributePciBusId)
#define cudaDevAttrPciDeviceId	__cu(DeviceAttributePciDeviceId)
#define cudaDevAttrTccDriver	__cu(DeviceAttributeTccDriver)
#define cudaDevAttrMemoryClockRate	__cu(DeviceAttributeMemoryClockRate)
#define cudaDevAttrMemoryBusWidth	__cu(DeviceAttributeMemoryBusWidth)
#define cudaDevAttrL2CacheSize	__cu(DeviceAttributeL2CacheSize)
#define cudaDevAttrMaxThreadsPerMultiProcessor	__cu(DeviceAttributeMaxThreadsPerMultiProcessor)
#define cudaDevAttrAsyncEngineCount	__cu(DeviceAttributeAsyncEngineCount)
#define cudaDevAttrUnifiedAddressing	__cu(DeviceAttributeUnifiedAddressing)
#define cudaDevAttrMaxTexture1DLayeredWidth	__cu(DeviceAttributeMaxTexture1DLayeredWidth)
#define cudaDevAttrMaxTexture1DLayeredLayers	__cu(DeviceAttributeMaxTexture1DLayeredLayers)
#define cudaDevAttrResvered44	__cu(DeviceAttributeResvered44)
#define cudaDevAttrMaxTexture2DGatherWidth	__cu(DeviceAttributeMaxTexture2DGatherWidth)
#define cudaDevAttrMaxTexture2DGatherHeight	__cu(DeviceAttributeMaxTexture2DGatherHeight)
#define cudaDevAttrMaxTexture3DWidthAlt	__cu(DeviceAttributeMaxTexture3DWidthAlt)
#define cudaDevAttrMaxTexture3DHeightAlt	__cu(DeviceAttributeMaxTexture3DHeightAlt)
#define cudaDevAttrMaxTexture3DDepthAlt	__cu(DeviceAttributeMaxTexture3DDepthAlt)
#define cudaDevAttrPciDomainId	__cu(DeviceAttributePciDomainId)
#define cudaDevAttrTexturePitchAlignment	__cu(DeviceAttributeTexturePitchAlignment)
#define cudaDevAttrMaxTextureCubemapWidth	__cu(DeviceAttributeMaxTextureCubemapWidth)
#define cudaDevAttrMaxTextureCubemapLayeredWidth	__cu(DeviceAttributeMaxTextureCubemapLayeredWidth)
#define cudaDevAttrMaxTextureCubemapLayeredLayers	__cu(DeviceAttributeMaxTextureCubemapLayeredLayers)
#define cudaDevAttrMaxSurface1DWidth	__cu(DeviceAttributeMaxSurface1DWidth)
#define cudaDevAttrMaxSurface2DWidth	__cu(DeviceAttributeMaxSurface2DWidth)
#define cudaDevAttrMaxSurface2DHeight	__cu(DeviceAttributeMaxSurface2DHeight)
#define cudaDevAttrMaxSurface3DWidth	__cu(DeviceAttributeMaxSurface3DWidth)
#define cudaDevAttrMaxSurface3DHeight	__cu(DeviceAttributeMaxSurface3DHeight)
#define cudaDevAttrMaxSurface3DDepth	__cu(DeviceAttributeMaxSurface3DDepth)
#define cudaDevAttrMaxSurface1DLayeredWidth	__cu(DeviceAttributeMaxSurface1DLayeredWidth)
#define cudaDevAttrMaxSurface1DLayeredLayers	__cu(DeviceAttributeMaxSurface1DLayeredLayers)
#define cudaDevAttrMaxSurface2DLayeredWidth	__cu(DeviceAttributeMaxSurface2DLayeredWidth)
#define cudaDevAttrMaxSurface2DLayeredHeight	__cu(DeviceAttributeMaxSurface2DLayeredHeight)
#define cudaDevAttrMaxSurface2DLayeredLayers	__cu(DeviceAttributeMaxSurface2DLayeredLayers)
#define cudaDevAttrMaxSurfaceCubemapWidth	__cu(DeviceAttributeMaxSurfaceCubemapWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredWidth	__cu(DeviceAttributeMaxSurfaceCubemapLayeredWidth)
#define cudaDevAttrMaxSurfaceCubemapLayeredLayers	__cu(DeviceAttributeMaxSurfaceCubemapLayeredLayers)
#define cudaDevAttrTexture1DLinearWidth	__cu(DeviceAttributeTexture1DLinearWidth)
#define cudaDevAttrTexture2DLinearWidth	__cu(DeviceAttributeTexture2DLinearWidth)
#define cudaDevAttrTexture2DLinearHeight	__cu(DeviceAttributeTexture2DLinearHeight)
#define cudaDevAttrTexture2DLinearPitch	__cu(DeviceAttributeTexture2DLinearPitch)
#define cudaDevAttrMaxTexture2DMipmappedWidth	__cu(DeviceAttributeMaxTexture2DMipmappedWidth)
#define cudaDevAttrMaxTexture2DMipmappedHeight	__cu(DeviceAttributeMaxTexture2DMipmappedHeight)
#define cudaDevAttrComputeCapabilityMajor	__cu(DeviceAttributeComputeCapabilityMajor)
#define cudaDevAttrComputeCapabilityMinor	__cu(DeviceAttributeComputeCapabilityMinor)
#define cudaDevAttrStreamPrioritiesSupported	__cu(DeviceAttributeStreamPrioritiesSupported)
#define cudaDevAttrGlobalL1CacheSupported	__cu(DeviceAttributeGlobalL1CacheSupported)
#define cudaDevAttrLocalL1CacheSupported	__cu(DeviceAttributeLocalL1CacheSupported)
#define cudaDevAttrMaxSharedMemoryPerMultiprocessor	__cu(DeviceAttributeMaxSharedMemoryPerMultiprocessor)
#define cudaDevAttrMaxRegistersPerMultiprocessor	__cu(DeviceAttributeMaxRegistersPerMultiprocessor)
#define cudaDevAttrManagedMemory	__cu(DeviceAttributeManagedMemory)
#define cudaDevAttrIsMultiGpuBoard	__cu(DeviceAttributeIsMultiGpuBoard)
#define cudaDevAttrMultiGpuBoardGroupID	__cu(DeviceAttributeMultiGpuBoardGroupID)
#define cudaDevAttrHostNativeAtomicSupported	__cu(DeviceAttributeHostNativeAtomicSupported)
#define cudaDevAttrSingleToDoublePrecisionPerfRatio	__cu(DeviceAttributeSingleToDoublePrecisionPerfRatio)
#define cudaDevAttrPageableMemoryAccess	__cu(DeviceAttributePageableMemoryAccess)
#define cudaDevAttrConcurrentManagedAccess	__cu(DeviceAttributeConcurrentManagedAccess)
#define cudaDevAttrComputePreemptionSupported	__cu(DeviceAttributeComputePreemptionSupported)
#define cudaDevAttrCanUseHostPointerForRegisteredMem	__cu(DeviceAttributeCanUseHostPointerForRegisteredMem)
#define cudaDevAttrReserved92	__cu(DeviceAttributeReserved92)
#define cudaDevAttrReserved93	__cu(DeviceAttributeReserved93)
#define cudaDevAttrReserved94	__cu(DeviceAttributeReserved94)
#define cudaDevAttrCooperativeLaunch	__cu(DeviceAttributeCooperativeLaunch)
#define cudaDevAttrCooperativeMultiDeviceLaunch	__cu(DeviceAttributeCooperativeMultiDeviceLaunch)
#define cudaDevAttrMaxSharedMemoryPerBlockOptin	__cu(DeviceAttributeMaxSharedMemoryPerBlockOptin)
#define cudaDevAttrCanFlushRemoteWrites	__cu(DeviceAttributeCanFlushRemoteWrites)
#define cudaDevAttrHostRegisterSupported	__cu(DeviceAttributeHostRegisterSupported)
#define cudaDevAttrPageableMemoryAccessUsesHostPageTables	__cu(DeviceAttributePageableMemoryAccessUsesHostPageTables)
#define cudaDevAttrDirectManagedMemAccessFromHost	__cu(DeviceAttributeDirectManagedMemAccessFromHost)
#define cudaDevAttrReserved102	__cu(DeviceAttributeReserved102)
#define cudaDevAttrReserved103	__cu(DeviceAttributeReserved103)
#define cudaDevAttrReserved104	__cu(DeviceAttributeReserved104)
#define cudaDevAttrReserved105	__cu(DeviceAttributeReserved105)
#define cudaDevAttrReserved107	__cu(DeviceAttributeReserved107)
#define cudaDevAttrMaxPersistingL2CacheSize	__cu(DeviceAttributeMaxPersistingL2CacheSize)
#define cudaDevAttrMaxAccessPolicyWindowSize	__cu(DeviceAttributeMaxAccessPolicyWindowSize)
#define cudaDevAttrReserved110	__cu(DeviceAttributeReserved110)
#define cudaDevAttrReservedSharedMemoryPerBlock	__cu(DeviceAttributeReservedSharedMemoryPerBlock)
#define cudaDevAttrSparseHpccArraySupported	__cu(DeviceAttributeSparseHpccArraySupported)
#define cudaDevAttrHostRegisterReadOnlySupported	__cu(DeviceAttributeHostRegisterReadOnlySupported)
#define cudaDevAttrTimelineSemaphoreInteropSupported	__cu(DeviceAttributeTimelineSemaphoreInteropSupported)
#define cudaDevAttrMemoryPoolsSupported	__cu(DeviceAttributeMemoryPoolsSupported)
#define cudaDevAttrGPUDirectRDMASupported	__cu(DeviceAttributeGPUDirectRDMASupported)
#define cudaDevAttrGPUDirectRDMAFlushWritesOptions	__cu(DeviceAttributeGPUDirectRDMAFlushWritesOptions)
#define cudaDevAttrGPUDirectRDMAWritesOrdering	__cu(DeviceAttributeGPUDirectRDMAWritesOrdering)
#define cudaDevAttrMemoryPoolSupportedHandleTypes	__cu(DeviceAttributeMemoryPoolSupportedHandleTypes)
#define cudaDevAttrClusterLaunch	__cu(DeviceAttributeClusterLaunch)
#define cudaDevAttrDeferredMappingHpccArraySupported	__cu(DeviceAttributeDeferredMappingHpccArraySupported)
#define cudaDevAttrReserved122	__cu(DeviceAttributeReserved122)
#define cudaDevAttrReserved123	__cu(DeviceAttributeReserved123)
#define cudaDevAttrReserved124	__cu(DeviceAttributeReserved124)
#define cudaDevAttrIpcEventSupport	__cu(DeviceAttributeIpcEventSupport)
#define cudaDevAttrMemSyncDomainCount	__cu(DeviceAttributeMemSyncDomainCount)
#define cudaDevAttrReserved127	__cu(DeviceAttributeReserved127)
#define cudaDevAttrReserved128	__cu(DeviceAttributeReserved128)
#define cudaDevAttrReserved129	__cu(DeviceAttributeReserved129)
#define cudaDevAttrNumaConfig	__cu(DeviceAttributeNumaConfig)
#define cudaDevAttrNumaId	__cu(DeviceAttributeNumaId)
#define cudaDevAttrReserved132	__cu(DeviceAttributeReserved132)
#define cudaDevAttrMpsEnabled	__cu(DeviceAttributeMpsEnabled)
#define cudaDevAttrHostNumaId	__cu(DeviceAttributeHostNumaId)
#define cudaDevAttrWaveSize	__cu(DeviceAttributeWaveSize)
#define cudaDevAttrHdpMemFlushCntl	__cu(DeviceAttributeHdpMemFlushCntl)
#define cudaDevAttrHdpRegFlushCntl	__cu(DeviceAttributeHdpRegFlushCntl)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedFunc	__cu(DeviceAttributeCooperativeMultiDeviceUnmatchedFunc)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedGridDim	__cu(DeviceAttributeCooperativeMultiDeviceUnmatchedGridDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedBlockDim	__cu(DeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim)
#define cudaDevAttrCooperativeMultiDeviceUnmatchedSharedMem	__cu(DeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem)
#define cudaDevAttrAsicRevision	__cu(DeviceAttributeAsicRevision)
#define cudaDevAttrVirtualMemoryManagementSupported	__cu(DeviceAttributeVirtualMemoryManagementSupported)
#define cudaDevAttrHandleTypePosixFileDescriptorSupported	__cu(DeviceAttributeHandleTypePosixFileDescriptorSupported)
#define cudaDevAttrHandleTypeWin32HandleSupported	__cu(DeviceAttributeHandleTypeWin32HandleSupported)
#define cudaDevAttrGenericCompressionSupported	__cu(DeviceAttributeGenericCompressionSupported)
#define cudaDevAttrCanUseStreamWaitValue	__cu(DeviceAttributeCanUseStreamWaitValue)
#define cudaDevAttrCanUseStreamMemOps	__cu(DeviceAttributeCanUseStreamMemOps)
#define cudaDevAttrCanUseStreamWaitWaitValueNor	__cu(DeviceAttributeCanUseStreamWaitWaitValueNor)
#define cudaDevAttrLocalSocketId	__cu(DeviceAttributeLocalSocketId)
#define cudaDevAttrSocketId	__cu(DeviceAttributeSocketId)
#define cudaDevAttrPeerSocketId	__cu(DeviceAttributePeerSocketId)
#define cudaDevAttrMulticastSupported	__cu(DeviceAttributeMulticastSupported)
#endif	/* HAVE_HCCL */

#define cudaDeviceP2PAttr	__cu(DeviceP2PAttr)
/**
 * cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr,
 *                                       int srcDevice, int dstDevice);
 */
#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	__cu(DeviceGetP2PAttribute(v, attr, src, dst))
#define cudaDevP2PAttrPerformanceRank	__cu(DevP2PAttrPerformanceRank)
#define cudaDevP2PAttrAccessSupported	__cu(DevP2PAttrAccessSupported)
#define cudaDevP2PAttrNativeAtomicSupported	__cu(DevP2PAttrNativeAtomicSupported)

/**
 * cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice);
 */
#define cudaDeviceCanAccessPeer(can, devfrom, devto) __cu(DeviceCanAccessPeer(can, devfrom, devto))
#define cudaDeviceEnablePeerAccess(peerdev, flag)	__cu(DeviceEnablePeerAccess(peerdev, flag))
/**
 * cudaError_t cudaDeviceDisablePeerAccess(int peerDevice);
 */
#define cudaDeviceDisablePeerAccess(dev)	__cu(DeviceDisablePeerAccess(dev))

#define cudaDeviceSynchronize()	__cu(DeviceSynchronize())

/**
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 */
#define cublasGetStatusString(status)	__cu(blasGetStatusString(status))
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
	__cu(blasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	__cu(blasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
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
#define cufftGetProperty(v, pval)	__cu(fftGetProperty(v, pval))

/**
 * SPARSE
 */
#define cusparseStatus_t	__cu(sparseStatus_t)
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
#define CUmodule	__CU(module)
#define cuModuleLoad(pmodule, name)	__cu(ModuleLoad(pmodule, name))
#define CUfunction	__CU(function)
#define cuModuleGetFunction(pfunc, mod, name)	__cu(ModuleGetFunction(pfunc, mod, name))
