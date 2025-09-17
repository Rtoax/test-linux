// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <cuda.h>
#include <curand.h>
#include <cuda_runtime.h>


#ifdef __cplusplus
extern "C" {
#endif
curandStatus_t curandGetVersion(int *version)
{
	*version = 10;
	return CURAND_STATUS_SUCCESS;
}
#ifdef __cplusplus
}
#endif
