// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUCOMPLEX_H
#define __CUDA_ADAPTER_CUCOMPLEX_H 1

#include "wrapper_defs.h"

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */

/**
 * CUDA: typedef cuFloatComplex cuComplex;
 */
#define cuComplex __cu(Complex)
/**
 * CUDA: typedef double2 cuDoubleComplex;
 */
#define cuDoubleComplex __cu(DoubleComplex)

#endif
