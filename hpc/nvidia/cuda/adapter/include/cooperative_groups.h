// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER__COOPERATIVE_GROUPS_H__H
#define __CUDA_ADAPTER__COOPERATIVE_GROUPS_H__H 1

#ifdef _COOPERATIVE_GROUPS_H_
#error "CudaAdapter not allow include origin CUDA cooperative_groups.h"
#endif

#ifdef __USE_HPCC__
# include <hpcc_cooperative_groups.h>
#elif defined(__USE_LUCA__)
# include <luca_cooperative_groups.h>
#elif defined(__USE_HIP__)
# include <hip/hip_cooperative_groups.h>
#endif

#endif
