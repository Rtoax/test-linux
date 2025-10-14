// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	int num= 1024;
	float *ptr;

	gpu_init(0);

	cudaMalloc(&ptr, sizeof(*ptr) * num);
	cudaMemset(ptr, 0, sizeof(*ptr) * num);
	cudaFree(ptr);

	return 0;
}
