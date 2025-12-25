// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025 Rong Tao */
/**
 * Input definitions:
 * - __USE_HPCC__
 * - __USE_HIP__
 * - __USE_HIP_V2__: use V2 API, default: disable
 * - __USE_LUCA__
 * - LUCA_PHASE_II_PROJECT:
 *
 * - __NOT_USE_FP8__: include fp8 header
 *
 * - HAVE_NCCL
 * - HAVE_CUDNN
 * - HAVE_RCCL
 * - HAVE_HPCC
 * - HAVE_HCDNN
 * - HAVE_LCDNN
 * - HAVE_CUFILE
 * - HAVE_LCFILE
 * - HAVE_CUPTI
 * - HAVE_LCPTI
 * - HAVE_HIP
 * - HAVE_HIPBLASLT
 * - HAVE_HIP_FP8
 */
#ifndef __CUDA_COMPAT_H
#define __CUDA_COMPAT_H	1

/******************************************************************************\
 * HPCC: High Performance Computing Communications                            *
\******************************************************************************/
#ifdef __USE_HPCC__
# include <hcr/hc_runtime.h>
# include <hcr/hcrtc.h>
# include <hcc/hcc_internal.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include <hcsparse/hcsparse.h>
# include <hcrand/hcrand.h>
# include <hcfft/hcfft.h>
# include <hcsolver/hcsolver_common.h>
# ifdef HAVE_HCDNN
#  include <hcdnn/hcdnn.h>
# endif
/* TODO: add rtc */
# ifndef __NOT_USE_FP8__
#  include <hpcc_fp8.h>
# endif
# include <hpcc_fp16.h>
# ifdef __HPCC__
#  include <hpcc_cooperative_groups.h>
# endif
# include <hccl.h>
# include <hcfile.h>
# include <hcc/hcc_internal.h>
# include "cuda_adapter.h"
# ifndef HAVE_HPCC
#  error "Not found HPCC envrioment, but use HPCC"
# endif
# define CUNAME	"HPCC"
/******************************************************************************\
 * LUCA                                                                       *
\******************************************************************************/
#elif defined(__USE_LUCA__)
/**
 * In the second phase of LUCA development, the filename changed, and the
 * definition was deleted once development was completed.
 */
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcr/lc_runtime.h>
#  include <lcr/lcrtc.h>
#  include <lcc/lcc_internal.h>
#  include <lcblas/lcblas.h>
#  include <lcblas/lcblasLt.h>
#  include <lcsparse/lcsparse.h>
#  include <lcrand/lcrand.h>
#  include <lcfft/lcfft.h>
#  include <lcsolver/lcsolver_common.h>
#  ifdef HAVE_LCDNN
#   include <lcdnn/lcdnn.h>
#  endif
#  include <lccl.h>
#  ifdef HAVE_LCFILE
#   include <lcfile.h>
#  endif
#  ifdef HAVE_LCPTI
#   include <lcpti/lcpti.h>
#  endif
# else /* LUCA_PHASE_II_PROJECT */
#  include <hcr/hc_runtime.h>
#  include <hcr/hcrtc.h>
#  include <hcc/hcc_internal.h>
#  include <hcblas/hcblas.h>
#  include <hcblas/hcblasLt.h>
#  include <hcsparse/hcsparse.h>
#  include <hcrand/hcrand.h>
#  include <hcfft/hcfft.h>
#  include <hcsolver/hcsolver_common.h>
#  ifdef HAVE_LCDNN
#   include <hcdnn/hcdnn.h>
#  endif
#  include <hccl.h>
#  ifdef HAVE_LCFILE
#   include <hcfile.h>
#  endif
#  ifdef HAVE_LCPTI
#   include <hcpti/hcpti.h>
#  endif
# endif /* LUCA_PHASE_II_PROJECT */
# ifndef __NOT_USE_FP8__
#  include <luca_fp8.h>
# endif
# include <luca_fp16.h>
# ifdef __LUCA__
#  include <luca_cooperative_groups.h>
# endif
# include "cuda_adapter.h"
# define CUNAME	"LUCA"
/******************************************************************************\
 * AMD ROCm HIP                                                               *
\******************************************************************************/
#elif defined(__USE_HIP__)
# ifdef __USE_HIP_V2__
#  define HIPBLAS_V2
# endif
/**
 * Must define exactly one of __HIP_PLATFORM_AMD__ or __HIP_PLATFORM_NVIDIA__
 */
# define __HIP_PLATFORM_AMD__
# include <hip/hip_version.h>
# include <hip/hip_runtime.h>
# include <hip/hip_runtime_api.h>
# include <hip/hiprtc.h>
# include <hipfft/hipfft.h>
# include <hipsparse/hipsparse.h>
# include <hiprand/hiprand.h>
# include <hipsolver/hipsolver.h>
# include <hip/hip_cooperative_groups.h>
# define HIPBLAS_USE_HIP_HALF
# include <hipblas/hipblas.h>
# ifdef HAVE_HIPBLASLT
#  include <hipblaslt/hipblaslt.h>
# endif
# ifdef HAVE_HIP_FP8
#  include <hip/hip_fp8.h>
# endif
# include <hip/hip_fp16.h>
# ifdef HAVE_RCCL
#  include <rccl/rccl.h>
# endif
# include "cuda_adapter.h"
# ifndef HAVE_HIP
#  error "Not found ROCm HIP envrioment, but use HIP"
# endif
# define CUNAME	"ROCm HIP"
/******************************************************************************\
 * CUDA                                                                       *
\******************************************************************************/
#else /* fallback to CUDA */
/**
 * macro:
 * - CUDA_VERSION
 *   12020: V12.2.140
 */
# include <nvrtc.h>
# include <cuda.h>
# include <cuda_runtime.h>
# include <cuda_runtime_api.h>
# include <cublas_v2.h>
# include <cublasLt.h>
# include <cufft.h>
# include <curand.h>
# include <cusolver_common.h>
# if CUDA_VERSION > 12040
#  include <cuda_fp6.h>
# endif
# ifndef __NOT_USE_FP8__
#  include <cuda_fp8.h>
# endif
# include <cuda_fp16.h>
# include <cuda_bf16.h>
# define DISABLE_CUSPARSE_DEPRECATED	1
# include <cusparse.h>
# include <cooperative_groups.h>
# ifdef HAVE_NCCL
#  include <nccl.h>
# endif
# ifdef HAVE_CUDNN
#  include <cudnn.h>
# endif
# ifdef HAVE_CUFILE
#  include <cufile.h>
# endif
# ifdef HAVE_CUPTI
#  include <cupti.h>
#  include <cupti_pmsampling.h>
#  include <cupti_profiler_target.h>
#  include <cupti_profiler_host.h>
#  include <cupti_range_profiler.h>
#  include <cupti_target.h>
# endif
# define CUNAME	"NVIDIA CUDA"
#endif

#endif
