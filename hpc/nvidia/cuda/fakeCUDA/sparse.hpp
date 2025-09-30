// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "cuda_compat.h"


#ifdef __cplusplus
extern "C" {
#endif

cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value);

#ifdef __cplusplus
}
#endif
