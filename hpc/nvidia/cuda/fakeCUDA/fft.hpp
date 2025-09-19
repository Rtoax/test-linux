// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "compat.hpp"


#ifdef __cplusplus
extern "C" {
#endif

cufftResult cufftGetProperty(libraryPropertyType type, int *value);

#ifdef __cplusplus
}
#endif
