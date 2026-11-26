// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <assert.h>
#include <errno.h>
#include <float.h>
#include <malloc.h>
#include <math.h>
#include <ncurses.h>
#include <string.h>
#include "line.h"
#include "legend.h"

static char **legends = NULL;
static int nr_legends = 0;
static int idx_legends = -1;

/**
 * Since this program is single-thread, we could set line name with a global
 * list.
 */
int enqueue_legend(const char *name)
{
	if (!name)
		return -EINVAL;

	for (int i = 0; i < nr_legends; i++) {
		if (!strcmp(name, legends[i])) {
			fprintf(stderr,
				"ERROR: line label '%s' already exist.\n",
				name);
			return -EEXIST;
		}
	}

	nr_legends++;
	legends = (char **)realloc(legends, nr_legends * sizeof(char *));

	/* FIXME: memleak here */
	legends[nr_legends - 1] = strdup(name);
	return 0;
}

const char *dequeue_legend(void)
{
	if (nr_legends <= 0 || idx_legends >= nr_legends)
		return NULL;
	return legends[++idx_legends];
}
