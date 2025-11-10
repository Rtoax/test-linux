#pragma once

#include <stdio.h>
#include <ctype.h>

static void __attribute__((unused))
memshow(const char *prefix, void *ptr, ssize_t size)
{
	unsigned char *byte = (unsigned char *)ptr;
	unsigned char *line_hdr = NULL;
	int i, j, cnt = 0;

	for (i = 0; i < size; i++) {
		if (cnt % 16 == 0) {
			printf("%s0x%04x:  ", prefix, cnt);
			line_hdr = byte;
		}

		printf("%02x", *byte);

		if(cnt % 2)
			printf(" ");
		byte++;

		cnt++;
		if (cnt % 16 == 0) {
			printf(" | ");
			for (j = 0; j < 16; j++) {
				if (i + j < size) {
					printf("%c", isascii(*line_hdr) ? *line_hdr : '.');
					line_hdr++;
				}
			}
			printf("\n");
			fflush(stdout);
		}
	}
	printf("\n");
	fflush(stdout);
}

void memdump(FILE *f, const char *title, const void *buf, unsigned int len);
void fhexdump(FILE *fp, const void *mem, size_t size);
void hexdump(const void *mem, size_t size);
