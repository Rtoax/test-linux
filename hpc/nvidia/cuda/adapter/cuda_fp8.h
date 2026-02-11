// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP8_H
#define __CUDA_ADAPTER_FP8_H 1

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
#define __nv_fp8_storage_t ____nv_(fp8_storage_t)
#define __nv_fp8x2_storage_t ____nv_(fp8x2_storage_t)
#define __nv_fp8x4_storage_t ____nv_(fp8x4_storage_t)

#define __nv_fp8_interpretation_t ____nv_(fp8_interpretation_t)
#define __NV_E4M3 ____NV_(E4M3)
#define __NV_E5M2 ____NV_(E5M2)

#define __nv_saturation_t ____nv_(saturation_t)
#define __NV_NOSAT ____NV_(NOSAT)
#define __NV_SATFINITE ____NV_(SATFINITE)

#define __nv_cvt_halfraw_to_fp8 ____nv_(cvt_halfraw_to_fp8)
#define __nv_cvt_halfraw2_to_fp8x2 ____nv_(cvt_halfraw2_to_fp8x2)

#define __nv_fp8_e4m3 ____nv_(fp8_e4m3)
#define __nv_fp8_e5m2 ____nv_(fp8_e5m2)
#define __nv_fp8_e8m0 ____nv_(fp8_e8m0)
#define __nv_fp8x2_e4m3 ____nv_(fp8x2_e4m3)
#define __nv_fp8x2_e5m2 ____nv_(fp8x2_e5m2)
#define __nv_fp8x2_e8m0 ____nv_(fp8x2_e8m0)
#define __nv_fp8x4_e4m3 ____nv_(fp8x4_e4m3)
#define __nv_fp8x4_e5m2 ____nv_(fp8x4_e5m2)
#define __nv_fp8x4_e8m0 ____nv_(fp8x4_e8m0)

#define __nv_cvt_double2_to_e8m0x2 ____nv_(cvt_double2_to_e8m0x2)
#define __nv_cvt_double2_to_fp8x2 ____nv_(cvt_double2_to_fp8x2)
#define __nv_cvt_double_to_e8m0 ____nv_(cvt_double_to_e8m0)
#define __nv_cvt_double_to_fp8 ____nv_(cvt_double_to_fp8)

#define __nv_cvt_float2_to_e8m0x2 ____nv_(cvt_float2_to_e8m0x2)
#define __nv_cvt_float2_to_fp8x2 ____nv_(cvt_float2_to_fp8x2)

#define __nv_cvt_float_to_e8m0 ____nv_(cvt_float_to_e8m0)
#define __nv_cvt_float_to_fp8 ____nv_(cvt_float_to_fp8)

#define __nv_cvt_fp8_to_halfraw ____nv_(cvt_fp8_to_halfraw)
#define __nv_cvt_fp8x2_to_halfraw2 ____nv_(cvt_fp8x2_to_halfraw2)

#endif
