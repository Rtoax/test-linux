// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <errno.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	void *mem;

	for (;;) {
		mem = malloc(getpagesize());
		if (!mem && errno == ENOMEM) {
			fprintf(stderr, "OOMing...\n");
		}
		*(int *)mem = 1;
		/* Just leak the memory */
	}
	return 0;
}
