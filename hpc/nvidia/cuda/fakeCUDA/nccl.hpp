// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "cuda_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

ncclResult_t ncclGetVersion(int *version);
const char* ncclGetErrorString(ncclResult_t result);
ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId);

#ifdef __cplusplus
}
#endif
