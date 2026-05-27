// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "plot.h"

chtype flavor[C_MAX] = { 0 };
static const char *verstring = "github.com/rtoax/test-linux v1.1.0";

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg)
{
	assert(lg->ops.create && "lgroup ops is not set, set it first");

	if (!p->lghead) {
		p->lghead = lg;
		p->lgcount = 1;
	} else {
		p->lgtail->next = lg;
	}
	p->lgcount++;
	p->lgtail = lg;
	lg->plot = p;
	lg->ops.arg = lg_ops_arg;
	return 0;
}

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
	p->plotheight = p->height - BND_BOTTOM - BND_TOP;
	p->plotwidth = p->width - BND_LEFT - BND_RIGHT;
}

void plot_append_val(const struct plot *p, struct line *l, double v)
{
	struct timeval now;
	gettimeofday(&now, NULL);

	/* Only add new value when the time interval is at least 1 second */
	if (l->tail && l->tail->tv.tv_sec == now.tv_sec)
		return;
	enqueue_val(l, v);

	/**
	 * Due to the limited width of the screen, we removed unnecessary
	 * history records. TODO: maybe we should keep the old values.
	 */
	for (int i = p->plotwidth - 2; i < l->count; i++)
		dequeue_val(l);
}

void __plot_warning(const struct plot *p, char *fmt, ...)
{
	char buff[256];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buff, 256, fmt, va);
	va_end(va);
	attron(flavor[C_RED] | A_BOLD);
	mvaddstr(p->height / 2, (p->width - strlen(buff)) / 2, buff);
	attroff(flavor[C_RED] | A_BOLD);
}

void plot_paint_line(const struct plot *p, struct line *ln, const char *label,
		     double max, double min, chtype color)
{
	int i = 0;
	int prev_h = -1;

	for_each_value(ln, v)
	{
		double span = .0f, diff = .0f;

		if (max == min || max == 0.0 || max < min) {
			diff = 0;
			span = 1;
		} else {
			diff = v->v - min;
			span = max - min;
		}

		int h = p->plotheight + BND_TOP - 1 -
			diff * (p->plotheight - 2) / span;
		int w = p->plotwidth + BND_LEFT - ln->count + i;
		attron(color);
		mvprintw(h, w, U2501);
		attroff(color);

		/**
		 * Print the corner, like: ---+
		 *                            |
		 *                            +----
		 */
		if (prev_h != -1) {
			attron(color);
			cchar_t wch_vline = WCH_U2503;
			if (prev_h > h) {
				mvprintw(prev_h, w, U251B);
				mvprintw(h, w, U250F);
				mvvline_set(h + 1, w, &wch_vline,
					    prev_h - h - 1);
			} else if (h > prev_h) {
				mvprintw(prev_h, w, U2513);
				mvprintw(h, w, U2517);
				mvvline_set(prev_h + 1, w, &wch_vline,
					    h - prev_h - 1);
			}
			attroff(color);
		}

		prev_h = h;

		i++;

		/* set x axis */
		if ((i - 1) % 10 == 0) {
			char buf[10];
			strftime(buf, 10, "%T", localtime(&v->tv.tv_sec));
			mvprintw(p->height - BND_BOTTOM + 1, w, "%s", buf);
		}

		/* set y axis */
		attron(color);
		mvprintw(h, 0, "%.3f", v->v);
		if (i == ln->count) {
			mvprintw(h, w + 1, "%s", label);
#ifdef DEBUG
			mvprintw(h + 1, w + 1, "%d", ln->count);
			mvprintw(h + 2, w + 1, "%.1f", ln->min->v);
			mvprintw(h + 3, w + 1, "%.1f", ln->max->v);
#endif
		}
		attroff(color);
	}
}

void plot_draw_title(const struct plot *p)
{
	mvaddstr(0, (p->width - strlen(p->title)) / 2, p->title);
}

void plot_draw_axes(const struct plot *p)
{
	mvhline(p->plotheight + BND_TOP, BND_LEFT, T_HLINE, p->plotwidth);
	mvvline(BND_TOP, BND_LEFT, T_VLINE, p->plotheight);
	mvaddch(p->plotheight + BND_TOP, BND_LEFT, T_LLCR);

	mvaddch(BND_TOP, BND_LEFT, T_UARR);
	mvprintw(BND_TOP, BND_LEFT, U25B2);
	if (p->label_y)
		mvaddstr(BND_TOP - 1, BND_LEFT, p->label_y);

	mvprintw(p->plotheight + BND_TOP, p->plotwidth + BND_LEFT, U25BA);
	if (p->label_x)
		mvaddstr(p->plotheight + BND_TOP + 1, p->plotwidth + BND_LEFT,
			 p->label_x);
}

static void __paint_plot_lg(const struct plot *p, const struct lgroup *lg)
{
	double max = 0, min = 9999;

	/* find min and max first */
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		max = max < l->max->v ? l->max->v : max;
		min = min > l->min->v ? l->min->v : min;
	}
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		plot_paint_line(p, l, l->name, max, min, flavor[l->color]);
	}
}

/**
 * need erase() before, refresh() after
 */
void paint_plot(const struct plot *p)
{
	plot_draw_title(p);
	plot_draw_axes(p);

	for_each_lg(p, lg)
	{
		__paint_plot_lg(p, lg);
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

void redraw_screen(const struct plot *p)
{
	erase();

	for_each_lg(p, lg)
	{
		lg->ops.update(lg, lg->ops.arg);
	}

	paint_plot(p);
	refresh();
}
