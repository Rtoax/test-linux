// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "utils.hpp"


extern bool fakecuda_debug;


void memdump(const void *mem, size_t size)
{
	const int width = 8;
	int nr_newline = 0;
	int nr_startline = 0;

	for (size_t i = 0; i < size; i++) {
		bool startline = i % width == 0;
		bool newline = (i + 1) % width == 0;

		if (startline) {
			printf("%#016x | ", (uint64_t)mem + width * nr_newline);
		}

		uint8_t u8 = *(uint8_t *)((uint8_t *)mem + i);
		printf("%02x%s", u8, newline ? " |" : " ");

		/**
		 * Display memory as character
		 */
		if (newline) {
			const void *memch = (uint8_t *)mem + width * nr_newline;
			for (size_t j = 0; j < width; j++) {
				uint8_t c8 = *(uint8_t *)((uint8_t *)memch + j);
				printf("%c", isprint(c8) ? c8 : '.');
			}
			printf("|\n");
		}

		if (newline)
			nr_newline++;
		if (startline)
			nr_startline++;
	}

	if (nr_newline != nr_startline)
		printf("\n");
}

void debug_memdump(const void *mem, size_t size)
{
	if (!fakecuda_debug)
		return;
	memdump(mem, size);
}
