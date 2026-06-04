// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <errno.h>
#include <stdio.h>
#include "file.h"
#include "plot.h"

#define FILE_DATA "plotcake.dat"

/**
 * only have one plot
 */
int save_plot(struct plot *p)
{
	int lg_idx;
	char *path = FILE_DATA;
	FILE *fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", path);
		return -errno;
	}

	fprintf(fp, "#    lgroup count\n");
	fprintf(fp, "plot %d\n", p->lgcount);

	lg_idx = 0;
	for_each_lg(p, lg)
	{
		int ln_idx = 0;

		fprintf(fp, "#      idx nline\n");
		fprintf(fp, "lgroup %d %d\n", lg_idx, lg->count);

		for_each_line(lg, ln)
		{
			fprintf(fp, "#    lgidx lnidx nvals\n");
			fprintf(fp, "line %d %d %d\n", lg_idx, ln_idx,
				ln->count);

			// For each value

			ln_idx++;
		}

		lg_idx++;
	}

	fclose(fp);
	return 0;
}
