// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcsparse/hcsparse.h>
#include <cuda_adapter.h>
#else
#define DISABLE_CUSPARSE_DEPRECATED	1
#include <cusparse.h>
#endif
#include "debug.h"


#ifdef __cplusplus
extern "C" {
#endif
cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value)
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
		return CUSPARSE_STATUS_INVALID_VALUE;
	}
	return CUSPARSE_STATUS_SUCCESS;
}
#ifdef __cplusplus
}
#endif
