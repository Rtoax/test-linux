// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <errno.h>
#include <malloc.h>
#include <ncursesw/curses.h>
#include <string.h>
#include "config.h"
#include "plot.h"
#include "line.h"

static enum draw_ops_type_enum *draws = NULL;
static int nr_draws = 0;
static int idx_draw = -1;

static void nothing(const struct plot *p, WINDOW *win, int y, int x)
{
}

static void nothing_v(const struct plot *p, WINDOW *win, int y, int x, int n)
{
}

static void unicode_bold_horizon(const struct plot *p, WINDOW *win, int y,
				 int x, int n)
{
	for (int i = 0; i < n; i++)
		mvwprintw(win, y, x + i, U2501);
}

static void unicode_bold_uarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U25B2);
}

static void unicode_bold_darrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U25BC);
}

static void unicode_bold_rarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U25BA);
}

static void unicode_bold_point(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U25A0);
}

static void unicode_horizon(const struct plot *p, WINDOW *win, int y, int x,
			    int n)
{
	for (int i = 0; i < n; i++)
		mvwprintw(win, y, x + i, U2500);
}

static void unicode_bold_horizon_dashed_line(const struct plot *p, WINDOW *win,
					     int y, int x, int n)
{
	for (int i = 0; i < n; i++) {
		if ((x + i) % 2)
			mvwprintw(win, y, x + i, U2501);
	}
}

static void unicode_horizon_dashed_line(const struct plot *p, WINDOW *win,
					int y, int x, int n)
{
	for (int i = 0; i < n; i++) {
		if ((x + i) % 2)
			mvwprintw(win, y, x + i, U2500);
	}
}

static void unicode_uarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2191);
}

static void unicode_darrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2193);
}

static void unicode_rarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2192);
}

static void unicode_point(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U25AA);
}

static void unicode_bold_vertical(const struct plot *p, WINDOW *win, int y,
				  int x, int n)
{
	cchar_t wch_vline = WCH_U2503;
	mvwvline_set(win, y, x, &wch_vline, n);
}

static void unicode_vertical(const struct plot *p, WINDOW *win, int y, int x,
			     int n)
{
	cchar_t wch_vline = WCH_U2502;
	mvwvline_set(win, y, x, &wch_vline, n);
}

static void unicode_bold_vertical_dashed_line(const struct plot *p, WINDOW *win,
					      int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2503;
	for (int i = 0; i < n; i += 2)
		mvwvline_set(win, y + i, x, &wch_vline, 1);
}

static void unicode_vertical_dashed_line(const struct plot *p, WINDOW *win,
					 int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2502;
	for (int i = 0; i < n; i += 2)
		mvwvline_set(win, y + i, x, &wch_vline, 1);
}

static void unicode_bold_ulcorner(const struct plot *p, WINDOW *win, int y,
				  int x)
{
	mvwprintw(win, y, x, U250F);
}

static void unicode_ulcorner(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U250C);
}

static void unicode_bold_llcorner(const struct plot *p, WINDOW *win, int y,
				  int x)
{
	mvwprintw(win, y, x, U2517);
}

static void unicode_llcorner(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2514);
}

static void unicode_bold_urcorner(const struct plot *p, WINDOW *win, int y,
				  int x)
{
	mvwprintw(win, y, x, U2513);
}

static void unicode_urcorner(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2510);
}

static void unicode_bold_lrcorner(const struct plot *p, WINDOW *win, int y,
				  int x)
{
	mvwprintw(win, y, x, U251B);
}

static void unicode_lrcorner(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2518);
}

static void unicode_boldbold_horizon(const struct plot *p, WINDOW *win, int y,
				     int x, int n)
{
	for (int i = 0; i < n; i++)
		mvwprintw(win, y, x + i, U2584);
}

static void unicode_boldbold_vertical(const struct plot *p, WINDOW *win, int y,
				      int x, int n)
{
	cchar_t wch_vline = WCH_U2588;
	mvwvline_set(win, y, x, &wch_vline, n);
}

static void unicode_boldbold_corner1(const struct plot *p, WINDOW *win, int y,
				     int x)
{
	mvwprintw(win, y, x, U2584);
}

