// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include "plot.h"

chtype flavor[C_MAX] = { 0 };
static const char *verstring = "github.com/rtoax/test-linux " MY_VERSION;

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg)
{
	assert(lg->ops->create && "lgroup ops is not set, set it first");

	if (!p->lghead) {
		p->lghead = lg;
		p->lgcount = 1;
	} else {
		p->lgtail->next = lg;
	}
	p->lgcount++;
	p->lgtail = lg;
	lg->plot = p;
	lg->ops->arg = lg_ops_arg;
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

void plot_update_size(struct plot *p, bool init)
{
	if (init) {
		p->bnd.top = BND_TOP;
		p->bnd.bottom = BND_BOTTOM;
		p->bnd.left = BND_LEFT;
		p->bnd.right = BND_RIGHT;
	} else {
		/**
		 * Just use left and right to make sure y axis values and line
		 * names show correctly.
		 */
		p->bnd.left = p->bnd.left > p->prev_max.left ? p->bnd.left :
							       p->prev_max.left;
		p->bnd.right = p->bnd.right > p->prev_max.right ?
				       p->bnd.right :
				       p->prev_max.right;
	}

	getmaxyx(stdscr, p->height, p->width);

	p->plotheight = p->height - p->bnd.bottom - p->bnd.top;
	p->plotwidth = p->width - p->bnd.left - p->bnd.right;

	if (p->heightmax < p->height)
		p->heightmax = p->height;
	if (p->widthmax < p->width)
		p->widthmax = p->width;

	p->prev_max.left = BND_LEFT;
	p->prev_max.right = BND_RIGHT;
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

static void paint_line(struct plot *p, struct line *ln, double max, double min)
{
	int i = 0;
	int prev_h = -1;
	chtype color = flavor[ln->color];

	for_each_value(ln, v)
	{
		double span = .0f, diff = .0f;

		/**
		 * The number of data points may be greater than the horizontal
		 * size of the plotting area, so it is necessary to first skip
		 * the data points that exceed the plotting area.
		 *
		 *     |------------------------| count
		 *         |--------------------| plotwidth
		 *
		 *     ^^^^^ skip
		 *
		 * see also __paint_plot_lg().
		 */
		if (i <= ln->count - p->plotwidth) {
			i++;
			continue;
		}

		if (max == min || max == 0.0 || max < min) {
			diff = 0;
			span = 1;
		} else {
			diff = v->v - min;
			span = max - min;
		}

		int h = p->plotheight + p->bnd.top - 1 -
			diff * (p->plotheight - 2) / span;
		int w = p->plotwidth + p->bnd.left - ln->count + i;

		attron(color);
		ln->ops->horizon(ln, h, w);
		attroff(color);

		/**
		 * Print the corner, like: ---+
		 *                            |
		 *                            +----
		 */
		if (prev_h != -1) {
			attron(color);
			if (prev_h > h) {
				ln->ops->lrcorner(ln, prev_h, w);
				ln->ops->ulcorner(ln, h, w);
				ln->ops->vertical(ln, h + 1, w, prev_h - h - 1);
			} else if (h > prev_h) {
				ln->ops->urcorner(ln, prev_h, w);
				ln->ops->llcorner(ln, h, w);
				ln->ops->vertical(ln, prev_h + 1, w,
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
			mvprintw(p->height - p->bnd.bottom + 1, w, "%s", buf);
		}

		/* set y axis */
		attron(color);
		char sv[64];
		int nc = snprintf(sv, 64, "%.3f", v->v);
		if (p->prev_max.left < nc)
			p->prev_max.left = nc;
		mvprintw(h, 0, "%s", sv);

		if (i == ln->count) {
			mvprintw(h, w + 1, "%s", ln->name);
			nc = strlen(ln->name);
			if (p->prev_max.right < nc)
				p->prev_max.right = nc;
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
	mvhline(p->plotheight + p->bnd.top, p->bnd.left, T_HLINE, p->plotwidth);
	mvvline(p->bnd.top, p->bnd.left, T_VLINE, p->plotheight);
	mvaddch(p->plotheight + p->bnd.top, p->bnd.left, T_LLCR);

	mvaddch(p->bnd.top, p->bnd.left, T_UARR);
	mvprintw(p->bnd.top, p->bnd.left, U25B2);
	if (p->label_y)
		mvaddstr(p->bnd.top - 1, p->bnd.left, p->label_y);

	mvprintw(p->plotheight + p->bnd.top, p->plotwidth + p->bnd.left, U25BA);
	if (p->label_x)
		mvaddstr(p->plotheight + p->bnd.top + 1,
			 p->plotwidth + p->bnd.left, p->label_x);
}

static void __paint_plot_lg(struct plot *p, const struct lgroup *lg)
{
	double max = -DBL_MAX, min = DBL_MAX;

	/* find min and max first */
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;

		/* see also line count and plotwidth check in paint_line() */
		double _max = line_range_max(l, l->count - p->plotwidth,
					     p->plotwidth);
		double _min = line_range_min(l, l->count - p->plotwidth,
					     p->plotwidth);
		max = max < _max ? _max : max;
		min = min > _min ? _min : min;
	}

	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		paint_line(p, l, max, min);
	}
#ifdef DEBUG
	if (lg->ops->plot_debug)
		lg->ops->plot_debug(lg, lg->ops->arg);
#endif
}

/**
 * need erase() before, refresh() after
 */
void paint_plot(struct plot *p)
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

#ifdef DEBUG
	mvprintw(p->height - 2, 0, "plot: (%d,%d) max(%d,%d) plot(%d,%d)",
		 p->height, p->width, p->heightmax, p->widthmax, p->plotheight,
		 p->plotwidth);
#endif

	move(0, 0);
}

void plot_create_data(struct plot *p)
{
	for_each_lg(p, lg)
	{
		lg->ops->create(lg, lg->ops->arg);
	}
}

void plot_update_data(struct plot *p)
{
	for_each_lg(p, lg)
	{
		lg->ops->update(lg, lg->ops->arg);
	}
}

void redraw_screen(struct plot *p)
{
	erase();
	paint_plot(p);
	refresh();

	plot_update_size(p, false);
}
