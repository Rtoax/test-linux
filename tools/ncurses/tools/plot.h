// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <ncurses.h>
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

#define C_GREEN 0
#define C_RED 1
#define C_CYAN 2
#define C_WHITE 3
#define C_MAGENTA 4
#define C_BLUE 5
#define C_YELLOW 6

#define HEIGHT_BND 4
#define WIDTH_BND 6

struct plot {
	char *title;
	int height, width;
	int plotheight, plotwidth;
};

void plot_update_size(struct plot *p);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);
void plot_paint_values(const struct plot *p, struct values *load, char *label,
		       double max, double min, chtype color);
