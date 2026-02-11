// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_RUNTIME_API_H
#define __CUDA_ADAPTER_CUDA_RUNTIME_API_H 1

#define cudaGetDeviceCount(pgpus) __cuda(GetDeviceCount(pgpus))
#define cudaGetDevice(p_id) __cuda(GetDevice(p_id))
#define cudaSetDevice(dev_id) __cuda(SetDevice(dev_id))

/**
 * CUDA 13
 * cudaError_t cudaPeekAtLastError(void);
 *
 * HIP 6.3.42133-0
 * hipError_t hipPeekAtLastError(void);
 */
#define cudaPeekAtLastError() __cuda(PeekAtLastError())

#define cudaGetLastError() __cuda(GetLastError())
#define cudaGetErrorString(err) __cuda(GetErrorString(err))

/**
 * CUDA 13:
 * const char* cudaGetErrorName(cudaError_t error);
 *
 * HIP 6.3.42133-0
 * const char* hipGetErrorName(hipError_t hip_error);
 */
#define cudaGetErrorName(error) __cuda(GetErrorName(error))

#define cudaDeviceSetLimit(limit, value) __cuda(DeviceSetLimit(limit, value))
#define cudaDeviceGetLimit(limit, value) __cuda(DeviceGetLimit(limit, value))

/**
 * CUDA
 * cudaError_t cudaDriverGetVersion(int *driverVersion);
 */
#define cudaDriverGetVersion __cuda(DriverGetVersion)

/**
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html
 */
#define cudaMalloc(pp, sz) __cuda(Malloc(pp, sz))
#define cudaFree(ptr) __cuda(Free(ptr))

/**
 * Pinned memory, on CPU memory, GPU accessable, DMA copy
 *
 * HIPCC 6.4
 * hipError_t hipMallocHost(void** ptr, size_t size);
 * hipError_t hipHostMalloc(void** ptr, size_t size, unsigned int flags);
 */
#define cudaMallocHost(ptr, sz, flags) __cuda(MallocHost(ptr, sz, flags))
#define cudaFreeHost(ptr) __cuda(FreeHost(ptr))

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
#define cudaMallocAsync(pp, sz, stream) __cuda(MallocAsync(pp, sz, stream))

/**
 * CUDA 12:
 * cudaError_t cudaFreeAsync(void *devPtr, cudaStream_t hStream);
 *
 * HIP:
 * hipError_t hipFreeAsync(void* dev_ptr, hipStream_t stream);
 */
#define cudaFreeAsync(ptr, stream) __cuda(FreeAsync(ptr, stream))

/**
 * cudaError_t cudaMallocManaged(void **devPtr, size_t size,
 *                               unsigned int flags = cudaMemAttachGlobal);
 * hcError_t hcMallocManaged(void **dev_ptr, size_t size,
 *                           unsigned int flags __dparm(hcMemAttachGlobal));
 */
#define cudaMallocManaged(pp, sz, flags) __cuda(MallocManaged(pp, sz, flags))

#define cudaMemset(ptr, v, size) __cuda(Memset(ptr, v, size))

/**
 * CUDA 12
 * cudaError_t cudaMemsetAsync(void *devPtr, int value, size_t count,
 *                             cudaStream_t stream);
 *
 * HIP
 * hipError_t hipMemsetAsync(void* dst, int value, size_t sizeBytes,
 *                           hipStream_t stream);
 */
#define cudaMemsetAsync(ptr, v, size, stream) \
	__cuda(MemsetAsync(ptr, v, size, stream))

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
#define cudaMemset2DAsync(dst, pitch, value, width, height, stream) \
	__cuda(Memset2DAsync(dst, pitch, value, width, height, stream))

#define cudaMemcpy(dst, src, size, flag) __cuda(Memcpy(dst, src, size, flag))

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
#define cudaMemcpyAsync __cuda(MemcpyAsync)

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
#define cudaMemcpy2D __cuda(Memcpy2D)

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
#define cudaMemcpy2DAsync __cuda(Memcpy2DAsync)

/**
 * CUDA 12 don't have cudaMemcpyWithStream()
 *
 * HIP
 * hipError_t hipMemcpyWithStream(void* dst, const void* src, size_t sizeBytes,
 *                                hipMemcpyKind kind, hipStream_t stream);
 */
// TODO

/**
 * CUDA 13:
 * cudaError_t cudaGetSymbolAddress(void **devPtr, const void *symbol);
 *
 * HPCC:
 * hcError_t hcGetSymbolAddress(void **devPtr, const void *symbol);
 */
#define cudaGetSymbolAddress __cuda(GetSymbolAddress)

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
#define cudaMemcpyFromSymbol __cuda(MemcpyFromSymbol)
#define cudaMemcpyToSymbol __cuda(MemcpyToSymbol)

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
#define cudaMemcpyPeer __cuda(MemcpyPeer)

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
#define cudaMemcpyPeerAsync __cuda(MemcpyPeerAsync)

