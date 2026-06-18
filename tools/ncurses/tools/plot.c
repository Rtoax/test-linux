// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "plot.h"
#include "keyboard.h"

chtype flavor[C_MAX] = { 0 };
static const char *verstring = GIT_REPO " " MY_VERSION;

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg)
{
	assert(lg->ops->create && "lgroup ops is not set, set it first");

	if (!p->lghead) {
		p->lghead = lg;
		p->lgcount = 1;
	} else {
		p->lgtail->next = lg;
		p->lgcount++;
	}
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
		p->bnd.left = p->bnd.left > p->bnd_prev_max.left ?
				      p->bnd.left :
				      p->bnd_prev_max.left;
		p->bnd.right = p->bnd.right > p->bnd_prev_max.right ?
				       p->bnd.right :
				       p->bnd_prev_max.right;
	}

	getmaxyx(stdscr, p->height, p->width);

	p->plotheight = p->height - p->bnd.bottom - p->bnd.top;
	p->plotwidth = p->width - p->bnd.left - p->bnd.right;

	if (p->heightmax < p->height)
		p->heightmax = p->height;
	if (p->widthmax < p->width)
		p->widthmax = p->width;

	/**
	 * When refreshing or modifying the drawing type, the boundary size may
	 * change. We need to reset the maximum value to avoid excessive blank
	 * space at the boundary.
	 */
	switch (p->keyboard.current_key) {
	case 'r':
	case 't':
		p->bnd.top = p->bnd_prev_max.top;
		p->bnd.bottom = p->bnd_prev_max.bottom;
		p->bnd.left = p->bnd_prev_max.left;
		p->bnd.right = p->bnd_prev_max.right;
		p->need_redraw = true;
		break;
	}

	p->bnd_prev_max.top = BND_TOP;
	p->bnd_prev_max.bottom = BND_BOTTOM;
	p->bnd_prev_max.left = BND_LEFT;
	p->bnd_prev_max.right = BND_RIGHT;
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

/**
 * @max and @min is original value, if use logarithmic, must convert it youself.
 */
static void paint_line(struct plot *p, struct line *ln, double max, double min,
		       bool debug)
{
	int iv;
	int nvs = (ln->count + p->plotscaling - 1) / p->plotscaling;
	int prev_h = -1;
	chtype color = flavor[ln->color];

	switch (p->v_scaling) {
	case NS_LOGARITHMIC:
		max = log(max);
		min = log(min);
		break;
	case NS_LOGARITHMIC10:
		max = log10(max);
		min = log10(min);
		break;
	case NS_EXPONENTIAL:
		max = exp(max);
		min = exp(min);
		break;
	case NS_NONE:
	default:
		break;
	}

	iv = 0;

	for_each_value(ln, v)
	{
		double span = .0f, diff = .0f;
		double plot_v = v->v;

		int ivs = (iv + p->plotscaling - 1) / p->plotscaling;

		/**
		 * The number of data points may be greater than the horizontal
		 * size of the plotting area, so it is necessary to first skip
		 * the data points that exceed the plotting area.
		 *
		 *     |------------------------| count
		 *         |--------------------| plotwidth * plotscaling
		 *
		 *     ^^^^^ skip
		 *
		 * see also paint_lgroup().
		 */
		if (iv <= ln->count - p->plotwidth * p->plotscaling) {
			iv++;
			continue;
		}

		if (iv % p->plotscaling != 0) {
			iv++;
			continue;
		}

		if (p->v_scaling == NS_LOGARITHMIC)
			plot_v = v->logarithmic_v;
		else if (p->v_scaling == NS_LOGARITHMIC10)
			plot_v = v->logarithmic10_v;
		else if (p->v_scaling == NS_EXPONENTIAL)
			plot_v = v->exponential_v;

		if (max == min || max == 0.0 || max < min) {
			diff = 0;
			span = 1;
		} else {
			diff = plot_v - min;
			span = max - min;
		}

		int h = p->plotheight + p->bnd.top - 1 -
			diff * (p->plotheight - 2) / span;
		int w = p->plotwidth + p->bnd.left - (nvs - ivs);

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

		iv++;

		/* set x axis */
		if ((ivs - 1) % 10 == 0) {
			char buf[10];
			strftime(buf, 10, "%T", localtime(&v->tv.tv_sec));
			mvprintw(p->height - p->bnd.bottom + 1, w, "%s", buf);
		}

		/* set y axis */
		attron(color);
		char sv[64];
		int nc;

		if (p->v_scaling == NS_LOGARITHMIC)
			nc = snprintf(sv, 64, "log(%.3f)=%.3f", v->v, plot_v);
		else if (p->v_scaling == NS_LOGARITHMIC10)
			nc = snprintf(sv, 64, "log10(%.3f)=%.3f", v->v, plot_v);
		else if (p->v_scaling == NS_EXPONENTIAL)
			nc = snprintf(sv, 64, "exp(%.3f)=%.3f", v->v, plot_v);
		else
			nc = snprintf(sv, 64, "%.3f", v->v);

		if (p->bnd_prev_max.left < nc)
			p->bnd_prev_max.left = nc;

		mvprintw(h, 0, "%s", sv);

		if (iv + p->plotscaling > ln->count) {
			mvprintw(h, w + 1, "%s", ln->name);
			nc = strlen(ln->name);
			if (p->bnd_prev_max.right < nc)
				p->bnd_prev_max.right = nc;

			if (debug) {
				mvprintw(h + 1, w + 1, "%ld", ln->count);
				mvprintw(h + 2, w + 1, "%.1f", ln->min->v);
				mvprintw(h + 3, w + 1, "%.1f", ln->max->v);
			}
		}
		attroff(color);
	}
}

