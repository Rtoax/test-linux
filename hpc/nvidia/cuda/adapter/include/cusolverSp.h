// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_SOLVERSP_COMMON_H
#define __CUDA_ADAPTER_SOLVERSP_COMMON_H 1

#ifdef CUSOLVERSP_H_
#error "CudaAdapter not allow include origin CUDA cusolverSp.h"
#endif

#include "wrapper_defs.h"
#include "cusolver_common.h"

#define cusolverSpContext cuX(solverSpContext)
#define cusolverSpHandle_t cuX(solverSpHandle_t)

/**
 * cusolverStatus_t cusolverSpCreate(cusolverSpHandle_t *handle);
 * lcsolverStatus_t lcsolverSpCreate(lcsolverSpHandle_t *handle);
 */
#define cusolverSpCreate cuX(solverSpCreate)
#define cusolverSpDestroy cuX(solverSpDestroy)

/**
 * cusolverStatus_t cusolverSpSetStream(cusolverSpHandle_t handle,
 *                                      cudaStream_t streamId);
 */
#define cusolverSpSetStream cuX(solverSpSetStream)
#define cusolverSpGetStream cuX(solverSpGetStream)

#ifdef __USE_HPCC__
# include <hcsolver/hcsolverSp.h>
#elif defined(__USE_LUCA__)
# include <lcsolver/lcsolverSp.h>
#elif defined(__USE_HIP__)
// TODO
#endif

#endif