/**
 * CUDA 13.0
 * cudaError_t cudaHostRegister(void *ptr, size_t size, unsigned int flags);
 * cudaError_t cudaHostUnregister(void *ptr);
 *
 * HIP 6.4
 * hipError_t hipHostRegister(void* hostPtr, size_t sizeBytes, unsigned int flags);
 */
#define cudaHostRegister __cuda(HostRegister)
#define cudaHostUnregister __cuda(HostUnregister)

/**
 * CUDA 13.0
 * cudaError_t cudaHostGetDevicePointer(T **pDevice, void *pHost, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipHostGetDevicePointer(void** devPtr, void* hstPtr, unsigned int flags);
 */
#define cudaHostGetDevicePointer __cuda(HostGetDevicePointer)

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
#define cudaMemAdvise(ptr, count, advice, location_or_device) \
	__cuda(MemAdvise(ptr, count, advice, location_or_device))
#define cudaMemAdvise_v2(ptr, count, advice, location_or_device) \
	__cuda(MemAdvise_v2(ptr, count, advice, location_or_device))

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
#define cudaDeviceGetDefaultMemPool(pool, dev) \
	__cuda(DeviceGetDefaultMemPool(pool, dev))

/**
 * CUDA
 * cudaError_t cudaMemPoolTrimTo(cudaMemPool_t memPool, size_t minBytesToKeep);
 *
 * HIP
 * hipError_t hipMemPoolTrimTo(hipMemPool_t mem_pool, size_t min_bytes_to_hold);
 */
#define cudaMemPoolTrimTo(p, b) __cuda(MemPoolTrimTo(p, b))

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
#define cudaPointerGetAttributes(a, p) __cuda(PointerGetAttributes(a, p))

#define cudaEventCreate(pe) __cuda(EventCreate(pe))
#define cudaEventCreateWithFlags(pe, f) __cuda(EventCreateWithFlags(pe, f))
#define cudaEventDestroy(ev) __cuda(EventDestroy(ev))

/**
 * cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
 */
#define cudaEventRecord(ev, stream) __cuda(EventRecord(ev, stream))
#define cudaEventElapsedTime(pt, start, stop) \
	__cuda(EventElapsedTime(pt, start, stop))

/**
 * cudaEventSynchronize() will block the CPU until the CPU waits for the GPU
 * calculation to complete the event 'ev'.
 */
#define cudaEventSynchronize(ev) __cuda(EventSynchronize(ev))

/**
 * CUDA 13.0
 * cudaError_t cudaEventQuery(cudaEvent_t event);
 *
 * HIP 6.4
 * hipError_t hipEventQuery(hipEvent_t event);
 */
#define cudaEventQuery __cuda(EventQuery)

/**
 * CUDA 13
 * cudaError_t cudaGraphCreate(cudaGraph_t *pGraph, unsigned int flags);
 *
 * LUCA
 * lcError_t lcGraphCreate(lcGraph_t *pGraph, unsigned int flags);
 * lcError_t lcGraphDestroy(lcGraph_t graph);
 */
#define cudaGraphCreate __cuda(GraphCreate)
#define cudaGraphDestroy __cuda(GraphDestroy)

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
#define cudaGraphAddMemcpyNode1D __cuda(GraphAddMemcpyNode1D)

#define cudaGraphAddMemAllocNode __cuda(GraphAddMemAllocNode)
#define cudaGraphAddMemFreeNode __cuda(GraphAddMemFreeNode)

#define cudaGraphInstantiate __cuda(GraphInstantiate)
#define cudaGraphExecDestroy __cuda(GraphExecDestroy)
#define cudaGraphLaunch __cuda(GraphLaunch)

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
#define cudaGraphRetainUserObject __cuda(GraphRetainUserObject)

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
#define cudaGraphAddEventWaitNode __cuda(GraphAddEventWaitNode)

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
#define cudaGraphAddEventRecordNode __cuda(GraphAddEventRecordNode)

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
#define cudaGraphAddHostNode __cuda(GraphAddHostNode)

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
#define cudaGraphAddKernelNode __cuda(GraphAddKernelNode)

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
 * CUDA V13.0.48:
 * cudaError_t cudaLaunchCooperativeKernel(const void *func, dim3 gridDim, dim3 blockDim,
 *                                         void **args, size_t sharedMem,
 *                                         cudaStream_t stream);
 *
 * HPCC 3.0.0:
 * hcError_t hcLaunchCooperativeKernel(const void *f, dim3 gridDim, dim3 blockDim,
 *                                     void **kernelParams, unsigned int sharedMemBytes,
 *                                     hcStream_t stream);
 */
