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
 * - HAVE_HPCC
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
# else /* LUCA_PHASE_II_PROJECT */
# endif /* LUCA_PHASE_II_PROJECT */
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
# include "cuda_adapter.h"
# ifndef HAVE_HIP
#  error "Not found ROCm HIP envrioment, but use HIP"
# endif
# define CUNAME	"ROCm HIP"
/******************************************************************************\
 * CUDA                                                                       *
\******************************************************************************/
#else /* fallback to CUDA */
# include <cuda.h>
# define DISABLE_CUSPARSE_DEPRECATED	1
# define CUNAME	"NVIDIA CUDA"
#endif

#endif
