// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUCOMPLEX_H
#define __CUDA_ADAPTER_CUCOMPLEX_H 1

#include "wrapper_defs.h"

#ifdef CU_COMPLEX_H_
#error "CudaAdapter not allow include origin CUDA cuComplex.h"
#endif

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */

/**
 * CUDA: typedef float2 cuFloatComplex;
 * HIP: typedef float2 hipFloatComplex;
 * LUCA: typedef float2 lcFloatComplex;
 */
#define cuFloatComplex cuX(FloatComplex)

/**
 * cuFloatComplex make_cuFloatComplex(float r, float i);
 */
#define make_cuFloatComplex XcuX(make_, FloatComplex)

/**
 * CUDA: typedef cuFloatComplex cuComplex;
 */
#define cuComplex cuX(Complex)
/**
 * CUDA: typedef double2 cuDoubleComplex;
 */
#define cuDoubleComplex cuX(DoubleComplex)

/**
 * CUDA: float cuCrealf(cuFloatComplex x);
 */
#define cuCrealf cuX(Crealf)

/**
 * CUDA: float cuCimagf(cuFloatComplex x);
 */
#define cuCimagf cuX(Cimagf)

#ifdef __USE_HPCC__
# include <hcComplex.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcComplex.h>
# else
#  include <hcComplex.h>
# endif
#elif defined(__USE_HIP__)
# include <amd_detail/amd_hip_complex.h>
#endif

#endif
