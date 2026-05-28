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

static void unicode_bold_vertical(struct line *ln, int y, int x, int n)
{
	cchar_t wch_vline = WCH_U2503;
	mvvline_set(y, x, &wch_vline, n);
}

static void unicode_bold_ulcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U250F);
}

static void unicode_bold_llcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2517);
}

static void unicode_bold_urcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U2513);
}

static void unicode_bold_lrcorner(struct line *ln, int y, int x)
{
	mvprintw(y, x, U251B);
}

struct ldraw_ops unicode_bold_line_ops = {
	.horizon = unicode_bold_horizon,
	.vertical = unicode_bold_vertical,
	.ulcorner = unicode_bold_ulcorner,
	.llcorner = unicode_bold_llcorner,
	.urcorner = unicode_bold_urcorner,
	.lrcorner = unicode_bold_lrcorner,
};
