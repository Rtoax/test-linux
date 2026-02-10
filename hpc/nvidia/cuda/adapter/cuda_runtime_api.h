// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_RUNTIME_API_H
#define __CUDA_ADAPTER_CUDA_RUNTIME_API_H 1

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

#endif
