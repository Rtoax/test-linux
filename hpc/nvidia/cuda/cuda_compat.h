// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Input definitions:
 * - __USE_HPCC__
 * - __USE_HIP__
 * - __USE_LUCA__
 * - __USE_HIP_V2__: use V2 API, default: disable
 */
#ifndef __CUDA_COMPAT_H
#define __CUDA_COMPAT_H	1

#ifdef __USE_HPCC__
# include <hcr/hc_runtime.h>
# include <hcr/hcrtc.h>
# include <hcc/hcc_internal.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include <hcsparse/hcsparse.h>
# include <hcrand/hcrand.h>
# include <hcfft/hcfft.h>
/* TODO: add rtc */
# include <hpcc_fp8.h>
# include <hpcc_fp16.h>
#ifdef __HPCC__
#  include <hpcc_cooperative_groups.h>
#endif
# include <hccl.h>
# include "cuda_adapter.h"
# ifndef HAVE_HPCC
#  error "Not found HPCC envrioment, but use HPCC"
# endif
# define CUNAME	"MetaX"
#elif defined(__USE_LUCA__)
/* FIXME: luca has it's own headers */
# include <hcr/hc_runtime.h>
# include <hcr/hcrtc.h>
# include <hcc/hcc_internal.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include <hcsparse/hcsparse.h>
# include <hcrand/hcrand.h>
# include <hcfft/hcfft.h>
# include <luca_fp8.h>
# include <luca_fp16.h>
# include <luca_cooperative_groups.h>
# include <hccl.h>
# include "cuda_adapter.h"
# define CUNAME	"CESTC"
#elif defined(__USE_HIP__)
# ifdef __USE_HIP_V2__
#  define HIPBLAS_V2
# endif
/**
 * Must define exactly one of __HIP_PLATFORM_AMD__ or __HIP_PLATFORM_NVIDIA__
 */
# define __HIP_PLATFORM_AMD__
# include <hip/hip_runtime.h>
# include <hip/hip_runtime_api.h>
# include <hip/hiprtc.h>
# include <hipfft/hipfft.h>
# include <hipsparse/hipsparse.h>
# include <hiprand/hiprand.h>
# include <hip/hip_cooperative_groups.h>
# define HIPBLAS_USE_HIP_HALF
# include <hipblas/hipblas.h>
# include <hipblaslt/hipblaslt.h>
# include <hip/hip_fp8.h>
# include <hip/hip_fp16.h>
# ifdef HAVE_RCCL
#  include <rccl/rccl.h>
# endif
# include "cuda_adapter.h"
# ifndef HAVE_HIP
#  error "Not found ROCm HIP envrioment, but use HIP"
# endif
# define CUNAME	"ROCm HIP"
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
# if CUDA_VERSION >= 12000
#  include <cuda_fp6.h>
# endif
# include <cuda_fp8.h>
# include <cuda_fp16.h>
# include <cuda_bf16.h>
# define DISABLE_CUSPARSE_DEPRECATED	1
# include <cusparse.h>
# include <cooperative_groups.h>
# ifdef HAVE_NCCL
#  include <nccl.h>
# endif
# define CUNAME	"NVIDIA CUDA"
#endif

#endif
