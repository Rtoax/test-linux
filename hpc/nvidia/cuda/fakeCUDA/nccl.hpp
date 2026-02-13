// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <nccl.h>

#ifdef __cplusplus
extern "C" {
#endif

ncclResult_t ncclGetVersion(int *version);
const char* ncclGetErrorString(ncclResult_t result);
ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId);

#ifdef __cplusplus
}
#endif