static void unicode_boldbold_corner2(const struct plot *p, WINDOW *win, int y,
				     int x)
{
	cchar_t wch_vline = WCH_U2588;
	mvwvline_set(win, y, x, &wch_vline, 1);
}

static void unicode_area_chart_horizon(const struct plot *p, WINDOW *win, int y,
				       int x, int n)
{
	cchar_t wch_vline = WCH_U2588;
	int _nx, ny;

	/**
	 * If it is not the main window, the length should correspond to the
	 * size of 'win' rather than the size of the plot.
	 */
	if (p->win != win) {
		getmaxyx(win, ny, _nx);
		ny -= y + 1;
		(void)_nx;
	} else
		ny = p->bnd.top + p->plotheight - y;

	for (int ix = 0; ix < n; ix++)
		mvwvline_set(win, y, x + ix, &wch_vline, ny);
}

static void unicode_heart(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, U2665);
}

static void unicode_heart_vertical(const struct plot *p, WINDOW *win, int y,
				   int x, int n)
{
	cchar_t wch_vline = WCH_U2665;
	mvwvline_set(win, y, x, &wch_vline, n);
}

static void unicode_heart_horizon(const struct plot *p, WINDOW *win, int y,
				  int x, int n)
{
	for (int i = 0; i < n; i++)
		mvwprintw(win, y, x + i, U2665);
}

/**
 * UTF-8
 */
static void utf8_horizon(const struct plot *p, WINDOW *win, int y, int x, int n)
{
	for (int i = 0; i < n; i++)
		mvwprintw(win, y, x + i, "-");
}

static void utf8_vertical(const struct plot *p, WINDOW *win, int y, int x,
			  int n)
{
	mvwvline(win, y, x, '|', n);
}

static void utf8_cross(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, "+");
}

static void utf8_uarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, "^");
}

static void utf8_darrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, "`");
}

static void utf8_rarrow(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, ">");
}

static void utf8_point(const struct plot *p, WINDOW *win, int y, int x)
{
	mvwprintw(win, y, x, ".");
}

/**
 * Line operations
 */

static const struct draw_operations unicode_heart_line_ops = {
	.name = "unicode-heart",
	.horizon = unicode_heart_horizon,
	.vertical = unicode_heart_vertical,
	.ulcorner = unicode_heart,
	.llcorner = unicode_heart,
	.urcorner = unicode_heart,
	.lrcorner = unicode_heart,
	.uarrow = unicode_heart,
	.darrow = unicode_heart,
	.rarrow = unicode_heart,
	.point = unicode_heart,
};

static const struct draw_operations unicode_boldbold_line_ops = {
	.name = "unicode-boldbold",
	.horizon = unicode_boldbold_horizon,
	.vertical = unicode_boldbold_vertical,
	.ulcorner = unicode_boldbold_corner1,
	.llcorner = unicode_boldbold_corner2,
	.urcorner = unicode_boldbold_corner1,
	.lrcorner = unicode_boldbold_corner2,
	.uarrow = unicode_bold_uarrow,
	.darrow = unicode_bold_darrow,
	.rarrow = unicode_bold_rarrow,
	.point = unicode_bold_point,
};

static const struct draw_operations unicode_bold_line_ops = {
	.name = "unicode-bold",
	.horizon = unicode_bold_horizon,
	.vertical = unicode_bold_vertical,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
	.uarrow = unicode_bold_uarrow,
	.darrow = unicode_bold_darrow,
	.rarrow = unicode_bold_rarrow,
	.point = unicode_bold_point,
};

static const struct draw_operations unicode_bold_dashed_line_ops = {
	.name = "unicode-bold-dashed",
	.horizon = unicode_bold_horizon_dashed_line,
	.vertical = unicode_bold_vertical_dashed_line,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
	.uarrow = unicode_bold_uarrow,
	.darrow = unicode_bold_darrow,
	.rarrow = unicode_bold_rarrow,
	.point = unicode_bold_point,
};

static const struct draw_operations unicode_line_ops = {
	.name = "unicode",
	.horizon = unicode_horizon,
	.vertical = unicode_vertical,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
	.uarrow = unicode_uarrow,
	.darrow = unicode_darrow,
	.rarrow = unicode_rarrow,
	.point = unicode_point,
};

