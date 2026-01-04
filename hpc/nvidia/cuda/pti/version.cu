// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * https://docs.nvidia.com/cupti/api/group__CUPTI__VERSION__API.html
 */
#include <stdio.h>
#include <stdint.h>
#include "cuda_compat.h"

int main(void)
{
	uint32_t version = 0;
	cuptiGetVersion(&version);
#ifndef __LUCA__
	/* FIXME: why not have it? */
	printf("CUPTI_API_VERSION = %d\n", CUPTI_API_VERSION);
#endif
	printf("cupti version %d\n", version);
	return 0;
}
