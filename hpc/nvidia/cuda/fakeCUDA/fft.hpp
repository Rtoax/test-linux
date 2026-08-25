// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao. All rights reserved. */
#include <cufft.h>

#ifdef __cplusplus
extern "C" {
#endif

cufftResult cufftGetProperty(libraryPropertyType type, int *value);

#ifdef __cplusplus
}
#endif
