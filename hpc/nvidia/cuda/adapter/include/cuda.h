// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_H
#define __CUDA_ADAPTER_CUDA_H 1

/**
 * TODO: Adapt to multi CUDA versions
 */
#ifndef CUDA_VERSION
#define CUDA_VERSION 13000
#endif

#include "wrapper_defs.h"

/**
 * CUDA: typedef enum cudaError_enum { ... } CUresult;
 * LUCA: typedef enum lcc_status { ... } lcc_status_t;
 * HIP: enum { HIP_SUCCESS = 0, ... };
 *
 * Note: In fact, HIP does not provide a CUresult type that is compatible
 * with CUDA.
 */
/**
 * CUDA 13: typedef CUdevice_v1 CUdevice;
 */
/**
 * CUDA: typedef struct CUmod_st *CUmodule;
 * LUCA: typedef struct LCmod_st *LCmodule;
 */
/**
 * CUDA: typedef struct CUfunc_st *CUfunction;
 * LUCA: typedef struct LCfunc_st *LCfunction;
 */
/**
 * CUDA: typedef enum CUjit_option_enum {...} CUjit_option;
 */
#if defined(__USE_HPCC__)
# include "driver_types.h"
# define CUresult hcError_t
# define CUdevice hcDevice_t
# define CUmodule hcModule_t
# define CUfunction hcFunction_t
# define CUjit_option hcJitOption
#elif defined(__USE_LUCA__)
# include "driver_types.h"
# ifdef LUCA_PHASE_II_PROJECT
#  define CUresult lcError_t
#  define CUdevice lcDevice_t
#  define CUmodule lcModule_t
#  define CUfunction lcFunction_t
#  define CUjit_option lcJitOption
# else
#  define CUresult hcError_t
#  define CUdevice hcDevice_t
#  define CUmodule hcModule_t
#  define CUfunction hcFunction_t
#  define CUjit_option hcJitOption
# endif
#elif defined(__USE_HIP__)
# include "driver_types.h"
/* Because hip_runtime_api.h: typedef struct ihipModule_t* hipModule_t; */
# include "cuda_runtime_api.h"
# define CUresult hipError_t
# define CUdevice hipDevice_t
# define CUmodule hipModule_t
# define CUfunction hipFunction_t
# define CUjit_option hipJitOption
#endif

/**
 * HIP: /usr/include/hip/amd_detail/amd_hip_runtime.h
 *      #define CUDA_SUCCESS hipSuccess
 */
#ifndef CUDA_SUCCESS
#define CUDA_SUCCESS cudaX(Success)
#endif
#define CUDA_ERROR_INVALID_VALUE cudaX(ErrorInvalidValue) /* 1 */
#define CUDA_ERROR_OUT_OF_MEMORY CUDA_ERROR_X(ERROR_OUT_OF_MEMORY) /* 2 */
#define CUDA_ERROR_NOT_INITIALIZED CUDA_ERROR_X(ERROR_NOT_INITIALIZED) /* 3 */
#define CUDA_ERROR_DEINITIALIZED CUDA_ERROR_X(ERROR_DEINITIALIZED)
#define CUDA_ERROR_PROFILER_DISABLED CUDA_ERROR_X(ERROR_PROFILER_DISABLED)
#define CUDA_ERROR_PROFILER_NOT_INITIALIZED \
	CUDA_ERROR_X(ERROR_PROFILER_NOT_INITIALIZED)
#define CUDA_ERROR_PROFILER_ALREADY_STARTED \
	CUDA_ERROR_X(ERROR_PROFILER_ALREADY_STARTED)
#define CUDA_ERROR_PROFILER_ALREADY_STOPPED \
	CUDA_ERROR_X(ERROR_PROFILER_ALREADY_STOPPED)
#define CUDA_ERROR_STUB_LIBRARY CUDA_ERROR_X(ERROR_STUB_LIBRARY)
#define CUDA_ERROR_CALL_REQUIRES_NEWER_DRIVER \
	CUDA_ERROR_X(ERROR_CALL_REQUIRES_NEWER_DRIVER)
