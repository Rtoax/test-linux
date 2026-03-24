// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * CUDA >= 13 support cuda_fp6.h
 */
#ifndef __CUDA_ADAPTER_FP6_H
#define __CUDA_ADAPTER_FP6_H 1

#ifdef __CUDA_FP6_H__
#error "CudaAdapter not allow include origin CUDA cuda_fp6.h"
#endif

#include "wrapper_defs.h"

/* bring in fp8 types infrastructure and dependencies */
#include "cuda_fp8.h"

/**
 * typedef __nv_fp8_storage_t __nv_fp6_storage_t;
 * typedef __nv_fp8x2_storage_t __nv_fp6x2_storage_t;
 * typedef __nv_fp8x4_storage_t __nv_fp6x4_storage_t;
 */
#define __nv_fp6_storage_t __nv_X(fp6_storage_t)
#define __nv_fp6x2_storage_t __nv_X(fp6x2_storage_t)
#define __nv_fp6x4_storage_t __nv_X(fp6x4_storage_t)

#define __nv_fp6_interpretation_t __nv_X(fp6_interpretation_t) /* enum */
#define __NV_E2M3 __NV_X(E2M3)
#define __NV_E3M2 __NV_X(E3M2)

/* convert */
#define __nv_cvt_double_to_fp6 __nv_X(cvt_double_to_fp6)
#define __nv_cvt_double2_to_fp6x2 __nv_X(cvt_double2_to_fp6x2)
#define __nv_cvt_float_to_fp6 __nv_X(cvt_float_to_fp6)
#define __nv_cvt_float2_to_fp6x2 __nv_X(cvt_float2_to_fp6x2)
#define __nv_cvt_halfraw_to_fp6 __nv_X(cvt_halfraw_to_fp6)
#define __nv_cvt_halfraw2_to_fp6x2 __nv_X(cvt_halfraw2_to_fp6x2)
#define __nv_cvt_bfloat16raw_to_fp6 __nv_X(cvt_bfloat16raw_to_fp6)
#define __nv_cvt_bfloat16raw2_to_fp6x2 __nv_X(cvt_bfloat16raw2_to_fp6x2)
#define __nv_cvt_fp6_to_halfraw __nv_X(cvt_fp6_to_halfraw)
#define __nv_cvt_fp6x2_to_halfraw2 __nv_X(cvt_fp6x2_to_halfraw2)

#if defined(__cplusplus)
#define __nv_fp6_e2m3 __nv_X(fp6_e2m3)
#define __nv_fp6x2_e2m3 __nv_X(fp6x2_e2m3)
#define __nv_fp6x4_e2m3 __nv_X(fp6x4_e2m3)

#define __nv_fp6_e3m2 __nv_X(fp6_e3m2)
#define __nv_fp6x2_e3m2 __nv_X(fp6x2_e3m2)
#define __nv_fp6x4_e3m2 __nv_X(fp6x4_e3m2)
#endif

#ifdef __USE_HPCC__
#elif defined(__USE_LUCA__)
#elif defined(__USE_HIP__)
#endif

#endif
