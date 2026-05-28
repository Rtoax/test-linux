// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <stdarg.h>
#include "config.h"
#include "value.h"

#ifdef NOACS
#define T_HLINE '-'
#define T_VLINE '|'
#define T_LLCR 'L'
#define T_RARR '>'
#define T_UARR '^'
#else
#define T_HLINE ACS_HLINE
#define T_VLINE ACS_VLINE
#define T_LLCR ACS_LLCORNER
#define T_RARR ACS_RARROW
#define T_UARR ACS_UARROW
#endif

struct plot {
	char *title;
	char *label_x;
	char *label_y;
	int height, width;
	int plotheight, plotwidth;
	int interval_sec;
	struct lgroup *lghead, *lgtail;
	int lgcount;
};

#define for_each_lg(plt, iter)                                           \
	for (struct lgroup *iter = ((struct plot *)(plt))->lghead; iter; \
	     iter = iter->next)

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg);

void plot_update_size(struct plot *p);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);
void plot_paint_line(const struct plot *p, struct line *load, const char *label,
		     double max, double min, chtype color);
void plot_append_val(const struct plot *p, struct line *l, double v);

void paint_plot(const struct plot *p);
void redraw_screen(const struct plot *p);

void init_flavor(void);
