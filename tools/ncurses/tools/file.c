// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <errno.h>
#include <stdio.h>
#include "file.h"
#include "plot.h"

#define FILE_DATA "plotcake.dat"

int save_plot(struct plot *p)
{
	char *path = FILE_DATA;
	FILE *fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", path);
		return -errno;
	}

	fprintf(fp, "plot %d\n", p->lgcount);

	fclose(fp);
	return 0;
}
