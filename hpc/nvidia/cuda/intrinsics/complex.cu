// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <cuda_runtime.h>
#include <cuComplex.h>
#include "compiler.h"
#include "print.h"
#include "types.h"

__global__ void k_cuFloatComplex_types(void)
{
}

int main(int argc, char *argv[])
{
	assert(sizeof(cuFloatComplex) == 8 && "bad size of cuFloatComplex");

	cuFloatComplex fc = make_cuFloatComplex(3.14, 3.14);

	k_cuFloatComplex_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