void plot_draw_title(const struct plot *p)
{
	char buf[128], *title = buf;
	if (p->v_scaling == NS_LOGARITHMIC)
		snprintf(buf, 128, "%s (logarithmic)", p->title);
	else if (p->v_scaling == NS_LOGARITHMIC10)
		snprintf(buf, 128, "%s (base-10 logarithmic)", p->title);
	else if (p->v_scaling == NS_EXPONENTIAL)
		snprintf(buf, 128, "%s (base-e exponential)", p->title);
	else
		title = p->title;
	mvaddstr(0, (p->width - strlen(title)) / 2, title);
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

static void paint_lgroup(struct plot *p, const struct lgroup *lg, bool debug)
{
	double max = -DBL_MAX, min = DBL_MAX;

	/**
	 * Since we are not drawing all the data for the entire curve, we need
	 * to first obtain the maximum and minimum values of the data for the
	 * plotting portion.
	 */
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;

		/* see also line count and plotwidth check in paint_line() */
		int len = p->plotwidth * p->plotscaling;
		int start = l->count - len;

		double _max = line_range_max(l, start, len);
		double _min = line_range_min(l, start, len);
		max = max < _max ? _max : max;
		min = min > _min ? _min : min;
	}

	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		paint_line(p, l, max, min, debug);
	}

	if (debug && lg->ops->plot_debug)
		lg->ops->plot_debug(lg, lg->ops->arg);
}

/**
 * need erase() before, refresh() after
 */
