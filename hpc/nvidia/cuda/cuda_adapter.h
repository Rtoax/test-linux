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
#define CUDA_ADAPTER_MINOR 3
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

#include "adapter/cuda.h"
#include "adapter/cuda_runtime.h"
#include "adapter/cuda_runtime_api.h"
#include "adapter/driver_types.h"

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

#define cudaMemAllocNodeParams	__cuda(MemAllocNodeParams)
#define cudaMemAllocationTypeInvalid	__cuda(MemAllocationTypeInvalid) /* 0 */
#define cudaMemAllocationTypePinned	__cuda(MemAllocationTypePinned) /* 1 */
#define cudaMemAllocationTypeManaged	__cuda(MemAllocationTypeManaged) /* 2 */
#define cudaMemAllocationTypeMax	__cuda(MemAllocationTypeMax) /* 0x7FFFFFFF */

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

#define cudaHostNodeParams	__cuda(HostNodeParams)

#define cudaKernelNodeParams __cuda(KernelNodeParams)

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

#include "adapter/nvrtc.h"

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

#include "adapter/device_types.h"
#include "adapter/cuda_fp6.h"
#include "adapter/cuda_fp8.h"
#include "adapter/cuda_bf16.h"

#include "adapter/cudnn.h"
#include "adapter/cusolver.h"
#include "adapter/cufile.h"
#include "adapter/cupti.h"
#include "adapter/nccl.h"

#endif
