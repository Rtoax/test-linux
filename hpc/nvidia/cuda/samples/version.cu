// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

int main(void)
{
	int driverVersion = 0;
	cudaDriverGetVersion(&driverVersion);
	printf("Driver version is: %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10);
	return 0;
}
