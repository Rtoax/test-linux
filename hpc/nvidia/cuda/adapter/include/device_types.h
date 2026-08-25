// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#ifndef __CUDA_ADAPTER_DEVICE_TYPES_H
#define __CUDA_ADAPTER_DEVICE_TYPES_H 1

#include "wrapper_defs.h"

/* enum cudaRoundMode */
#define cudaRoundMode cudaX(RoundMode)
#define cudaRoundNearest cudaX(RoundNearest)
#define cudaRoundZero cudaX(RoundZero)
#define cudaRoundPosInf cudaX(RoundPosInf)
#define cudaRoundMinInf cudaX(RoundMinInf)

#endif
