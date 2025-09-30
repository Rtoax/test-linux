// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int version;
	CURAND_CHECK(curandGetVersion(&version), exit(1));
	printf(CUNAME " version %d\n", version);
	return 0;
}
