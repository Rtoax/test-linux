// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
#if defined(__HPCC__) || defined(__LUCA__)
	printf("hcDNN version %d.%d.%d\n", HCDNN_MAJOR, HCDNN_MINOR, HCDNN_PATCHLEVEL);
#endif
	printf("cuDNN version %d.%d.%d\n", CUDNN_MAJOR, CUDNN_MINOR, CUDNN_PATCHLEVEL);
	return 0;
}
