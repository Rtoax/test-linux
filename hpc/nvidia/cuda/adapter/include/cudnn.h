// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             DNN                                                            *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_DNN_H
#define __CUDA_ADAPTER_DNN_H 1

#ifdef CUDNN_H_
#error "CudaAdapter not allow include origin CUDA cudnn.h"
#endif

#include "wrapper_defs.h"

#ifdef __USE_HPCC__
# include <hcdnn/hcdnn.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcdnn/lcdnn.h>
# else
#  include <hcdnn/hcdnn.h>
# endif
#elif defined(__USE_HIP__)
#endif

#endif
