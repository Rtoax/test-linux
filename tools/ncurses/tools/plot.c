// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <string.h>
#include "plot.h"

void plot_update_size(struct plot *p)
{
	getmaxyx(stdscr, p->height, p->width);
	p->plotheight = p->height - HEIGHT_BND * 2;
	p->plotwidth = p->width - WIDTH_BND * 2;
}

void plot_paint_values(const struct plot *p, struct values *load, char *label,
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
