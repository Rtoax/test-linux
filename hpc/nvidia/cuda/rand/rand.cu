// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao. All rights reserved. */
#include <stdio.h>
#include <curand.h>
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int version;
	CURAND_CHECK(curandGetVersion(&version), exit(1));
	printf("curand version %d\n", version);
	return 0;
}
