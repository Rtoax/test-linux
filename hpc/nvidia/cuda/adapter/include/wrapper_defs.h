// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
/**
 * Input definitions:
 * - __USE_HIP__		AMD ROCm HIP
 * - __USE_HPCC__		Mars
 * - __USE_LUCA__		Luca
 *   LUCA_PHASE_II_PROJECT
 */
#ifndef __CUDA_ADAPTER_WRAPPER_DEFS_H
#define __CUDA_ADAPTER_WRAPPER_DEFS_H 1

/******************************************************************************\
 * HPCC: High Performance Computing Communications                            *
\******************************************************************************/
#if defined(__USE_HPCC__)
/* HPCC has CUDA-compatible APIs */
# define cuX(name) hc##name
# define cudaX(name) hc##name
# define CUX(name) HC##name
# define CUXcudaX(n1, n2) HC##n1##hc##n2
# define cudaXCudaX(n1, n2) hc##n1##Hpcc##n2
# define CUDAX(name) HC_##name
# define CUDA_ERROR_X(name) HCC_STATUS_##name
# define XcuX(a, b) a##hc##b
# define nvX(name) hc##name
# define __nv_X(name) __hpcc_##name
# define __NV_X(name) __HPCC_##name
# define NVX(name) HC##name
# define ncclX(name) hccl##name
# define NCCLX(name) HCCL##name
# define pncclX(name) phccl##name
/******************************************************************************\
 * LUCA                                                                       *
\******************************************************************************/
#elif defined(__USE_LUCA__)
/**
 * In the second phase of LUCA development, the filename changed, and the
 * definition was deleted once development was completed.
 */
# ifdef LUCA_PHASE_II_PROJECT
#  define cuX(name) lc##name
#  define cudaX(name) lc##name
#  define CUX(name) LC##name
#  define CUXcudaX(n1, n2) LC##n1##lc##n2
#  define cudaXCudaX(n1, n2) lc##n1##Luca##n2
#  define CUDAX(name) LC_##name
#  define CUDA_ERROR_X(name) LCC_STATUS_##name
#  define XcuX(a, b) a##lc##b
#  define nvX(name) lc##name
#  define NVX(name) LC##name
#  define ncclX(name) lccl##name
#  define NCCLX(name) LCCL##name
#  define pncclX(name) plccl##name
# else /* LUCA_PHASE_II_PROJECT */
#  define cuX(name) hc##name
#  define cudaX(name) hc##name
#  define CUX(name) HC##name
#  define CUXcudaX(n1, n2) HC##n1##hc##n2
#  define cudaXCudaX(n1, n2) hc##n1##Hpcc##n2
#  define CUDAX(name) HC_##name
#  define CUDA_ERROR_X(name) HCC_STATUS_##name
#  define XcuX(a, b) a##hc##b
#  define nvX(name) hc##name
#  define NVX(name) HC##name
#  define ncclX(name) hccl##name
#  define NCCLX(name) HCCL##name
#  define pncclX(name) phccl##name
# endif /* LUCA_PHASE_II_PROJECT */
# define __nv_X(name) __luca_##name
# define __NV_X(name) __LUCA_##name
/******************************************************************************\
 * AMD ROCm HIP                                                               *
\******************************************************************************/
#elif defined(__USE_HIP__)
# if !defined(__HIP_PLATFORM_AMD__) && !defined(__HIP_PLATFORM_NVIDIA__)
#  define __HIP_PLATFORM_AMD__
# endif
# define cuX(name) hip##name
# define cudaX(name) hip##name
# define CUX(name) HIP##name
/* TODO: CUXcudaX, cudaXCudaX */
# define CUDAX(name) HIP_##name
# define CUDA_ERROR_X(name) HIP_##name
# define XcuX(a, b) a##hip##b
# define nvX(name) hip##name
# define __nv_X(name) __hip_##name
# define __NV_X(name) __HIP_##name
# define NVX(name) HIP##name
/* ROCm rccl use 'nccl' prefix, see /usr/include/rccl/rccl.h */
# define ncclX(name) nccl##name
# define NCCLX(name) NCCL##name
# define pncclX(name) pnccl##name
#else
# error "Must define one of __USE_HPCC__, __USE_HIP__, __USE_LUCA__"
#endif

#endif