#define CUDA_ERROR_DEVICE_UNAVAILABLE CUDA_ERROR_X(ERROR_DEVICE_UNAVAILABLE)
#define CUDA_ERROR_NO_DEVICE CUDA_ERROR_X(ERROR_NO_DEVICE)
#define CUDA_ERROR_INVALID_DEVICE CUDA_ERROR_X(ERROR_INVALID_DEVICE) /* 101 */
#define CUDA_ERROR_DEVICE_NOT_LICENSED CUDA_ERROR_X(ERROR_DEVICE_NOT_LICENSED)
#define CUDA_ERROR_INVALID_IMAGE CUDA_ERROR_X(ERROR_INVALID_IMAGE)
#define CUDA_ERROR_INVALID_CONTEXT CUDA_ERROR_X(ERROR_INVALID_CONTEXT)
#define CUDA_ERROR_CONTEXT_ALREADY_CURRENT \
	CUDA_ERROR_X(ERROR_CONTEXT_ALREADY_CURRENT)
#define CUDA_ERROR_MAP_FAILED CUDA_ERROR_X(ERROR_MAP_FAILED)
#define CUDA_ERROR_UNMAP_FAILED CUDA_ERROR_X(ERROR_UNMAP_FAILED)
#define CUDA_ERROR_ARRAY_IS_MAPPED CUDA_ERROR_X(ERROR_ARRAY_IS_MAPPED)
#define CUDA_ERROR_ALREADY_MAPPED CUDA_ERROR_X(ERROR_ALREADY_MAPPED)
#define CUDA_ERROR_NO_BINARY_FOR_GPU CUDA_ERROR_X(ERROR_NO_BINARY_FOR_GPU)
#define CUDA_ERROR_ALREADY_ACQUIRED CUDA_ERROR_X(ERROR_ALREADY_ACQUIRED)
#define CUDA_ERROR_NOT_MAPPED CUDA_ERROR_X(ERROR_NOT_MAPPED)
#define CUDA_ERROR_NOT_MAPPED_AS_ARRAY CUDA_ERROR_X(ERROR_NOT_MAPPED_AS_ARRAY)
#define CUDA_ERROR_NOT_MAPPED_AS_POINTER \
	CUDA_ERROR_X(ERROR_NOT_MAPPED_AS_POINTER)
#define CUDA_ERROR_ECC_UNCORRECTABLE CUDA_ERROR_X(ERROR_ECC_UNCORRECTABLE)
#define CUDA_ERROR_UNSUPPORTED_LIMIT CUDA_ERROR_X(ERROR_UNSUPPORTED_LIMIT)
#define CUDA_ERROR_CONTEXT_ALREADY_IN_USE \
	CUDA_ERROR_X(ERROR_CONTEXT_ALREADY_IN_USE)
#define CUDA_ERROR_PEER_ACCESS_UNSUPPORTED \
	CUDA_ERROR_X(ERROR_PEER_ACCESS_UNSUPPORTED)
#define CUDA_ERROR_INVALID_PTX CUDA_ERROR_X(ERROR_INVALID_PTX)
#define CUDA_ERROR_INVALID_GRAPHICS_CONTEXT \
	CUDA_ERROR_X(ERROR_INVALID_GRAPHICS_CONTEXT)
#define CUDA_ERROR_NVLINK_UNCORRECTABLE CUDA_ERROR_X(ERROR_NVLINK_UNCORRECTABLE)
#define CUDA_ERROR_JIT_COMPILER_NOT_FOUND \
	CUDA_ERROR_X(ERROR_JIT_COMPILER_NOT_FOUND)
#define CUDA_ERROR_UNSUPPORTED_PTX_VERSION \
	CUDA_ERROR_X(ERROR_UNSUPPORTED_PTX_VERSION)
#define CUDA_ERROR_JIT_COMPILATION_DISABLED \
	CUDA_ERROR_X(ERROR_JIT_COMPILATION_DISABLED)
