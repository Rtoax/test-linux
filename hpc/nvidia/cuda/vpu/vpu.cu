// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	lcVPUInst encInst;

	CUDA_RUNTIME_CHECK_EXIT(lcVpueOpen(&encInst));

	// TODO

	CUDA_RUNTIME_CHECK_EXIT(lcVpueClose(encInst));
	return 0;
}
