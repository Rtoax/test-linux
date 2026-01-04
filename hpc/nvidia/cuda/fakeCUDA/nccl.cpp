// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "nccl.hpp"


ncclResult_t ncclGetVersion(int *version)
{
	*version = 21605;
	return ncclSuccess;
}

const char* ncclGetErrorString(ncclResult_t result)
{
	switch (result) {
#define CASE(n)	case n: return ""#n
	CASE(ncclSuccess);
	CASE(ncclUnhandledCudaError);
	CASE(ncclSystemError);
	CASE(ncclInternalError);
	CASE(ncclInvalidArgument);
	CASE(ncclInvalidUsage);
	CASE(ncclRemoteError);
	CASE(ncclInProgress);
	CASE(ncclNumResults);
	default:
		return "Unknown";
	}
#undef CASE
}

/**
 * typedef struct {
 *   char internal[128];
 * } ncclUniqueId;
 */
ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId)
{
	int i;
	srandom((int)time(0));
	for (i = 0; i < sizeof(*uniqueId); i++) {
		*(uint8_t *)&uniqueId->internal[i] = (int)(256.0 * random() / RAND_MAX + 1.0) % 256;
	}
	return ncclSuccess;
}
