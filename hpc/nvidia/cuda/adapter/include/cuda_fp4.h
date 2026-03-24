// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP4_H
#define __CUDA_ADAPTER_FP4_H 1

#ifdef __CUDA_FP4_H__
#error "CudaAdapter not allow include origin CUDA cuda_fp4.h"
#endif

#include "wrapper_defs.h"

#include "device_types.h"
#include "cuda_fp6.h"

/* typedef __nv_fp8_storage_t __nv_fp4_storage_t; */
#define __nv_fp4_storage_t __nv_X(fp4_storage_t)
/* typedef __nv_fp8_storage_t __nv_fp4x2_storage_t; */
#define __nv_fp4x2_storage_t __nv_X(fp4x2_storage_t)
/* typedef __nv_fp8x2_storage_t __nv_fp4x4_storage_t; */
#define __nv_fp4x4_storage_t __nv_X(fp4x4_storage_t)

#define __nv_fp4_interpretation_t __nv_X(fp4_interpretation_t) /* enum */
#define __NV_E2M1 __NV_X(E2M1)

/**
 * __nv_fp4_storage_t
 * __nv_cvt_double_to_fp4(const double x,
 *                        const __nv_fp4_interpretation_t fp4_interpretation,
 *                        const enum cudaRoundMode rounding);
 */
#define __nv_cvt_double_to_fp4 __nv_X(cvt_double_to_fp4)

/**
 * __nv_fp4x2_storage_t
 * __nv_cvt_double2_to_fp4x2(const double2 x,
 *                           const __nv_fp4_interpretation_t fp4_interpretation,
 *                           const enum cudaRoundMode rounding);
 */
#define __nv_cvt_double2_to_fp4x2 __nv_X(cvt_double2_to_fp4x2)

/**
 * __nv_fp4_storage_t
 * __nv_cvt_float_to_fp4(const float x,
 *                       const __nv_fp4_interpretation_t fp4_interpretation,
 *                       const enum cudaRoundMode rounding);
 */
#define __nv_cvt_float_to_fp4 __nv_X(cvt_float_to_fp4)

/**
 * __nv_fp4x2_storage_t
 * __nv_cvt_float2_to_fp4x2(const float2 x,
 *                          const __nv_fp4_interpretation_t fp4_interpretation,
 *                          const enum cudaRoundMode rounding);
 */
#define __nv_cvt_float2_to_fp4x2 __nv_X(cvt_float2_to_fp4x2)

/**
 * __nv_fp4_storage_t
 * __nv_cvt_halfraw_to_fp4(const __half_raw x,
 *                         const __nv_fp4_interpretation_t fp4_interpretation,
 *                         const enum cudaRoundMode rounding);
 */
#define __nv_cvt_halfraw_to_fp4 __nv_X(cvt_halfraw_to_fp4)

/**
 * __nv_fp4x2_storage_t
 * __nv_cvt_halfraw2_to_fp4x2(const __half2_raw x,
 *                            const __nv_fp4_interpretation_t fp4_interpretation,
 *                            const enum cudaRoundMode rounding);
 */
#define __nv_cvt_halfraw2_to_fp4x2 __nv_X(cvt_halfraw2_to_fp4x2)

/**
 * __nv_fp4_storage_t
 * __nv_cvt_bfloat16raw_to_fp4(const __nv_bfloat16_raw x,
 *                             const __nv_fp4_interpretation_t fp4_interpretation,
 *                             const enum cudaRoundMode rounding);
 */
#define __nv_cvt_bfloat16raw_to_fp4 __nv_X(cvt_bfloat16raw_to_fp4)

/**
 * __nv_fp4x2_storage_t
 * __nv_cvt_bfloat16raw2_to_fp4x2(const __nv_bfloat162_raw x,
 *                                const __nv_fp4_interpretation_t fp4_interpretation,
 *                                const enum cudaRoundMode rounding);
 */
#define __nv_cvt_bfloat16raw2_to_fp4x2 __nv_X(cvt_bfloat16raw2_to_fp4x2)

/**
 * __half_raw
 * __nv_cvt_fp4_to_halfraw(const __nv_fp4_storage_t x,
 *                         const __nv_fp4_interpretation_t fp4_interpretation);
 */
#define __nv_cvt_fp4_to_halfraw __nv_X(cvt_fp4_to_halfraw)

/**
 * __half2_raw
 * __nv_cvt_fp4x2_to_halfraw2(const __nv_fp4x2_storage_t x,
 *                            const __nv_fp4_interpretation_t fp4_interpretation);
 */
#define __nv_cvt_fp4x2_to_halfraw2 __nv_X(cvt_fp4x2_to_halfraw2)

#if defined(__cplusplus)
#define __nv_fp4_e2m1 __nv_X(fp4_e2m1)
#define __nv_fp4x2_e2m1 __nv_X(fp4x2_e2m1)
#define __nv_fp4x4_e2m1 __nv_X(fp4x4_e2m1)
#endif

#ifdef __USE_HPCC__
#elif defined(__USE_LUCA__)
#elif defined(__USE_HIP__)
#endif

#endif
