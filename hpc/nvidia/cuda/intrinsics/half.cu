// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cuda_compat.h"


__global__ void kmul(void)
{
	half h1, h2, h3;
	float f1;

	h1 = __float2half(3.14);
	h2 = __float2half(3.14);

	h3 = __hmul(h1, h2);
	f1 = __half2float(h3);

	printf("%f\n", f1);
}

int main(int argc, char *argv[])
{
	kmul<<<1, 1>>>();
	(void)cudaDeviceSynchronize();
	return 0;
}