#define cudaLaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes,    \
				    stream)                                 \
	__cuda(LaunchCooperativeKernel(kernel, blocks, blksz, kargs, bytes, \
				       stream))

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
 * CUDA 13.0
 * cudaError_t cudaLaunchHostFunc(cudaStream_t stream, cudaHostFn_t fn, void *userData);
 *
 * HIP 6.4
 * hipError_t hipLaunchHostFunc(hipStream_t stream, hipHostFn_t fn, void* userData);
 */
#define cudaLaunchHostFunc __cuda(LaunchHostFunc)

/**
 * cudaError_t cudaGetFuncBySymbol(cudaFunction_t* functionPtr, const void* symbolPtr);
 */
#define cudaGetFuncBySymbol __cuda(GetFuncBySymbol)

/**
 * CUDA V13.0
 * cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const void *func);
 *
 * HIP 6.4
 * hipError_t hipFuncGetAttributes(struct hipFuncAttributes* attr, const void* func);
 */
#define cudaFuncGetAttributes(a, f) __cuda(FuncGetAttributes(a, f))

/**
 * CUDA V13.0
 * cudaError_t cudaFuncSetAttribute(T *func, enum cudaFuncAttribute a, int value);
 *
 * HIP 6.4
 * hipError_t hipFuncSetAttribute(const void* func, hipFuncAttribute attr, int value);
 */
#define cudaFuncSetAttribute(f, a, v) __cuda(FuncSetAttribute(f, a, v))

/**
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
#define cudaStreamCreate(pstream) __cuda(StreamCreate(pstream))
#define cudaStreamCreateWithFlags(s, f) __cuda(StreamCreateWithFlags(s, f))
#define cudaStreamDestroy(stream) __cuda(StreamDestroy(stream))

#define cudaStreamSynchronize(stream) __cuda(StreamSynchronize(stream))

/**
 * CUDA V13.0:
 * cudaError_t CUDARTAPI cudaStreamQuery(cudaStream_t stream);
 *
 * HIP 6.4
 * hipError_t hipStreamQuery(hipStream_t stream);
 */
#define cudaStreamQuery(s) __cuda(StreamQuery(s))

/**
 * cudaError_t cudaStreamBeginCapture(cudaStream_t stream, enum cudaStreamCaptureMode mode);
 */
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
#define cudaStreamIsCapturing(stream, pCaptureStatus) \
	__cuda(StreamIsCapturing(stream, pCaptureStatus))

/**
 * LUCA:
 * lcError_t lcStreamCopyAttributes(lcStream_t dst, lcStream_t src);
 */
#define cudaStreamCopyAttributes __cuda(StreamCopyAttributes)

/**
 * LUCA:
 * lcError_t lcStreamGetAttribute(lcStream_t hStream, lcStreamAttrID attr,
 *                                lcStreamAttrValue *value_out);
 */
#define cudaStreamGetAttribute __cuda(StreamGetAttribute)

/**
 * LUCA:
 * lcError_t lcStreamSetAttribute(lcStream_t hStream, lcStreamAttrID attr,
 *                                const lcStreamAttrValue *value);
 */
#define cudaStreamSetAttribute __cuda(StreamSetAttribute)

/**
 * LUCA:
 * lcError_t lcStreamGetPriority(lcStream_t hStream, int *priority);
 */
#define cudaStreamGetPriority __cuda(StreamGetPriority)

/**
 * LUCA:
 * lcError_t lcStreamGetFlags(lcStream_t hStream, unsigned int *flags);
 */
#define cudaStreamGetFlags __cuda(StreamGetFlags)

/**
 * CUDA 13
 * cudaError_t cudaStreamAddCallback(cudaStream_t stream, cudaStreamCallback_t callback,
 *                                   void *userData, unsigned int flags);
 */
#define cudaStreamAddCallback __cuda(StreamAddCallback)

/**
 * CUDA V13.0
 * cudaError_t cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
 *
 * HIP 6.4
 * hipError_t hipStreamWaitEvent(hipStream_t stream, hipEvent_t event, unsigned int flags);
 */
#define cudaStreamWaitEvent(s, e, f) __cuda(StreamWaitEvent(s, e, f))

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
#define cudaStreamGetCaptureInfo __cuda(StreamGetCaptureInfo)

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
#define cudaStreamUpdateCaptureDependencies \
	__cuda(StreamUpdateCaptureDependencies)

/**
 * CUDA 13.0
 * cudaError_t cudaThreadExchangeStreamCaptureMode(enum cudaStreamCaptureMode *mode);
 *
 * HIP 6.4
 * hipError_t hipThreadExchangeStreamCaptureMode(hipStreamCaptureMode* mode);
 */
#define cudaThreadExchangeStreamCaptureMode(m) \
	__cuda(ThreadExchangeStreamCaptureMode(m))

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
#define cudaUserObjectCreate __cuda(UserObjectCreate)

#endif
