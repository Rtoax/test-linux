// SPDX-License-Identifier: GPL-3.0
/**
 * RTC - RunTime Compile
 *
 * Copyright (C) 2026 Rong Tao
 */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

char prog_buffer[] = { " \
	__global__ void kernelHello(void) { \
		printf(\"Hello from GPU.\n\"); \
	}" };

const char *compile_opts[] = { "-x luca" };

int main(void)
{
	nvrtcProgram prog;

	NVRTC_CHECK_EXIT(
		nvrtcCreateProgram(&prog, prog_buffer, "hello", 0, NULL, NULL));
	NVRTC_CHECK_EXIT(nvrtcCompileProgram(prog, ARRAY_SIZE(compile_opts),
					     compile_opts));

#ifdef __LUCA__
	size_t codeSize;
	nvrtcGetCodeSize(prog, &codeSize);
#endif

	return 0;
}