#define CUDA_ERROR_UNSUPPORTED_EXEC_AFFINITY \
	CUDA_ERROR_X(ERROR_UNSUPPORTED_EXEC_AFFINITY)
#define CUDA_ERROR_UNSUPPORTED_DEVSIDE_SYNC \
	CUDA_ERROR_X(ERROR_UNSUPPORTED_DEVSIDE_SYNC)
#define CUDA_ERROR_CONTAINED CUDA_ERROR_X(ERROR_CONTAINED)
#define CUDA_ERROR_INVALID_SOURCE CUDA_ERROR_X(ERROR_INVALID_SOURCE)
#define CUDA_ERROR_FILE_NOT_FOUND CUDA_ERROR_X(ERROR_FILE_NOT_FOUND) /* 301 */
#define CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND \
	CUDA_ERROR_X(ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND)
#define CUDA_ERROR_SHARED_OBJECT_INIT_FAILED \
	CUDA_ERROR_X(ERROR_SHARED_OBJECT_INIT_FAILED)
#define CUDA_ERROR_OPERATING_SYSTEM CUDA_ERROR_X(ERROR_OPERATING_SYSTEM)
#define CUDA_ERROR_INVALID_HANDLE CUDA_ERROR_X(ERROR_INVALID_HANDLE) /* 400 */
#define CUDA_ERROR_ILLEGAL_STATE CUDA_ERROR_X(ERROR_ILLEGAL_STATE)
#define CUDA_ERROR_LOSSY_QUERY CUDA_ERROR_X(ERROR_LOSSY_QUERY)
#define CUDA_ERROR_NOT_FOUND CUDA_ERROR_X(ERROR_NOT_FOUND) /* 500 */
#define CUDA_ERROR_NOT_READY CUDA_ERROR_X(ERROR_NOT_READY)
#define CUDA_ERROR_ILLEGAL_ADDRESS CUDA_ERROR_X(ERROR_ILLEGAL_ADDRESS)
#define CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES \
	CUDA_ERROR_X(ERROR_LAUNCH_OUT_OF_RESOURCES)
#define CUDA_ERROR_LAUNCH_TIMEOUT CUDA_ERROR_X(ERROR_LAUNCH_TIMEOUT)
#define CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING \
	CUDA_ERROR_X(ERROR_LAUNCH_INCOMPATIBLE_TEXTURING)
#define CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED \
	CUDA_ERROR_X(ERROR_PEER_ACCESS_ALREADY_ENABLED)
#define CUDA_ERROR_PEER_ACCESS_NOT_ENABLED \
	CUDA_ERROR_X(ERROR_PEER_ACCESS_NOT_ENABLED)
#define CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE \
	CUDA_ERROR_X(ERROR_PRIMARY_CONTEXT_ACTIVE)
#define CUDA_ERROR_CONTEXT_IS_DESTROYED CUDA_ERROR_X(ERROR_CONTEXT_IS_DESTROYED)
#define CUDA_ERROR_ASSERT CUDA_ERROR_X(ERROR_ASSERT)
#define CUDA_ERROR_TOO_MANY_PEERS CUDA_ERROR_X(ERROR_TOO_MANY_PEERS)
#define CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED \
	CUDA_ERROR_X(ERROR_HOST_MEMORY_ALREADY_REGISTERED)
#define CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED \
	CUDA_ERROR_X(ERROR_HOST_MEMORY_NOT_REGISTERED)
#define CUDA_ERROR_HARDWARE_STACK_ERROR CUDA_ERROR_X(ERROR_HARDWARE_STACK_ERROR)
#define CUDA_ERROR_ILLEGAL_INSTRUCTION CUDA_ERROR_X(ERROR_ILLEGAL_INSTRUCTION)
#define CUDA_ERROR_MISALIGNED_ADDRESS CUDA_ERROR_X(ERROR_MISALIGNED_ADDRESS)
#define CUDA_ERROR_INVALID_ADDRESS_SPACE \
	CUDA_ERROR_X(ERROR_INVALID_ADDRESS_SPACE)
