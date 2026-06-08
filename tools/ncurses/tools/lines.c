// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include "config.h"
#include "plot.h"
#include "value.h"

static void nothing(struct line *ln, int y, int x)
{
}

static void nothing_v(struct line *ln, int y, int x, int n)
{
}

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

static void utf8_horizon(struct line *ln, int y, int x)
{
	mvprintw(y, x, "-");
}

static void utf8_vertical(struct line *ln, int y, int x, int n)
{
	mvvline(y, x, '|', n);
}

static void utf8_cross(struct line *ln, int y, int x)
{
	mvprintw(y, x, "+");
}

static void unicode_boldbold_horizon(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2584);
}

static void unicode_boldbold_vertical(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2588;
	mvvline_set(y, x, &wch_vline, n);
}

static void unicode_boldbold_corner1(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2584);
}

static void unicode_boldbold_corner2(struct line *ln, int y, int x)
{
	cchar_t wch_vline = WCH_U2588;
	mvvline_set(y, x, &wch_vline, 1);
}

static void unicode_area_chart_horizon(struct line *ln, int y, int x)
{
	cchar_t wch_vline = WCH_U2588;
	struct plot *p = ln->lg->plot;
	int n = p->bnd.top + p->plotheight - y;
	mvvline_set(y, x, &wch_vline, n);
}

static void unicode_heart(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2665);
}

static void unicode_heart_vertical(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2665;
	mvvline_set(y, x, &wch_vline, n);
}

const struct ldraw_ops unicode_heart_line_ops = {
	.name = "unicode-heart",
	.horizon = unicode_heart,
	.vertical = unicode_heart_vertical,
	.ulcorner = unicode_heart,
	.llcorner = unicode_heart,
	.urcorner = unicode_heart,
	.lrcorner = unicode_heart,
};

const struct ldraw_ops unicode_boldbold_line_ops = {
	.name = "unicode-boldbold",
	.horizon = unicode_boldbold_horizon,
	.vertical = unicode_boldbold_vertical,
	.ulcorner = unicode_boldbold_corner1,
	.llcorner = unicode_boldbold_corner2,
	.urcorner = unicode_boldbold_corner1,
	.lrcorner = unicode_boldbold_corner2,
};

const struct ldraw_ops unicode_bold_line_ops = {
	.name = "unicode-bold",
	.horizon = unicode_bold_horizon,
	.vertical = unicode_bold_vertical,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
};

const struct ldraw_ops unicode_bold_dashed_line_ops = {
	.name = "unicode-bold-dashed",
	.horizon = unicode_bold_horizon_dashed_line,
	.vertical = unicode_bold_vertical_dashed_line,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
};

const struct ldraw_ops unicode_line_ops = {
	.name = "unicode",
	.horizon = unicode_horizon,
	.vertical = unicode_vertical,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
};

const struct ldraw_ops unicode_dashed_line_ops = {
	.name = "unicode-dashed",
	.horizon = unicode_horizon_dashed_line,
	.vertical = unicode_vertical_dashed_line,
	.ulcorner = unicode_ulcorner,
	.llcorner = unicode_llcorner,
	.urcorner = unicode_urcorner,
	.lrcorner = unicode_lrcorner,
};

const struct ldraw_ops unicode_area_chart_ops = {
	.name = "unicode-area-chart",
	.horizon = unicode_area_chart_horizon,
	.vertical = nothing_v,
	.ulcorner = nothing,
	.llcorner = nothing,
	.urcorner = nothing,
	.lrcorner = nothing,
};

const struct ldraw_ops utf8_line_ops = {
	.name = "utf8",
	.horizon = utf8_horizon,
	.vertical = utf8_vertical,
	.ulcorner = utf8_cross,
	.llcorner = utf8_cross,
	.urcorner = utf8_cross,
	.lrcorner = utf8_cross,
};

const struct ldraw_ops *ldraw_operations[LINE_TYPE_MAX] = {
	[LINE_TYPE_BOLD_UNICODE] = &unicode_bold_line_ops,
	[LINE_TYPE_BOLD_UNICODE_DASHED] = &unicode_bold_dashed_line_ops,
	[LINE_TYPE_BOLDBOLD_UNICODE] = &unicode_boldbold_line_ops,
	[LINE_TYPE_THIN_UNICODE] = &unicode_line_ops,
	[LINE_TYPE_THIN_UNICODE_DASHED] = &unicode_dashed_line_ops,
	[LINE_TYPE_AREA_CHART_UNICODE] = &unicode_area_chart_ops,
	[LINE_TYPE_UTF8] = &utf8_line_ops,
	[LINE_TYPE_HEART_UNICODE] = &unicode_heart_line_ops,
};

bool ldraw_hasname(const char *name)
{
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++)
		if (!strcmp(ldraw_operations[i]->name, name))
			return true;
	/**
	 * print error to stderr, hint to stdout.
	 */
	fprintf(stderr, "ERROR: not support line type '%s', please use:\n",
		name);
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++) {
		fprintf(stdout, "\t%s\n", ldraw_operations[i]->name);
	}
	return false;
}

enum ltype_enum ldraw_name2type(const char *name)
{
	for (int i = LINE_TYPE_DEFAULT; i < LINE_TYPE_MAX; i++)
		if (!strcmp(ldraw_operations[i]->name, name))
			return i;
	return LINE_TYPE_DEFAULT;
}

const struct ldraw_ops *ldraw_type2ops(enum ltype_enum t)
{
	if (t < LINE_TYPE_DEFAULT || t >= LINE_TYPE_MAX)
		t = LINE_TYPE_DEFAULT;
	return ldraw_operations[t];
}

const struct ldraw_ops *ldraw_name2ops(const char *name)
{
	return ldraw_type2ops(ldraw_name2type(name));
}

const char *ldraw_type2name(enum ltype_enum t)
{
	return ldraw_type2ops(t)->name;
}
