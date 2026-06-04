// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <errno.h>
#include <stdio.h>
#include "file.h"
#include "plot.h"
#ifdef HAVE_JSON_C
#include <json-c/json.h>
#define FILE_JSON "plotcake.json"
#endif

#define FILE_DATA "plotcake.dat"

static int save_txt(const struct plot *p)
{
	int lg_idx, ln_idx;
	char *path = FILE_DATA;
	FILE *fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", path);
		return -errno;
	}

	fprintf(fp, "#    lgroup title\n");
	fprintf(fp, "plot %d \"%s\" \"%s\" \"%s\"\n", p->lgcount, p->title,
		p->label_x, p->label_y);

	lg_idx = ln_idx = 0;
	for_each_lg(p, lg)
	{
		fprintf(fp, "#      idx nline\n");
		fprintf(fp, "lgroup %d %d\n", lg_idx, lg->count);

		for_each_line(lg, ln)
		{
			fprintf(fp, "#    lgidx lnidx nvals\n");
			fprintf(fp, "line %d %d %d\n", lg_idx, ln_idx,
				ln->count);

			fprintf(fp, "#     lnidx value sec usec\n");
			for_each_value(ln, v)
			{
				fprintf(fp, "value %d %lf %ld %ld\n", ln_idx,
					v->v, v->tv.tv_sec, v->tv.tv_usec);
			}

			ln_idx++;
		}

		lg_idx++;
	}

	fclose(fp);
	return 0;
}

#ifdef HAVE_JSON_C
static int save_json(const struct plot *p)
{
	// TODO
	return 0;
}
#else
#define save_json(p) 0
#endif

/**
 * only have one plot
 */
int save_plot(const struct plot *p)
{
	int err = 0;
	err = err ?: save_txt(p);
	err = err ?: save_json(p);
	return err;
}
