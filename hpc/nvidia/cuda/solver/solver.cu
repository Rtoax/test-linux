// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int version = 0;

#ifdef __HIPCC__
	version = hipsolverVersionMajor;
#else
	cusolverGetVersion(&version);
#endif
	printf("Solver version %d\n", version);

	return 0;
}
