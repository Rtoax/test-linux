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

/**
 * typedef enum cudaError_enum { ... } CUresult;
 * HIP: /usr/include/hip/amd_detail/amd_hip_runtime.h
 * #define CUDA_SUCCESS hipSuccess
 */
#ifndef CUDA_SUCCESS
#define CUDA_SUCCESS __CUDA_ERROR(SUCCESS);
#endif
#define CUDA_ERROR_INVALID_VALUE __CUDA_ERROR(ERROR_INVALID_VALUE)
#define CUDA_ERROR_OUT_OF_MEMORY __CUDA_ERROR(ERROR_OUT_OF_MEMORY)
#define CUDA_ERROR_NOT_INITIALIZED __CUDA_ERROR(ERROR_NOT_INITIALIZED)
#define CUDA_ERROR_DEINITIALIZED __CUDA_ERROR(ERROR_DEINITIALIZED)
#define CUDA_ERROR_PROFILER_DISABLED __CUDA_ERROR(ERROR_PROFILER_DISABLED)
#define CUDA_ERROR_PROFILER_NOT_INITIALIZED __CUDA_ERROR(ERROR_PROFILER_NOT_INITIALIZED)
#define CUDA_ERROR_PROFILER_ALREADY_STARTED __CUDA_ERROR(ERROR_PROFILER_ALREADY_STARTED)
#define CUDA_ERROR_PROFILER_ALREADY_STOPPED __CUDA_ERROR(ERROR_PROFILER_ALREADY_STOPPED)
#define CUDA_ERROR_STUB_LIBRARY __CUDA_ERROR(ERROR_STUB_LIBRARY)
#define CUDA_ERROR_CALL_REQUIRES_NEWER_DRIVER __CUDA_ERROR(ERROR_CALL_REQUIRES_NEWER_DRIVER)
#define CUDA_ERROR_DEVICE_UNAVAILABLE __CUDA_ERROR(ERROR_DEVICE_UNAVAILABLE)
#define CUDA_ERROR_NO_DEVICE __CUDA_ERROR(ERROR_NO_DEVICE)
#define CUDA_ERROR_INVALID_DEVICE __CUDA_ERROR(ERROR_INVALID_DEVICE) /* 101 */
#define CUDA_ERROR_DEVICE_NOT_LICENSED __CUDA_ERROR(ERROR_DEVICE_NOT_LICENSED)
#define CUDA_ERROR_INVALID_IMAGE __CUDA_ERROR(ERROR_INVALID_IMAGE)
#define CUDA_ERROR_INVALID_CONTEXT __CUDA_ERROR(ERROR_INVALID_CONTEXT)
#define CUDA_ERROR_CONTEXT_ALREADY_CURRENT __CUDA_ERROR(ERROR_CONTEXT_ALREADY_CURRENT)
#define CUDA_ERROR_MAP_FAILED __CUDA_ERROR(ERROR_MAP_FAILED)
#define CUDA_ERROR_UNMAP_FAILED __CUDA_ERROR(ERROR_UNMAP_FAILED)
#define CUDA_ERROR_ARRAY_IS_MAPPED __CUDA_ERROR(ERROR_ARRAY_IS_MAPPED)
#define CUDA_ERROR_ALREADY_MAPPED __CUDA_ERROR(ERROR_ALREADY_MAPPED)
#define CUDA_ERROR_NO_BINARY_FOR_GPU __CUDA_ERROR(ERROR_NO_BINARY_FOR_GPU)
#define CUDA_ERROR_ALREADY_ACQUIRED __CUDA_ERROR(ERROR_ALREADY_ACQUIRED)
#define CUDA_ERROR_NOT_MAPPED __CUDA_ERROR(ERROR_NOT_MAPPED)
#define CUDA_ERROR_NOT_MAPPED_AS_ARRAY __CUDA_ERROR(ERROR_NOT_MAPPED_AS_ARRAY)
#define CUDA_ERROR_NOT_MAPPED_AS_POINTER __CUDA_ERROR(ERROR_NOT_MAPPED_AS_POINTER)
#define CUDA_ERROR_ECC_UNCORRECTABLE __CUDA_ERROR(ERROR_ECC_UNCORRECTABLE)
#define CUDA_ERROR_UNSUPPORTED_LIMIT __CUDA_ERROR(ERROR_UNSUPPORTED_LIMIT)
#define CUDA_ERROR_CONTEXT_ALREADY_IN_USE __CUDA_ERROR(ERROR_CONTEXT_ALREADY_IN_USE)
#define CUDA_ERROR_PEER_ACCESS_UNSUPPORTED __CUDA_ERROR(ERROR_PEER_ACCESS_UNSUPPORTED)
#define CUDA_ERROR_INVALID_PTX __CUDA_ERROR(ERROR_INVALID_PTX)
#define CUDA_ERROR_INVALID_GRAPHICS_CONTEXT __CUDA_ERROR(ERROR_INVALID_GRAPHICS_CONTEXT)
#define CUDA_ERROR_NVLINK_UNCORRECTABLE __CUDA_ERROR(ERROR_NVLINK_UNCORRECTABLE)
#define CUDA_ERROR_JIT_COMPILER_NOT_FOUND __CUDA_ERROR(ERROR_JIT_COMPILER_NOT_FOUND)
#define CUDA_ERROR_UNSUPPORTED_PTX_VERSION __CUDA_ERROR(ERROR_UNSUPPORTED_PTX_VERSION)
#define CUDA_ERROR_JIT_COMPILATION_DISABLED __CUDA_ERROR(ERROR_JIT_COMPILATION_DISABLED)
#define CUDA_ERROR_UNSUPPORTED_EXEC_AFFINITY __CUDA_ERROR(ERROR_UNSUPPORTED_EXEC_AFFINITY)
#define CUDA_ERROR_UNSUPPORTED_DEVSIDE_SYNC __CUDA_ERROR(ERROR_UNSUPPORTED_DEVSIDE_SYNC)
#define CUDA_ERROR_CONTAINED __CUDA_ERROR(ERROR_CONTAINED)
#define CUDA_ERROR_INVALID_SOURCE __CUDA_ERROR(ERROR_INVALID_SOURCE)
#define CUDA_ERROR_FILE_NOT_FOUND __CUDA_ERROR(ERROR_FILE_NOT_FOUND) /* 301 */
#define CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND __CUDA_ERROR(ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND)
#define CUDA_ERROR_SHARED_OBJECT_INIT_FAILED __CUDA_ERROR(ERROR_SHARED_OBJECT_INIT_FAILED)
#define CUDA_ERROR_OPERATING_SYSTEM __CUDA_ERROR(ERROR_OPERATING_SYSTEM)
#define CUDA_ERROR_INVALID_HANDLE __CUDA_ERROR(ERROR_INVALID_HANDLE) /* 400 */
#define CUDA_ERROR_ILLEGAL_STATE __CUDA_ERROR(ERROR_ILLEGAL_STATE)
#define CUDA_ERROR_LOSSY_QUERY __CUDA_ERROR(ERROR_LOSSY_QUERY)
#define CUDA_ERROR_NOT_FOUND __CUDA_ERROR(ERROR_NOT_FOUND) /* 500 */
#define CUDA_ERROR_NOT_READY __CUDA_ERROR(ERROR_NOT_READY)
#define CUDA_ERROR_ILLEGAL_ADDRESS __CUDA_ERROR(ERROR_ILLEGAL_ADDRESS)
#define CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES __CUDA_ERROR(ERROR_LAUNCH_OUT_OF_RESOURCES)
#define CUDA_ERROR_LAUNCH_TIMEOUT __CUDA_ERROR(ERROR_LAUNCH_TIMEOUT)
#define CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING __CUDA_ERROR(ERROR_LAUNCH_INCOMPATIBLE_TEXTURING)
#define CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED __CUDA_ERROR(ERROR_PEER_ACCESS_ALREADY_ENABLED)
#define CUDA_ERROR_PEER_ACCESS_NOT_ENABLED __CUDA_ERROR(ERROR_PEER_ACCESS_NOT_ENABLED)
#define CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE __CUDA_ERROR(ERROR_PRIMARY_CONTEXT_ACTIVE)
#define CUDA_ERROR_CONTEXT_IS_DESTROYED __CUDA_ERROR(ERROR_CONTEXT_IS_DESTROYED)
#define CUDA_ERROR_ASSERT __CUDA_ERROR(ERROR_ASSERT)
#define CUDA_ERROR_TOO_MANY_PEERS __CUDA_ERROR(ERROR_TOO_MANY_PEERS)
#define CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED __CUDA_ERROR(ERROR_HOST_MEMORY_ALREADY_REGISTERED)
#define CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED __CUDA_ERROR(ERROR_HOST_MEMORY_NOT_REGISTERED)
#define CUDA_ERROR_HARDWARE_STACK_ERROR __CUDA_ERROR(ERROR_HARDWARE_STACK_ERROR)
#define CUDA_ERROR_ILLEGAL_INSTRUCTION __CUDA_ERROR(ERROR_ILLEGAL_INSTRUCTION)
#define CUDA_ERROR_MISALIGNED_ADDRESS __CUDA_ERROR(ERROR_MISALIGNED_ADDRESS)
#define CUDA_ERROR_INVALID_ADDRESS_SPACE __CUDA_ERROR(ERROR_INVALID_ADDRESS_SPACE)
#define CUDA_ERROR_INVALID_PC __CUDA_ERROR(ERROR_INVALID_PC)
#define CUDA_ERROR_LAUNCH_FAILED __CUDA_ERROR(ERROR_LAUNCH_FAILED)
#define CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE __CUDA_ERROR(ERROR_COOPERATIVE_LAUNCH_TOO_LARGE)
#define CUDA_ERROR_TENSOR_MEMORY_LEAK __CUDA_ERROR(ERROR_TENSOR_MEMORY_LEAK)
#define CUDA_ERROR_NOT_PERMITTED __CUDA_ERROR(ERROR_NOT_PERMITTED)
#define CUDA_ERROR_NOT_SUPPORTED __CUDA_ERROR(ERROR_NOT_SUPPORTED)
#define CUDA_ERROR_SYSTEM_NOT_READY __CUDA_ERROR(ERROR_SYSTEM_NOT_READY)
#define CUDA_ERROR_SYSTEM_DRIVER_MISMATCH __CUDA_ERROR(ERROR_SYSTEM_DRIVER_MISMATCH)
#define CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE __CUDA_ERROR(ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE)
#define CUDA_ERROR_MPS_CONNECTION_FAILED __CUDA_ERROR(ERROR_MPS_CONNECTION_FAILED)
#define CUDA_ERROR_MPS_RPC_FAILURE __CUDA_ERROR(ERROR_MPS_RPC_FAILURE)
#define CUDA_ERROR_MPS_SERVER_NOT_READY __CUDA_ERROR(ERROR_MPS_SERVER_NOT_READY)
#define CUDA_ERROR_MPS_MAX_CLIENTS_REACHED __CUDA_ERROR(ERROR_MPS_MAX_CLIENTS_REACHED)
#define CUDA_ERROR_MPS_MAX_CONNECTIONS_REACHED __CUDA_ERROR(ERROR_MPS_MAX_CONNECTIONS_REACHED)
#define CUDA_ERROR_MPS_CLIENT_TERMINATED __CUDA_ERROR(ERROR_MPS_CLIENT_TERMINATED)
#define CUDA_ERROR_CDP_NOT_SUPPORTED __CUDA_ERROR(ERROR_CDP_NOT_SUPPORTED)
#define CUDA_ERROR_CDP_VERSION_MISMATCH __CUDA_ERROR(ERROR_CDP_VERSION_MISMATCH)
#define CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED __CUDA_ERROR(ERROR_STREAM_CAPTURE_UNSUPPORTED)
#define CUDA_ERROR_STREAM_CAPTURE_INVALIDATED __CUDA_ERROR(ERROR_STREAM_CAPTURE_INVALIDATED)
#define CUDA_ERROR_STREAM_CAPTURE_MERGE __CUDA_ERROR(ERROR_STREAM_CAPTURE_MERGE)
#define CUDA_ERROR_STREAM_CAPTURE_UNMATCHED __CUDA_ERROR(ERROR_STREAM_CAPTURE_UNMATCHED)
#define CUDA_ERROR_STREAM_CAPTURE_UNJOINED __CUDA_ERROR(ERROR_STREAM_CAPTURE_UNJOINED)
#define CUDA_ERROR_STREAM_CAPTURE_ISOLATION __CUDA_ERROR(ERROR_STREAM_CAPTURE_ISOLATION)
#define CUDA_ERROR_STREAM_CAPTURE_IMPLICIT __CUDA_ERROR(ERROR_STREAM_CAPTURE_IMPLICIT)
#define CUDA_ERROR_CAPTURED_EVENT __CUDA_ERROR(ERROR_CAPTURED_EVENT)
#define CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD __CUDA_ERROR(ERROR_STREAM_CAPTURE_WRONG_THREAD)
#define CUDA_ERROR_TIMEOUT __CUDA_ERROR(ERROR_TIMEOUT)
#define CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE __CUDA_ERROR(ERROR_GRAPH_EXEC_UPDATE_FAILURE)
#define CUDA_ERROR_EXTERNAL_DEVICE __CUDA_ERROR(ERROR_EXTERNAL_DEVICE)
#define CUDA_ERROR_INVALID_CLUSTER_SIZE __CUDA_ERROR(ERROR_INVALID_CLUSTER_SIZE)
#define CUDA_ERROR_FUNCTION_NOT_LOADED __CUDA_ERROR(ERROR_FUNCTION_NOT_LOADED)
#define CUDA_ERROR_INVALID_RESOURCE_TYPE __CUDA_ERROR(ERROR_INVALID_RESOURCE_TYPE)
#define CUDA_ERROR_INVALID_RESOURCE_CONFIGURATION __CUDA_ERROR(ERROR_INVALID_RESOURCE_CONFIGURATION)
#define CUDA_ERROR_KEY_ROTATION __CUDA_ERROR(ERROR_KEY_ROTATION)
#define CUDA_ERROR_UNKNOWN __CUDA_ERROR(ERROR_UNKNOWN)

/**
 * CUDA: struct __device_builtin__ cudaDeviceProp {...};
 */
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
/**
 * CUDA:
 * cuda.h: typedef enum cudaError_enum { ... } CUresult;
 */
# undef CUresult
/**
 * CUDA:
 * cuda.h: typedef CUdevice_v1 CUdevice;
 */
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
