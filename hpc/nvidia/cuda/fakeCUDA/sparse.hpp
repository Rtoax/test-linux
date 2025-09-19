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


#ifdef __cplusplus
extern "C" {
#endif

cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value);

#ifdef __cplusplus
}
#endif
