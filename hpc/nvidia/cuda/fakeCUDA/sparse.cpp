// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "sparse.hpp"
#include "debug.h"


cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value)
{
	DEBUG_DBG("type %d\n", type);

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
