// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * Input definitions:
 * - __USE_HPCC__
 * - __USE_HIP__
 * - __USE_HIP_V2__: use V2 API, default: disable
 * - __USE_LUCA__
 * - LUCA_PHASE_II_PROJECT:
 *
 * - HAVE_NCCL
 * - HAVE_NVRTC
 * - HAVE_RCCL
 * - HAVE_HPCC
 * - HAVE_CUPTI
 * - HAVE_LCPTI
 * - HAVE_LSVPU
 * - HAVE_HIP
 */
#ifndef __CUDA_COMPAT_H
#define __CUDA_COMPAT_H	1

#define CUDA_COMPAT_MAJOR 1
#define CUDA_COMPAT_MINOR 0
#define CUDA_COMPAT_PATCH 0

/******************************************************************************\
 * HPCC: High Performance Computing Communications                            *
\******************************************************************************/
#ifdef __USE_HPCC__
# include <hcr/hc_runtime.h>
# include <hcr/hcrtc.h>
# include <hcc/hcc_internal.h>
/* TODO: add rtc */
# ifdef __HPCC__
#  include <hpcc_cooperative_groups.h>
# endif
# include <hccl.h>
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
#  include <lccl.h>
#  ifdef HAVE_LSVPU
#   include <lcr/lc_vpu_api.h>
#  endif
# else /* LUCA_PHASE_II_PROJECT */
#  include <hcr/hc_runtime.h>
#  include <hcr/hcrtc.h>
#  include <hcc/hcc_internal.h>
#  include <hccl.h>
#  ifdef HAVE_LSVPU
#   include <hcr/hc_vpu_api.h>
#  endif
# endif /* LUCA_PHASE_II_PROJECT */
# ifdef __LUCA__
#  include <luca_cooperative_groups.h>
# endif
# include "cuda_adapter.h"
# define CUNAME	"LUCA"
/******************************************************************************\
 * AMD ROCm HIP                                                               *
\******************************************************************************/
#elif defined(__USE_HIP__)
/**
 * Must define exactly one of __HIP_PLATFORM_AMD__ or __HIP_PLATFORM_NVIDIA__
 */
# define __HIP_PLATFORM_AMD__
# include <hip/hip_version.h>
# include <hip/hip_runtime.h>
# include <hip/hip_runtime_api.h>
# include <hip/hiprtc.h>
# include <hip/hip_cooperative_groups.h>
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
# ifdef HAVE_NVRTC
#  include <nvrtc.h>
# endif
# include <cuda.h>
# include <cuda_runtime.h>
# include <cuda_runtime_api.h>
# include <cusolver_common.h>
# if CUDA_VERSION > 12040
#  include <cuda_fp6.h>
# endif
# include <cuda_bf16.h>
# define DISABLE_CUSPARSE_DEPRECATED	1
# include <cusparse.h>
# include <cooperative_groups.h>
# ifdef HAVE_NCCL
#  include <nccl.h>
# endif
# ifdef HAVE_CUPTI
#  include <cupti.h>
#  include <cupti_profiler_target.h>
#  include <cupti_target.h>
#  if CUDA_VERSION > 12040
#   include <cupti_pmsampling.h>
#   include <cupti_profiler_host.h>
#   include <cupti_range_profiler.h>
#  endif
# endif
# define CUNAME	"NVIDIA CUDA"
#endif

#endif
