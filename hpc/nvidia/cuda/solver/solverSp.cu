// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdio.h>
#include <cusolverSp.h>
#include "cuda_helpers.h"

int main(int argc, char *argv[])
{
	cusolverSpHandle_t handle;
	CUSOLVER_CHECK_EXIT(cusolverSpCreate(&handle));
	CUSOLVER_CHECK_EXIT(cusolverSpDestroy(handle));
	return 0;
}
