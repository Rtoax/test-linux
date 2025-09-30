// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int major, minor, patch;

	cusparse_version(&major, &minor, &patch);
	printf("cuSPARSE version %d.%d.%d\n", major, minor, patch);

	return 0;
}
