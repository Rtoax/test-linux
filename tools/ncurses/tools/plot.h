// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include "config.h"
#include "value.h"

struct plot {
	char *title;
	char *label_x;
	char *label_y;
	struct {
		int top, bottom, left, right;
	} bnd, prev_max;
	int height, width;
	int plotheight, plotwidth;
	int prev_sec, interval_sec;
	struct lgroup *lghead, *lgtail;
	int lgcount;
};

#define for_each_lg(plt, iter)                                           \
	for (struct lgroup *iter = ((struct plot *)(plt))->lghead; iter; \
	     iter = iter->next)

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg);

void plot_update_size(struct plot *p, bool init);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);

void paint_plot(struct plot *p);
void plot_update_data(struct plot *p);
void redraw_screen(struct plot *p);

void init_flavor(void);
