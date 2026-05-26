// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <ncurses.h>
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
	int height, width;
	int plotheight, plotwidth;
	int interval_sec;
	struct line_group *lg;
};

extern chtype flavor[8];

void plot_update_size(struct plot *p);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);
void plot_paint_line(const struct plot *p, struct line *load, const char *label,
		     double max, double min, chtype color);
void plot_append_val(const struct plot *p, struct line *l, double v);

void paint_plot(const struct plot *p);

void init_flavor(void);
