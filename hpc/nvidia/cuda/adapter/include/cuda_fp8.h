// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP8_H
#define __CUDA_ADAPTER_FP8_H 1

#ifdef __CUDA_FP8_H__
#error "CudaAdapter not allow include origin CUDA cuda_fp8.h"
#endif

#include "wrapper_defs.h"

/**
 * fp8
 *   typedef unsigned char __nv_fp8_storage_t;
 *
 *   typedef unsigned short int __nv_fp8x2_storage_t;
 *   typedef __nv_fp8x2_storage_t __nv_fp4x4_storage_t;
 *
 *   typedef unsigned int __nv_fp8x4_storage_t;
 */
#define __nv_fp8_storage_t __nv_X(fp8_storage_t)
#define __nv_fp8x2_storage_t __nv_X(fp8x2_storage_t)
#define __nv_fp8x4_storage_t __nv_X(fp8x4_storage_t)

#define __nv_fp8_interpretation_t __nv_X(fp8_interpretation_t)
#define __NV_E4M3 __NV_X(E4M3)
#define __NV_E5M2 __NV_X(E5M2)

#define __nv_saturation_t __nv_X(saturation_t)
#define __NV_NOSAT __NV_X(NOSAT)
#define __NV_SATFINITE __NV_X(SATFINITE)

#define __nv_cvt_halfraw_to_fp8 __nv_X(cvt_halfraw_to_fp8)
#define __nv_cvt_halfraw2_to_fp8x2 __nv_X(cvt_halfraw2_to_fp8x2)

#define __nv_fp8_e4m3 __nv_X(fp8_e4m3)
#define __nv_fp8_e5m2 __nv_X(fp8_e5m2)
#define __nv_fp8_e8m0 __nv_X(fp8_e8m0)
#define __nv_fp8x2_e4m3 __nv_X(fp8x2_e4m3)
#define __nv_fp8x2_e5m2 __nv_X(fp8x2_e5m2)
#define __nv_fp8x2_e8m0 __nv_X(fp8x2_e8m0)
#define __nv_fp8x4_e4m3 __nv_X(fp8x4_e4m3)
#define __nv_fp8x4_e5m2 __nv_X(fp8x4_e5m2)
#define __nv_fp8x4_e8m0 __nv_X(fp8x4_e8m0)

#define __nv_cvt_double2_to_e8m0x2 __nv_X(cvt_double2_to_e8m0x2)
#define __nv_cvt_double2_to_fp8x2 __nv_X(cvt_double2_to_fp8x2)
#define __nv_cvt_double_to_e8m0 __nv_X(cvt_double_to_e8m0)
#define __nv_cvt_double_to_fp8 __nv_X(cvt_double_to_fp8)

#define __nv_cvt_float2_to_e8m0x2 __nv_X(cvt_float2_to_e8m0x2)
#define __nv_cvt_float2_to_fp8x2 __nv_X(cvt_float2_to_fp8x2)

#define __nv_cvt_float_to_e8m0 __nv_X(cvt_float_to_e8m0)
#define __nv_cvt_float_to_fp8 __nv_X(cvt_float_to_fp8)

#define __nv_cvt_fp8_to_halfraw __nv_X(cvt_fp8_to_halfraw)
#define __nv_cvt_fp8x2_to_halfraw2 __nv_X(cvt_fp8x2_to_halfraw2)

#ifdef __USE_HPCC__
# include <hpcc_fp8.h>
#elif defined(__USE_LUCA__)
# include <luca_fp8.h>
#elif defined(__USE_HIP__)
# include <hip/hip_fp8.h>
#endif

#endif
