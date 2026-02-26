// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP4_H
#define __CUDA_ADAPTER_FP4_H 1

#ifdef __CUDA_FP4_H__
#error "CudaAdapter not allow include origin CUDA cuda_fp4.h"
#endif

#include "wrapper_defs.h"

#include "cuda_fp6.h"

/* typedef __nv_fp8_storage_t __nv_fp4_storage_t; */
#define __nv_fp4_storage_t __nv_X(fp4_storage_t)
/* typedef __nv_fp8_storage_t __nv_fp4x2_storage_t; */
#define __nv_fp4x2_storage_t __nv_X(fp4x2_storage_t)
/* typedef __nv_fp8x2_storage_t __nv_fp4x4_storage_t; */
#define __nv_fp4x4_storage_t __nv_X(fp4x4_storage_t)

#define __nv_fp4_interpretation_t __nv_X(fp4_interpretation_t) /* enum */
#define __NV_E2M1 __NV_X(E2M1)

#ifdef __USE_HPCC__
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
# else
# endif
#elif defined(__USE_HIP__)
#endif

#endif