static const struct draw_operations unicode_dashed_line_ops = {
	.name = "unicode-dashed",
	.horizon = unicode_horizon_dashed_line,
	.vertical = unicode_vertical_dashed_line,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
	.uarrow = unicode_uarrow,
	.darrow = unicode_darrow,
	.rarrow = unicode_rarrow,
	.point = unicode_point,
};

static const struct draw_operations unicode_area_chart_ops = {
	.name = "unicode-area-chart",
	.horizon = unicode_area_chart_horizon,
	.vertical = nothing_v,
	.ulcorner = nothing,
	.llcorner = nothing,
	.urcorner = nothing,
	.lrcorner = nothing,
	.uarrow = nothing,
	.darrow = nothing,
	.rarrow = nothing,
	.point = unicode_point,
};

static const struct draw_operations utf8_line_ops = {
	.name = "utf8",
	.horizon = utf8_horizon,
	.vertical = utf8_vertical,
	.ulcorner = utf8_cross,
	.llcorner = utf8_cross,
	.urcorner = utf8_cross,
	.lrcorner = utf8_cross,
	.uarrow = utf8_uarrow,
	.darrow = utf8_darrow,
	.rarrow = utf8_rarrow,
	.point = utf8_point,
};

static const struct draw_operations *draw_ops[LINE_TYPE_MAX] = {
	[LINE_TYPE_BOLD_UNICODE] = &unicode_bold_line_ops,
	[LINE_TYPE_BOLD_UNICODE_DASHED] = &unicode_bold_dashed_line_ops,
	[LINE_TYPE_BOLDBOLD_UNICODE] = &unicode_boldbold_line_ops,
	[LINE_TYPE_THIN_UNICODE] = &unicode_line_ops,
	[LINE_TYPE_THIN_UNICODE_DASHED] = &unicode_dashed_line_ops,
	[LINE_TYPE_AREA_CHART_UNICODE] = &unicode_area_chart_ops,
	[LINE_TYPE_UTF8] = &utf8_line_ops,
	[LINE_TYPE_HEART_UNICODE] = &unicode_heart_line_ops,
};

int draw_ops_print_names(FILE *fp)
{
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++) {
		fprintf(fp, "\t%s\n", draw_ops[i]->name);
	}
	return 0;
}

bool draw_ops_has_name(const char *name)
{
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++)
		if (!strcmp(draw_ops[i]->name, name))
			return true;
	/**
	 * print error to stderr, hint to stdout.
	 */
	fprintf(stderr, "ERROR: not support line type '%s', please use:\n",
		name);
	draw_ops_print_names(stdout);
	return false;
}

enum draw_ops_type_enum draw_ops_name2type(const char *name)
{
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++)
		if (!strcmp(draw_ops[i]->name, name))
			return i;
	return LINE_TYPE_DEFAULT;
}

const struct draw_operations *draw_ops_type2ops(enum draw_ops_type_enum t)
{
	if (t < LINE_TYPE_DEFAULT || t >= LINE_TYPE_MAX)
		t = LINE_TYPE_DEFAULT;
	return draw_ops[t];
}

const struct draw_operations *draw_ops_name2ops(const char *name)
{
	return draw_ops_type2ops(draw_ops_name2type(name));
}

const char *draw_ops_type2name(enum draw_ops_type_enum t)
{
	return draw_ops_type2ops(t)->name;
}

int enqueue_draw_ops(enum draw_ops_type_enum t)
{
	if (t >= LINE_TYPE_MAX || t < LINE_TYPE_DEFAULT)
		return -EINVAL;

	nr_draws++;
	draws = (enum draw_ops_type_enum *)realloc(
		draws, nr_draws * sizeof(enum draw_ops_type_enum));
	draws[nr_draws - 1] = t;
	return 0;
}

int get_nr_draw_ops(void)
{
	return nr_draws;
}

enum draw_ops_type_enum dequeue_draw_ops(void)
{
	if (nr_draws <= 0 || idx_draw >= nr_draws)
		return LINE_TYPE_DEFAULT;
	return draws[++idx_draw];
}

void reset_draw_ops_queue(void)
{
	idx_draw = -1;
}