#define CUDA_ERROR_INVALID_PC CUDA_ERROR_X(ERROR_INVALID_PC)
#define CUDA_ERROR_LAUNCH_FAILED CUDA_ERROR_X(ERROR_LAUNCH_FAILED)
#define CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE \
	CUDA_ERROR_X(ERROR_COOPERATIVE_LAUNCH_TOO_LARGE)
#define CUDA_ERROR_TENSOR_MEMORY_LEAK CUDA_ERROR_X(ERROR_TENSOR_MEMORY_LEAK)
#define CUDA_ERROR_NOT_PERMITTED CUDA_ERROR_X(ERROR_NOT_PERMITTED)
#define CUDA_ERROR_NOT_SUPPORTED CUDA_ERROR_X(ERROR_NOT_SUPPORTED)
#define CUDA_ERROR_SYSTEM_NOT_READY CUDA_ERROR_X(ERROR_SYSTEM_NOT_READY)
#define CUDA_ERROR_SYSTEM_DRIVER_MISMATCH \
	CUDA_ERROR_X(ERROR_SYSTEM_DRIVER_MISMATCH)
#define CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE \
	CUDA_ERROR_X(ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE)
#define CUDA_ERROR_MPS_CONNECTION_FAILED \
	CUDA_ERROR_X(ERROR_MPS_CONNECTION_FAILED)
#define CUDA_ERROR_MPS_RPC_FAILURE CUDA_ERROR_X(ERROR_MPS_RPC_FAILURE)
#define CUDA_ERROR_MPS_SERVER_NOT_READY CUDA_ERROR_X(ERROR_MPS_SERVER_NOT_READY)
#define CUDA_ERROR_MPS_MAX_CLIENTS_REACHED \
	CUDA_ERROR_X(ERROR_MPS_MAX_CLIENTS_REACHED)
#define CUDA_ERROR_MPS_MAX_CONNECTIONS_REACHED \
	CUDA_ERROR_X(ERROR_MPS_MAX_CONNECTIONS_REACHED)
#define CUDA_ERROR_MPS_CLIENT_TERMINATED \
	CUDA_ERROR_X(ERROR_MPS_CLIENT_TERMINATED)
#define CUDA_ERROR_CDP_NOT_SUPPORTED CUDA_ERROR_X(ERROR_CDP_NOT_SUPPORTED)
#define CUDA_ERROR_CDP_VERSION_MISMATCH CUDA_ERROR_X(ERROR_CDP_VERSION_MISMATCH)
#define CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_UNSUPPORTED)
#define CUDA_ERROR_STREAM_CAPTURE_INVALIDATED \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_INVALIDATED)
#define CUDA_ERROR_STREAM_CAPTURE_MERGE CUDA_ERROR_X(ERROR_STREAM_CAPTURE_MERGE)
#define CUDA_ERROR_STREAM_CAPTURE_UNMATCHED \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_UNMATCHED)
#define CUDA_ERROR_STREAM_CAPTURE_UNJOINED \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_UNJOINED)
#define CUDA_ERROR_STREAM_CAPTURE_ISOLATION \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_ISOLATION)
#define CUDA_ERROR_STREAM_CAPTURE_IMPLICIT \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_IMPLICIT)
#define CUDA_ERROR_CAPTURED_EVENT CUDA_ERROR_X(ERROR_CAPTURED_EVENT)
#define CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD \
	CUDA_ERROR_X(ERROR_STREAM_CAPTURE_WRONG_THREAD)
#define CUDA_ERROR_TIMEOUT CUDA_ERROR_X(ERROR_TIMEOUT)
#define CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE \
	CUDA_ERROR_X(ERROR_GRAPH_EXEC_UPDATE_FAILURE)
