// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once

#if defined(__USE_HPCC__)
typedef void *cudaKernel_t;
#endif

#ifndef __cplusplus
/* TODO: _Float32 may not supported */
typedef _Float32 __half;
#endif
