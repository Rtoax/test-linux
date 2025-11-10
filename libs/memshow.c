// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "memshow.h"

#define LINE_LEN 128

/**
 * like $ hexdump --canonical $FILE
 */
void hexdump(const void *mem, size_t size)
{
	const int width = 16;
	int nr_newline = 0;
	int nr_startline = 0;
	size_t align_size = 0;

	assert(!(width % 8) && "width must align of 8");

	while (align_size < size)
		align_size += width;

	for (size_t i = 0; i < size; i++) {
		bool startline = i % width == 0;
		bool newline = (i + 1) % width == 0;

		if (startline) {
			printf("%#016lx | ", (uint64_t)mem + width * nr_newline);
		}

		uint8_t u8 = *(uint8_t *)((uint8_t *)mem + i);
		printf("%02x%s", u8, newline ? " |" : " ");

		if ((i + 1) % 8 == 0 && !newline)
			printf(" ");

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

	if (align_size > size) {
		for (size_t i = 0; i < align_size - size; i++)
			printf("   ");
		printf("|");

		const void *memlastrow = (uint8_t *)mem + width * nr_newline;
		for (size_t i = 0; i < width - (align_size - size); i++) {
			uint8_t c8 = *(uint8_t *)((uint8_t *)memlastrow + i);
			printf("%c", isprint(c8) ? c8 : '.');
		}
		for (size_t i = 0; i < align_size - size; i++)
			printf(" ");
		printf("|");
	}

	if (nr_newline != nr_startline)
		printf("\n");
}

void memdump(FILE *f, const char *title, const void *buf, unsigned int len)
{
	unsigned int i, out;
	const unsigned char *data = (const unsigned char *)buf;
	char line[LINE_LEN];

	if (title)
		fprintf(f, "%s: ", title);

	line[0] = '\0';
	for (i = 0, out = 0; i < len; i++) {
		/* Make sure we do not overrun the line buffer length. */
		if (out >= LINE_LEN - 4) {
			fprintf(f, "%s", line);
			out = 0;
			line[out] = '\0';
		}
		out += snprintf(line + out, LINE_LEN - out, "%02x%s",
				(data[i] & 0xff), ((i + 1) < len) ? ":" : "");
	}
	if (out > 0)
		fprintf(f, "%s", line);
	fprintf(f, "\n");

	fflush(f);
}

#ifdef TEST
int main(void)
{
	char str[] = {
		"1234567890abcdefghijklmnopqrstuvwxyz:;,."
	};

	memshow(">>  ", str, sizeof(str));
	memshow(">>>>", str, sizeof(str));

	hexdump(str, sizeof(str));
	memdump(stdout, "memdump", str, sizeof(str));
}
#endif