#define CUDA_ERROR_EXTERNAL_DEVICE CUDA_ERROR_X(ERROR_EXTERNAL_DEVICE)
#define CUDA_ERROR_INVALID_CLUSTER_SIZE CUDA_ERROR_X(ERROR_INVALID_CLUSTER_SIZE)
#define CUDA_ERROR_FUNCTION_NOT_LOADED CUDA_ERROR_X(ERROR_FUNCTION_NOT_LOADED)
#define CUDA_ERROR_INVALID_RESOURCE_TYPE \
	CUDA_ERROR_X(ERROR_INVALID_RESOURCE_TYPE)
#define CUDA_ERROR_INVALID_RESOURCE_CONFIGURATION \
	CUDA_ERROR_X(ERROR_INVALID_RESOURCE_CONFIGURATION)
#define CUDA_ERROR_KEY_ROTATION CUDA_ERROR_X(ERROR_KEY_ROTATION)
#define CUDA_ERROR_UNKNOWN CUDA_ERROR_X(ERROR_UNKNOWN)

/**
 * CUDA: typedef __device_builtin__ struct CUstream_st *cudaStream_t;
 */
#define CUstream_st CUX(stream_st)

/**
 * CUDA: typedef struct CUstream_st *CUstream;
 */
#define CUstream CUX(stream)

/**
 * CUDA:
 * driver_types.h: typedef struct CUevent_st *cudaEvent_t;
 * cuda.h: typedef struct CUevent_st *CUevent;
 *
 * HPCC: typedef struct HCevent_st *hcEvent_t;
 * HIP: typedef struct ihipEvent_t* hipEvent_t;
 */
#ifdef __USE_HIP__
#define CUevent_st ihipEvent_t
#else
#define CUevent_st CUX(event_st)
#endif
/**
 * CUDA: typedef struct CUevent_st *CUevent;
 * LUCA: typedef struct LCevent_st *LCevent;
 */
#define CUevent CUX(event)

/**
 * CUDA 13:
 * CUresult cuGetErrorName(CUresult error, const char **pStr);
 */
#if defined(__USE_LUCA__) || defined(__USE_HPCC__) || defined(__USE_HIP__)
#define cuGetErrorName(error, pStr)                                     \
	do {                                                            \
		const char **__pstr = pStr;                             \
		*__pstr = "cuGetErrorName(): Function not implemented"; \
	} while (0)
#endif

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
#define cuDeviceGet(pdevice, dev_id) cuX(DeviceGet(pdevice, dev_id))

/**
 * CUresult cuDeviceComputeCapability(int *major, int *minor, CUdevice dev);
 */
#define cuDeviceComputeCapability(pmajor, pminor, pdev) \
	cuX(DeviceComputeCapability(pmajor, pminor, pdev))

/**
 * CUDA 13
 * CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX,
 *                         unsigned int gridDimY, unsigned int gridDimZ,
 *                         unsigned int blockDimX, unsigned int blockDimY,
 *                         unsigned int blockDimZ, unsigned int sharedMemBytes,
 *                         CUstream hStream, void **kernelParams, void **extra);
 */
#define cuLaunchKernel cuX(LaunchKernel)

/**
 * CUDA 13
 * CUresult cuModuleLoad(CUmodule* module, const char *fname);
 *
 * HIP
 * hipError_t hipModuleLoad(hipModule_t *module, const char* fname);
 */
#define cuModuleLoad(pmodule, name) cuX(ModuleLoad(pmodule, name))

/**
 * CUDA 13
 * CUresult cuModuleUnload(CUmodule hmod);
 *
 * HIP
 * typedef struct ihipModule_t* hipModule_t;
 * hipError_t hipModuleUnload(hipModule_t module);
 */
#define cuModuleUnload(mod) cuX(ModuleUnload(mod))

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
#define cuModuleGetFunction(pfunc, mod, name) \
	cuX(ModuleGetFunction(pfunc, mod, name))

/**
 * CUDA 13:
 * CUresult cuModuleLoadData(CUmodule *module, const void *image);
 *
 * HIP
 * hipError_t hipModuleLoadData(hipModule_t* module, const void* image);
 */
#define cuModuleLoadData cuX(ModuleLoadData)

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
#define cuModuleLoadDataEx cuX(ModuleLoadDataEx)

#endif
