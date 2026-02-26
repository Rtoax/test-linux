// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_RUNTIME_H
#define __CUDA_ADAPTER_CUDA_RUNTIME_H 1

#include "wrapper_defs.h"
#include "cuda_runtime_api.h"

/**
 * CUDA: typedef struct CUstream_st *CUstream;
 * LUCA: typedef struct LCstream_st *lcStream_t;
 */
#define cudaStream_t cudaX(Stream_t)

#ifdef __USE_HPCC__
# include <hcr/hc_runtime.h>
# include <hcc/hcc_internal.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcr/lc_runtime.h>
#  include <lcc/lcc_internal.h>
# else
#  include <hcr/hc_runtime.h>
#  include <hcc/hcc_internal.h>
# endif
#elif defined(__USE_HIP__)
# include <hip/hip_runtime.h>
#endif

#endif
