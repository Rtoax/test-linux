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

#include "adapter/cuComplex.h"
#include "adapter/cublas.h"
#include "adapter/curand.h"
#include "adapter/cufft.h"
#include "adapter/cusparse.h"

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
