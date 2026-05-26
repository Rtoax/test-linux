// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <string.h>
#include "plot.h"

chtype flavor[8] = { 0 };
static const char *verstring = "github.com/rtoax/test-linux v1.0.3";

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

void plot_paint_line(const struct plot *p, struct line *load, const char *label,
		     double max, double min, chtype color)
{
	int i = 0;
	for_each_value(load, v)
	{
		int h = p->plotheight + HEIGHT_BND - 1 -
			(v->v - min) * (p->plotheight - 2) / (max - min);
		int w = p->plotwidth + WIDTH_BND - load->count + i;
		attron(color);
		mvprintw(h, w, U2501);
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
	mvprintw(HEIGHT_BND, WIDTH_BND, U25B2);
	mvprintw(p->plotheight + HEIGHT_BND, p->plotwidth + WIDTH_BND, U25BA);
}

void paint_plot(const struct plot *p)
{
	erase();

	plot_draw_title(p);
	plot_draw_axes(p);

	double max = 0, min = 9999;
	for_each_line(p->lg, l)
	{
		max = max < l->max->v ? l->max->v : max;
		min = min > l->min->v ? l->min->v : min;
	}
	for_each_line(p->lg, l)
	{
		plot_paint_line(p, l, l->name, max, min, flavor[l->color]);
	}

	time_t sec = time(NULL);
	struct tm *tm = localtime(&sec);
	char ts[64] = { 0 };
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\n';
	mvaddstr(p->height - 2, p->width - strlen(ts) - 1, ts);

	mvaddstr(p->height - 1, p->width - strlen(verstring) - 1, verstring);

	move(0, 0);
}
