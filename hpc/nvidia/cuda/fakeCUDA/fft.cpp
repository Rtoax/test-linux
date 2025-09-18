// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcfft/hcfft.h>
#include <cuda_adapter.h>
#else
#include <cufft.h>
#endif
#include "debug.h"


#ifdef __cplusplus
extern "C" {
#endif
cufftResult cufftGetProperty(libraryPropertyType type, int *value)
{
	LOG_DEBUG("type %d\n", type);

	switch (type) {
	case MAJOR_VERSION:
		*value = 12;
		break;
	case MINOR_VERSION:
		*value = 1;
		break;
	case PATCH_LEVEL:
		*value = 1;
		break;
	default:
		return CUFFT_INVALID_TYPE;
	}
	return CUFFT_SUCCESS;
}
#ifdef __cplusplus
}
#endif