static void paint_plot(struct plot *p, bool debug)
{
	plot_draw_title(p);
	plot_draw_axes(p);

	for_each_lg(p, lg)
	{
		paint_lgroup(p, lg, debug);
	}

	time_t sec = time(NULL);
	struct tm *tm = localtime(&sec);
	char ts[64] = { 0 };
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\n';
	mvaddstr(p->height - 2, p->width - strlen(ts) - 1, ts);

	mvaddstr(p->height - 1, p->width - strlen(verstring) - 1, verstring);

	if (debug) {
		mvprintw(
			p->height - 2, 0,
			"plot: mem(%.3f MiB) win(%d,%d) max(%d,%d) plot(%d,%d) "
			"scale(%d) key(cnt=%ld,cur=%d=0x%x='%s')",
			plot_mem_size(p) * 1. / 1024 / 1024, p->height,
			p->width, p->heightmax, p->widthmax, p->plotheight,
			p->plotwidth, p->plotscaling, p->keyboard.cnt.total,
			p->keyboard.current_key, p->keyboard.current_key,
			keyname(p->keyboard.current_key));
		mvprintw(p->height - 1, 0,
			 "      redraw=%ld, key(left=%ld,right=%ld,up=%ld,"
			 "down=%ld,l=%ld,r=%ld,h=%ld,v=%ld,t=%ld,enter=%ld)",
			 p->redrawcount, p->keyboard.cnt.left,
			 p->keyboard.cnt.right, p->keyboard.cnt.up,
			 p->keyboard.cnt.down, p->keyboard.cnt.l,
			 p->keyboard.cnt.r, p->keyboard.cnt.h,
			 p->keyboard.cnt.v, p->keyboard.cnt.t,
			 p->keyboard.cnt.enter);
	}

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

static void __plot_redraw(struct plot *p, bool debug)
{
	p->need_redraw = false;
	p->redrawcount++;

	erase();

	/**
	 * Handle the keyboard first, because 'reset' need before paint.
	 */
	exec_key_handler(p->keyboard.current_key);

	paint_plot(p, debug);

	if (p->help_expired_usec && p->help_expired_usec > usecs()) {
		plot_help(p);
	} else {
		p->help_expired_usec = 0;
	}

	if (p->llabel_expired_usec && p->llabel_expired_usec > usecs()) {
		plot_llabel(p);
	} else {
		p->llabel_expired_usec = 0;
	}

	refresh();

	plot_update_size(p, false);

	/* do some reset */
	p->keyboard.current_key = 0;
}

void plot_redraw(struct plot *p, bool debug)
{
	__plot_redraw(p, debug);

	if (p->need_redraw) {
		plot_update_size(p, false);
		__plot_redraw(p, debug);
	}
}

void plot_help(const struct plot *p)
{
	int h = p->plotheight + p->bnd.top - 1;
	int w = p->bnd.left + 1;

	attron(flavor[C_BLUE] | A_BOLD);
	mvprintw(h - 8, w, KEY_HELP_h);
	mvprintw(h - 7, w, KEY_HELP_l);
	mvprintw(h - 6, w, KEY_HELP_q);
	mvprintw(h - 5, w, KEY_HELP_r);
	mvprintw(h - 4, w, KEY_HELP_t);
	mvprintw(h - 3, w, KEY_HELP_v);
	mvprintw(h - 2, w, KEY_HELP_UP);
	mvprintw(h - 1, w, KEY_HELP_DOWN);
	mvprintw(h, w, KEY_HELP_ENTER);
	attroff(flavor[C_BLUE] | A_BOLD);
}

void plot_llabel(const struct plot *p)
{
	int i, nline = 0;

	for_each_lg(p, lg)
	{
		nline += lg->count;
	}

	int h = p->plotheight + p->bnd.top - 1;
	int w = p->bnd.left + 1;

	i = 0;
	for_each_lg(p, lg)
	{
		for_each_line(lg, ln)
		{
			int hi = h - nline + i + 1;
			const int n = 6;

			attron(flavor[ln->color] | A_BOLD);
			for (int x = 0; x < n; x++)
				ln->ops->horizon(ln, hi, w + x);
			mvprintw(hi, w + n + 1, " %s", ln->name);
			attroff(flavor[ln->color] | A_BOLD);
			i++;
		}
	}
}

/**
 * Press key 'h', display the help info
 */
static void key_h(int key, void *arg)
{
	struct plot *p = arg;
	p->help_expired_usec = usecs() + 10e6;
	plot_help(p);
}

/**
 * Press key 'l', display the label for each line.
 */
static void key_l(int key, void *arg)
{
	struct plot *p = arg;
	p->llabel_expired_usec = usecs() + 10e6;
	plot_llabel(p);
}

/**
 * Press key 'r', reset plot
 */
static void key_r(int key, void *arg)
{
	struct plot *p = arg;

	plot_scaling_init(p);
	p->help_expired_usec = 0;
	p->llabel_expired_usec = 0;
}

void plot_init(struct plot *p)
{
	memset(p, 0, sizeof(struct plot));

	plot_scaling_init(p);

	register_key_handler('r', p, key_r);
	register_key_handler('h', p, key_h);
	register_key_handler('l', p, key_l);
}

/* Get memory bytes that plot already spent */
unsigned long plot_mem_size(const struct plot *p)
{
	unsigned long bytes = sizeof(struct plot);
	for_each_lg(p, lg)
	{
		bytes += sizeof(struct lgroup);
		for_each_line(lg, ln)
		{
			bytes += sizeof(struct line);
			bytes += ln->count * sizeof(struct value);
		}
	}
	return bytes;
}
