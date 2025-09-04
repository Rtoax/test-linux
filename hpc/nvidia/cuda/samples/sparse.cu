// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcsparse/hcsparse.h>
# include "hpcc_helpers.h"
# include "cuda_adapter.h"
# define NAME	"MetaX SPARSE"
#else
# include <cuda_runtime.h>
# include <cusparse.h>
# include "cuda_helpers.h"
# define NAME	"CUDA SPARSE"
#endif


int main(int argc, char *argv[])
{
	int major, minor, patch;

	cusparseGetProperty(MAJOR_VERSION, &major);
	cusparseGetProperty(MINOR_VERSION, &minor);
	cusparseGetProperty(PATCH_LEVEL, &patch);

	printf("cuSPARSE version %d.%d.%d\n", major, minor, patch);
	return 0;
}
