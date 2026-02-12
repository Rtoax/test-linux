// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdio.h>
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int major, minor, patch;
	cufft_version(&major, &minor, &patch);

	printf("cuFFT version %d.%d.%d\n", major, minor, patch);

	return 0;
}
