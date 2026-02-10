// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_DEVICE_TYPES_H
#define __CUDA_ADAPTER_DEVICE_TYPES_H 1

/* enum cudaRoundMode */
#define cudaRoundMode __cuda(RoundMode)
#define cudaRoundNearest __cuda(RoundNearest)
#define cudaRoundZero __cuda(RoundZero)
#define cudaRoundPosInf __cuda(RoundPosInf)
#define cudaRoundMinInf __cuda(RoundMinInf)

#endif
