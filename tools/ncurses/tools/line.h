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

/* PLOT_TYPE_LINE */
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

	/**
	 * The scaling factor for the drawing. The default value is 1, which
	 * means no scaling. It only supports zoomed-out display, similar to
	 * viewing "Global Routes" in map software.
	 */
	int ln_x_scale;
	/**
	 * As the amount of data increases, we may need to view historical data.
	 * @x_shift_left records the number of points moved to the left, and
	 * this number of points will be scaled by @ln_x_scale.
	 */
	unsigned long x_shift_left;
	int x_shift_left_timerfd;

#ifdef DEBUG
#define __LINE_DBG0_X_FMT ", %s:%d"
#define __LINE_DBG0_X_ARG(p) , ln_x_type_str(p->__line.x_type), p->__line.x_type
#else
#define __LINE_DBG0_X_FMT
#define __LINE_DBG0_X_ARG(p)
#endif
#define __LINE_INF0_FMT "line(scale %d, shft %ld/%ld" __LINE_DBG0_X_FMT ")"
#define __LINE_INF0_ARG(p)                            \
	p->__line.ln_x_scale, p->__line.x_shift_left, \
		plot_ln_shift(p) __LINE_DBG0_X_ARG(p)
};

#define for_each_value(l, iter)                                        \
	for (struct ln_value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

#define for_each_lgroup(lplt, iter)                                          \
	for (struct lgroup *iter = ((struct line_plotting *)(lplt))->lghead; \
	     iter; iter = iter->next)

struct lgroup *plot_lgroup(const struct line_plotting *p, int idx);

void line_add_value(struct line *l, double v, long limit, struct ln_x_value *x);
double line_range_avg(struct line *l, int start, int len);
double line_range_max(struct line *l, int start, int interval, int len);
double line_range_min(struct line *l, int start, int interval, int len);
double line_range_delta_max(struct line *l, int start, int interval, int len);
double line_range_delta_min(struct line *l, int start, int interval, int len);

struct line *new_line(struct lgroup *lg, const char *name, int color);
struct line *new_line_ops(struct lgroup *lg, const char *name, int color,
			  const struct draw_operations *ops);
void free_line(struct line *ln);

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

void __paint_debug_ln_label(const struct lgroup *lg, int y, int x);
int plot_create_lines(struct line_plotting *p);
