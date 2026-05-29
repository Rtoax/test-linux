// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include "config.h"
#include "plot.h"
#include "value.h"

static void unicode_bold_horizon(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2501);
}

static void unicode_horizon(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2500);
}

static void unicode_bold_horizon_dashed_line(struct line *ln, int y, int x)
{
	if (x % 2)
		mvprintw(y, x, U2501);
}

static void unicode_horizon_dashed_line(struct line *ln, int y, int x)
{
	if (x % 2)
		mvprintw(y, x, U2500);
}

static void unicode_bold_vertical(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2503;
	mvvline_set(y, x, &wch_vline, n);
}

static void unicode_vertical(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2502;
	mvvline_set(y, x, &wch_vline, n);
}

static void unicode_bold_vertical_dashed_line(struct line *ln, int y, int x,
					      int n)
{
	cchar_t wch_vline = WCH_U2503;
	for (int i = 0; i < n; i += 2)
		mvvline_set(y + i, x, &wch_vline, 1);
}

static void unicode_vertical_dashed_line(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2502;
	for (int i = 0; i < n; i += 2)
		mvvline_set(y + i, x, &wch_vline, 1);
}

static void unicode_bold_ulcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U250F);
}

static void unicode_ulcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U250C);
}

static void unicode_bold_llcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2517);
}

static void unicode_llcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2514);
}

static void unicode_bold_urcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2513);
}

static void unicode_urcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2510);
}

static void unicode_bold_lrcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U251B);
}

static void unicode_lrcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2518);
}

struct ldraw_ops unicode_bold_line_ops = {
	.horizon = unicode_bold_horizon,
	.vertical = unicode_bold_vertical,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
};

struct ldraw_ops unicode_bold_dashed_line_ops = {
	.horizon = unicode_bold_horizon_dashed_line,
	.vertical = unicode_bold_vertical_dashed_line,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
};

struct ldraw_ops unicode_line_ops = {
	.horizon = unicode_horizon,
	.vertical = unicode_vertical,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
};

struct ldraw_ops unicode_line_dashed_line_ops = {
	.horizon = unicode_horizon_dashed_line,
	.vertical = unicode_vertical_dashed_line,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
};
