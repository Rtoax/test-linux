// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcrand/hcrand.h>
#include <cuda_adapter.h>
#else
#include <cuda.h>
#include <curand.h>
#include <cuda_runtime.h>
#endif


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
