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
	struct __point *head, *tail;
	struct __value *max_x, *min_x, *max_y, *min_y;
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

struct scatter *sp_get_scatter_from_name(const struct scatter_plotting *sp,
					 const char *name);
int sp_add_scatter(struct scatter_plotting *sp, struct scatter *s);
struct scatter *new_scatter_ops(struct scatter_plotting *sp, const char *name,
				int color, const struct draw_operations *ops);
struct scatter *new_scatter(struct scatter_plotting *sp, const char *name,
			    int color);

void scatter_add_point(struct scatter *s, double x, double y);
