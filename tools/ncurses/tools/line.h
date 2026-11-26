// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"
#include "value.h"
#include "lgroup.h"
#include "axis.h"
#include "draw.h"

struct plot;
struct draw_operations;

struct line {
	char name[64];
	/* The line ID is unique only within the lgroup. */
	int id;
	int color; /* C_RED, ... */
	struct ln_value *head, *tail, *max, *min;
	long count; /* number of value */
	struct line *next; /* maybe line in group */
	struct lgroup *lg; /* belongs to */
	const struct draw_operations *ops;
	struct ln_x_range x_range;
};

struct line_plotting {
	struct lgroup *lghead, *lgtail;
	int lgcount;

	/**
	 * A stacked line chart shows how multiple series
	 * cumulatively add up to a total over time, emphasizing
	 * the overall trend and composition rather than each
	 * series’ absolute values.
	 *
	 *  Origin Line Chart           Stacked Line Chart
	 * ^                           ^
	 * |                           |           +-- line2
	 * |                           |           |
	 * |                           |  +--------+
	 * |                           |  |
	 * |           +-- line2       |  |
	 * |           |               |  |
	 * |  +--------+               |--+
	 * |  |                        |
	 * |--+----------- line1       |--------------- line1
	 * |  |                        |
	 * |--+                        |
	 * +--------------> 0          +---------------> 0
	 *
	 * Not support curve type MATH_TRANS_DELTA.
	 */
	bool enable_stacked_line_chart;

	enum ln_x_type x_type;
};

#define for_each_value(l, iter)                                        \
	for (struct ln_value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

#define for_each_lgroup(lplt, iter)                                          \
	for (struct lgroup *iter = ((struct line_plotting *)(lplt))->lghead; \
	     iter; iter = iter->next)

struct lgroup *plot_lgroup(const struct line_plotting *p, int idx);

int enqueue_llabel(const char *name);
const char *dequeue_llabel(void);

void line_add_value(struct line *l, double v, long limit, struct ln_x_value *x);
double line_range_avg(struct line *l, int start, int len);
double line_range_max(struct line *l, int start, int interval, int len);
double line_range_min(struct line *l, int start, int interval, int len);
double line_range_delta_max(struct line *l, int start, int interval, int len);
double line_range_delta_min(struct line *l, int start, int interval, int len);

struct line *new_line(struct lgroup *lg, const char *name, int color);
struct line *new_line_ops(struct lgroup *lg, const char *name, int color,
			  const struct draw_operations *ops);

static inline void set_line_name(struct line *ln, const char *name)
{
	/* already set name */
	if (ln->name[0] != '\0')
		return;
	snprintf(ln->name, sizeof(ln->name) - 1, "%s", name);
}

int paint_y0_line(const struct plot *p, double min, double max);

void __paint_line(struct plot *p, const struct lgroup *lg,
		  const struct line *ln, int start, int len, int shift,
		  double max, double min, double *stacked_line,
		  bool first_line);
