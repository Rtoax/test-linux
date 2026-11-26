// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include "value.h"

struct __point {
	struct __value x, y;
	struct __point *next;
};

struct scatter {
	char name[64];
	int id;
	int color;
	struct __point *head, *tail, *max, *min;
	long count;
	struct scatter *next;
	struct scatter_plotting *sp;
	const struct draw_operations *ops;
};

/* PLOT_TYPE_SCATTER */
struct scatter_plotting {
	struct scatter *schead, *sctail;
	int sccount;
};

#define for_each_scatter(sp, iter)                                             \
	for (struct scatter *iter = ((struct scatter_plotting *)(sp))->schead; \
	     iter; iter = iter->next)
