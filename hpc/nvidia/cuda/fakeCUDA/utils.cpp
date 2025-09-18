// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.hpp"


extern bool fakecuda_debug;


void memdump(void *mem, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		uint8_t c = *(uint8_t *)((uint8_t *)mem + i);
		printf("%02x%c", c, i % 8 == 0 ? '\n' : ' ');
	}
}

void debug_memdump(void *mem, size_t size)
{
	if (!fakecuda_debug)
		return;
	memdump(mem, size);
}
