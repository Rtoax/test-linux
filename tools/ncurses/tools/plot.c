// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <string.h>
#include "plot.h"

chtype flavor[8] = { 0 };

void init_flavor(void)
{
	if (has_colors()) {
		int bg = COLOR_BLACK;
		start_color();
#define SET_COLOR(num, fg)                        \
	init_pair(num + 1, (short)fg, (short)bg); \
	flavor[num] |= (chtype)COLOR_PAIR(num + 1)

		SET_COLOR(C_GREEN, COLOR_GREEN);
		SET_COLOR(C_RED, COLOR_RED);
		SET_COLOR(C_CYAN, COLOR_CYAN);
		SET_COLOR(C_WHITE, COLOR_WHITE);
		SET_COLOR(C_MAGENTA, COLOR_MAGENTA);
		SET_COLOR(C_BLUE, COLOR_BLUE);
		SET_COLOR(C_YELLOW, COLOR_YELLOW);
#undef SET_COLOR
	}
}

void plot_update_size(struct plot *p)
{
	getmaxyx(stdscr, p->height, p->width);
	p->plotheight = p->height - HEIGHT_BND * 2;
	p->plotwidth = p->width - WIDTH_BND * 2;
}

void plot_paint_line(const struct plot *p, struct line *load, char *label,
		     double max, double min, chtype color)
{
	int i = 0;
	for_each_value(load, v)
	{
		int h = p->plotheight + HEIGHT_BND - 1 -
			(v->v - min) * (p->plotheight - 2) / (max - min);
		int w = p->plotwidth + WIDTH_BND - load->count + i;
		attron(color);
		mvprintw(h, w, "━");
		attroff(color);

		i++;

		/* set x axis */
		if ((i - 1) % 10 == 0) {
			char buf[10];
			strftime(buf, 10, "%T", localtime(&v->tv.tv_sec));
			mvprintw(p->height - HEIGHT_BND + 1, w, "%s", buf);
		}

		/* set y axis */
		attron(color);
		mvprintw(h, 0, "%.3f", v->v);
		if (i == load->count)
			mvprintw(h, w + 1, "%s", label);
		attroff(color);
	}
}

void plot_draw_title(const struct plot *p)
{
	mvaddstr(0, (p->width - strlen(p->title)) / 2, p->title);
}

void plot_draw_axes(const struct plot *p)
{
	mvhline(p->plotheight + HEIGHT_BND, WIDTH_BND, T_HLINE, p->plotwidth);
	mvvline(HEIGHT_BND, WIDTH_BND, T_VLINE, p->plotheight);
	mvaddch(p->plotheight + HEIGHT_BND, WIDTH_BND, T_LLCR);
	mvaddch(HEIGHT_BND, WIDTH_BND, T_UARR);
	mvprintw(HEIGHT_BND, WIDTH_BND, "▲");
	mvprintw(p->plotheight + HEIGHT_BND, p->plotwidth + WIDTH_BND, "►");
}
