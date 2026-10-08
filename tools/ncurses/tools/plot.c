// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "file.h"
#include "plot.h"
#include "keyboard.h"
#include "utils.h"
#include "dialog.h"
#include "plotcake.h"

chtype colors[C_MAX] = { 0 };
static const char *verstring = GIT_REPO " " MY_VERSION;

static int __paint_help_win(struct plot *p, bool init);
static int __paint_llabels_win(struct plot *p, bool init);

int plot_add_lgroup(struct plot *p, struct lgroup *lg, void *lg_ops_arg)
{
	if (!p->lghead) {
		p->lghead = lg;
		p->lgcount = 1;
	} else {
		p->lgtail->next = lg;
		p->lgcount++;
	}
	p->lgtail = lg;
	lg->plot = p;
	lg->id = p->lgcount;
	if (lg->ops) {
		lg->ops->arg = lg_ops_arg;
	}

	assert(!(!lg->ops && lg_ops_arg) && "not allow none-ops with ops arg");
	return 0;
}

struct lgroup *plot_lgroup(const struct plot *p, int idx)
{
	for_each_lgroup(p, lg)
	{
		if (lg->id == idx)
			return lg;
	}
	return NULL;
}

void init_flavor(void)
{
	if (has_colors()) {
		int bg = COLOR_BLACK;
		start_color();
#define SET_COLOR(num, fg)                        \
	init_pair(num + 1, (short)fg, (short)bg); \
	colors[num] |= (chtype)COLOR_PAIR(num + 1)

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

chtype getflavor(enum lcolor_enum color)
{
	return colors[color];
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

	getmaxyx(p->win, p->height, p->width);

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
	switch (p->kb->current_key) {
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
	attron(colors[C_RED] | A_BOLD);
	mvaddstr(p->height / 2, (p->width - strlen(buff)) / 2, buff);
	attroff(colors[C_RED] | A_BOLD);
}

static int get_plot_value_heigh(const struct plot *p, double min, double max,
				double v)
{
	double span = .0f, diff = .0f;

	if (max == min || max == 0.0 || max < min) {
		diff = 0;
		span = 1;
	} else {
		diff = v - min;
		span = max - min;
	}
	return p->plotheight + p->bnd.top - 1 -
	       diff * (p->plotheight - 2) / span;
}

static double get_plot_value(const struct plot *p, const struct value *v)
{
	double val = v->v;

	if (p->curve_type == CURVE_TYPE_LOGARITHMIC)
		val = v->log_v;
	else if (p->curve_type == CURVE_TYPE_LOGARITHMIC10)
		val = v->log10_v;
	else if (p->curve_type == CURVE_TYPE_EXPONENTIAL)
		val = v->exp_v;
	else if (p->curve_type == CURVE_TYPE_DELTA)
		val = delta_v(v);

	return val;
}

/**
 * @start: start point of line.
 * @len: number of value to plot.
 * @max and @min is algorithm value, in the case of a logarithmic plot, 'max'
 * is already a logarithmic value.
 */
static void __paint_line(struct plot *p, const struct lgroup *lg,
			 const struct line *ln, int start, int len, int shift,
			 double max, double min)
{
	int iv;
	int prev_h = -1;
	chtype color = colors[ln->color];

	const long ln_shift_count = ln->count - shift;
	const int nvs = (ln_shift_count + p->plotscaling - 1) / p->plotscaling;

	iv = -1;
	for_each_value(ln, v)
	{
		iv++;
		/**
		 * The number of data points may be greater than the horizontal
		 * size of the plotting area, so it is necessary to first skip
		 * the data points that exceed the plotting area.
		 *
		 * line: |------------------------| line count
		 *
		 *                      <--shift--> plotshift * plotscaling
		 *
		 *       |--------------|           @ln_shift_count
		 *
		 * plot:        |=======|           plotwidth * plotscaling
		 *
		 *              ^ start
		 *                      ^ start + len
		 *
		 *     ^^^^^ skip
		 *
		 * see also paint_lgroup().
		 */
		if (iv <= start || iv >= start + len) {
			continue;
		}

		if (iv % p->plotscaling != 0) {
			continue;
		}

		double plot_v = get_plot_value(p, v);

		/**
		 * 1. the last value of line may be NaN, see delta_v()
		 */
		if (isnan(plot_v)) {
			iv = ln_shift_count;
			goto print_llabel;
		}

		int ivs = (iv + p->plotscaling - 1) / p->plotscaling;

		int h = get_plot_value_heigh(p, min, max, plot_v);
		int w = p->plotwidth + p->bnd.left - (nvs - ivs);

		attron(color);
		ln->ops->horizon(p, p->win, h, w, 1);
		attroff(color);

		/**
		 * Print the corner, like: ---+
		 *                            |
		 *                            +----
		 */
		if (prev_h != -1) {
			attron(color);
			if (prev_h > h) {
				ln->ops->lrcorner(p, p->win, prev_h, w);
				ln->ops->ulcorner(p, p->win, h, w);
				ln->ops->vertical(p, p->win, h + 1, w,
						  prev_h - h - 1);
			} else if (h > prev_h) {
				ln->ops->urcorner(p, p->win, prev_h, w);
				ln->ops->llcorner(p, p->win, h, w);
				ln->ops->vertical(p, p->win, prev_h + 1, w,
						  h - prev_h - 1);
			}
			attroff(color);
		}

		prev_h = h;

		/* set x axis */
		if ((ivs - 1) % 10 == 0) {
			switch (p->x_type) {
			case X_TIMEVAL: {
				char buf[32];
				mvprintw(p->height - p->bnd.bottom + 1, w, "%s",
					 timeval_str(&v->x_v.tv, buf));
				break;
			}
			case X_INDEX:
				mvprintw(p->height - p->bnd.bottom + 1, w,
					 "%ld", v->x_v.idx);
				break;
			default:
				break;
			}
		}

		/* set y axis */
		char sv[64];
		int nc;

		if (p->curve_type == CURVE_TYPE_LOGARITHMIC)
			nc = snprintf(sv, 64, "s*log(1+|%.3f|)=%.3f", v->v,
				      plot_v);
		else if (p->curve_type == CURVE_TYPE_LOGARITHMIC10)
			nc = snprintf(sv, 64, "s*log10(1+|%.3f|)=%.3f", v->v,
				      plot_v);
		else if (p->curve_type == CURVE_TYPE_EXPONENTIAL)
			nc = snprintf(sv, 64, "exp(%.3f)=%.3f", v->v, plot_v);
		else if (p->curve_type == CURVE_TYPE_DELTA)
			nc = snprintf(sv, 64, "delta(%.3f-%.3f)=%.3f",
				      v->next->v, v->v, plot_v);
		else
			nc = snprintf(sv, 64, "%.3f", plot_v);

		if (p->bnd_prev_max.left < nc)
			p->bnd_prev_max.left = nc;

		attron(color);
		mvprintw(h, 0, "%s", sv);
		attroff(color);

print_llabel:
		attron(color);
		if (iv + 1 + p->plotscaling > ln_shift_count) {
			mvprintw(h, w + 1, "%s", ln->name);
			nc = strlen(ln->name);
			if (p->bnd_prev_max.right < nc)
				p->bnd_prev_max.right = nc;

			if (p->debug) {
				mvprintw(h + 1, w + 1, "%ld", ln->count);
				mvprintw(h + 2, w + 1, "%.1f", ln->min->v);
				mvprintw(h + 3, w + 1, "%.1f", ln->max->v);
			}
		}
		attroff(color);
	}
}

static void __draw_title(const struct plot *p)
{
	char buf[sizeof(p->title) + 128];

	if (p->curve_type == CURVE_TYPE_LOGARITHMIC)
		snprintf(buf, sizeof(buf), "%s (signed logarithmic)", p->title);
	else if (p->curve_type == CURVE_TYPE_LOGARITHMIC10)
		snprintf(buf, sizeof(buf), "%s (base-10 signed logarithmic)",
			 p->title);
	else if (p->curve_type == CURVE_TYPE_EXPONENTIAL)
		snprintf(buf, sizeof(buf), "%s (base-e exponential)", p->title);
	else if (p->curve_type == CURVE_TYPE_DELTA)
		snprintf(buf, sizeof(buf), "%s (delta)", p->title);
	else
		snprintf(buf, sizeof(buf), "%s", p->title);

	mvaddstr(0, (p->width - strlen(buf)) / 2, buf);

	if (p->debug) {
		char buf2[64];
		snprintf(buf2, sizeof(buf2), "<pid:%d>", getpid());
		mvaddstr(1, (p->width - strlen(buf2)) / 2, buf2);
	}
}

static void __draw_axes(const struct plot *p)
{
	const struct ltype_ops *ops = ltype_type2ops(p->axis_curve_type);

	ops->horizon(p, p->win, p->plotheight + p->bnd.top, p->bnd.left,
		     p->plotwidth);
	ops->vertical(p, p->win, p->bnd.top, p->bnd.left, p->plotheight);
	ops->llcorner(p, p->win, p->plotheight + p->bnd.top, p->bnd.left);
	ops->uarrow(p, p->win, p->bnd.top, p->bnd.left);
	ops->rarrow(p, p->win, p->plotheight + p->bnd.top,
		    p->plotwidth + p->bnd.left);

	/* x/y axis labels */
	mvaddstr(p->bnd.top - 1, p->bnd.left, p->label_y);
	mvaddstr(p->plotheight + p->bnd.top + 1, p->plotwidth + p->bnd.left,
		 p->label_x);
}

static void paint_lgroup(struct plot *p, const struct lgroup *lg)
{
	double max = -DBL_MAX, min = DBL_MAX;
	int start = -1;
	int len = p->plotwidth * p->plotscaling;
	unsigned long shift = plot_shift(p);

	/**
	 * Since we are not drawing all the data for the entire curve, we need
	 * to first obtain the maximum and minimum values of the data for the
	 * plotting portion.
	 */
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;

		/**
		 * If the amount of data is insufficient to fill a screen, then
		 * @shift is meaningless, so clear it.
		 */
		const int _nvs =
			(l->count + p->plotscaling - 1) / p->plotscaling;
		if (p->plotwidth > _nvs) {
			p->plotshift = shift = 0;
		}

		start = l->count - len - shift;

		double _max, _min;
		if (p->curve_type == CURVE_TYPE_DELTA) {
			_max = line_range_delta_max(l, start, p->plotscaling,
						    len);
			_min = line_range_delta_min(l, start, p->plotscaling,
						    len);
		} else {
			_max = line_range_max(l, start, p->plotscaling, len);
			_min = line_range_min(l, start, p->plotscaling, len);
		}

		switch (p->curve_type) {
		case CURVE_TYPE_LOGARITHMIC:
			_max = signed_log_trans(_max);
			_min = signed_log_trans(_min);
			break;
		case CURVE_TYPE_LOGARITHMIC10:
			_max = signed_log10_trans(_max);
			_min = signed_log10_trans(_min);
			break;
		case CURVE_TYPE_EXPONENTIAL:
			_max = exp(_max);
			_min = exp(_min);
			break;
		case CURVE_TYPE_DELTA:
		case CURVE_TYPE_NONE:
		default:
			break;
		}

		max = max < _max ? _max : max;
		min = min > _min ? _min : min;
	}

	/* draw zero y line if needed */
	if (max > 0 && min < 0) {
		double h = get_plot_value_heigh(p, min, max, 0);
		attron(A_DIM);
		for (int i = 0; i < p->plotwidth - 1; i++)
			mvwprintw(p->win, h, p->bnd.left + 1 + i, "-");
		attroff(A_DIM);
	}

	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		__paint_line(p, lg, l, start, len, shift, max, min);
	}

	if (p->debug && lg->ops && lg->ops->plot_debug)
		lg->ops->plot_debug(lg, lg->ops->arg);
}

void __plot_debug_llabel(const struct lgroup *lg, int height)
{
	int i = 0;
	struct plot *p = lg->plot;

	for_each_line(lg, ln)
	{
		chtype color = getflavor(ln->color);
		attron(color);
		if (ln->count <= 0)
			mvprintw(i + height, p->bnd.left + 1, "%d: %s: %ld",
				 ln->id, ln->name, ln->count);
		else {
			char buf[64];

			mvprintw(i + height, p->bnd.left + 1,
				 "%d: %s: %ld %f x(%s) y(%lf~%lf)", ln->id,
				 ln->name, ln->count, ln->tail->v,
				 x_axis_range_str(lg->plot->x_type,
						  &ln->x_range, buf),
				 ln->min->v, ln->max->v);
		}
		attroff(color);
		i++;
	}
}

/**
 * need call werase() before, and call doupdate() after
 */
static void __paint_plot(struct plot *p)
{
	char hostname[64];
	char ts[128] = { 0 };
	time_t sec;
	struct tm *tm;

	__draw_title(p);
	__draw_axes(p);

	for_each_lgroup(p, lg)
	{
		paint_lgroup(p, lg);
	}

	sec = time(NULL);
	tm = localtime(&sec);
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\0';

	gethostname(hostname, sizeof(hostname));

	mvaddstr(p->height - 2, p->width - strlen(ts) - strlen(hostname) - 2,
		 ts);
	mvaddstr(p->height - 2, p->width - strlen(hostname) - 1, hostname);

	mvaddstr(p->height - 1, p->width - strlen(verstring) - 1, verstring);

	if (p->debug) {
		mvprintw(p->height - 2, 0, PLOT_INF0_FMT, PLOT_INF0_ARG(p));
		mvprintw(p->height - 1, 0, KEYBOARD_INF0_FMT,
			 KEYBOARD_INF0_ARG(p->kb));
	}

	move(0, 0);
}

/**
 * return the number of lines be created.
 */
int plot_create_lines(struct plot *p)
{
	int err = 0, n = 0;
	for_each_lgroup(p, lg)
	{
		if (!lg->ops || !lg->ops->create_lines)
			continue;
		err = lg->ops->create_lines(lg, lg->ops->arg);
		if (n < 0) {
			err = n;
			break;
		} else if (n > 0)
			n += err;
	}
	return err;
}

void plot_update_data(struct plot *p)
{
	for_each_lgroup(p, lg)
	{
		if (!lg->ops || !lg->ops->update_data)
			continue;
		lg->ops->update_data(lg, lg->ops->arg);
	}
}

static void __plot_redraw(struct plot *p)
{
	p->need_redraw = false;
	p->redrawcount++;

	erase();
	erase_dialog(&p->help);
	erase_dialog(&p->llabels);

	/**
	 * Handle the keyboard first, because 'reset' need before paint.
	 */
	if (p->kb->current_key != 0)
		exec_key_handler(p->kb, p->kb->current_key);

	__paint_plot(p);

	/**
	 * Paint the pop dialog window after curves.
	 */
	__paint_help_win(p, false);
	__paint_llabels_win(p, false);
}

void plot_redraw(struct plot *p)
{
	__plot_redraw(p);

	if (p->need_redraw) {
		plot_update_size(p, false);
		__plot_redraw(p);
	}

	wnoutrefresh(p->win);

	void fn(const struct id_handler *id, void *arg)
	{
		struct dialog *_d = id->arg;
		refresh_dialog(_d);
	}
	for_each_id(p->start_time_to_dialog, fn, NULL);

	doupdate();

	/* do some reset */
	plot_update_size(p, false);
	p->kb->current_key = 0;
}

static const char *key_helps[] = {
	KEY_HELP_h,    KEY_HELP_l,     KEY_HELP_q,     KEY_HELP_r,
	KEY_HELP_t,    KEY_HELP_v,     KEY_HELP_UP,    KEY_HELP_DOWN,
	KEY_HELP_LEFT, KEY_HELP_RIGHT, KEY_HELP_ENTER,
};

static int max_key_help_len(void)
{
	static int max = 0;
	if (max != 0)
		return max;

	for (int i = 0; i < ARRAY_SIZE(key_helps); i++) {
		int len = strlen(key_helps[i]);
		if (len > max)
			max = len;
	}
	return max;
}

/**
 * @return: return 0, 1, 2 if success, 0: without drawing, 1: create window,
 *          2: not create window.
 */
static int __paint_help_win(struct plot *p, bool init)
{
	int h, w, n, ret = 0;
	WINDOW *win = p->help.win;

	/**
	 * If no initialization flag is specified and the window is null, the
	 * drawing process is skipped.
	 */
	if (!init && !win)
		return 0;

	h = p->plotheight / 2 + p->bnd.top - ARRAY_SIZE(key_helps) / 2;
	w = p->plotwidth / 2 + p->bnd.left - max_key_help_len() / 2;
	n = sizeof(key_helps) / sizeof(key_helps[0]);

	if (init && win) {
		ret = 2;
	} else if (init && !win) {
		win = newwin(n + 2, max_key_help_len() + 2, h, w);
		new_dialog(&p->help, win);
		ret = 1;
	}

	wattron(win, colors[C_BLUE] | A_BOLD);
	set_win_border(win, p->win_border_type);
	mvwprintw(win, 0, 2, "[ HELP ]");
	for (int i = n - 1; i >= 0; i--)
		mvwprintw(win, i + 1, 1, "%s", key_helps[n - i - 1]);
	wattroff(win, colors[C_BLUE] | A_BOLD);

	return ret;
}

/**
 * @return: return 0, 1, 2 if success, 0: without drawing, 1: create window,
 *          2: not create window.
 */
static int __paint_llabels_win(struct plot *p, bool init)
{
	int ret = 0, i, nline = 0;
	int max_name_len = 0;
	WINDOW *win = p->llabels.win;
	const int n = 6;

	/**
	 * If no initialization flag is specified and the window is null, the
	 * drawing process is skipped.
	 */
	if (!init && !win)
		return 0;

	for_each_lgroup(p, lg)
	{
		nline += lg->count;
		for_each_line(lg, ln)
		{
			int len = strlen(ln->name);
			if (len > max_name_len)
				max_name_len = len;
		}
	}

	int h = p->plotheight / 2 + p->bnd.top - (nline / 2) - 1;
	int w = p->plotwidth / 2 + p->bnd.left - (max_name_len + n) / 2;

	if (init && win) {
		ret = 2;
	} else if (init && !win) {
		win = newwin(nline + 2, max_name_len + n + 3, h, w);
		new_dialog(&p->llabels, win);
		ret = 1;
	}

	i = 0;
	for_each_lgroup(p, lg)
	{
		for_each_line(lg, ln)
		{
			wattron(win, colors[ln->color] | A_BOLD);
			ln->ops->horizon(p, win, i + 1, 1, n);
			mvwprintw(win, i + 1, n + 1, " %s", ln->name);
			wattroff(win, colors[ln->color] | A_BOLD);
			i++;
		}
	}

	/**
	 * When the line type is set to 'unicode-area-chart', the legend window
	 * defaults to displaying lines that extend beyond its boundaries, as an
	 * area is being rendered. Consequently, the simplest current solution
	 * is to draw the box border last, thereby masking the excess lines.
	 */
	wattron(win, A_BOLD);
	set_win_border(win, p->win_border_type);
	mvwprintw(win, 0, 2, "[ LINES ]");
	wattroff(win, A_BOLD);

	return ret;
}

static void dialog_add_to_window(struct plot *p, struct dialog *d)
{
	unsigned long ns = nsecs();
	register_id(p->dialog_to_start_time, (long)d, NULL, (void *)ns);
	register_id(p->start_time_to_dialog, (long)ns, NULL, d);
}

static void dialog_del_from_window(struct plot *p, struct dialog *d)
{
	struct id_handler *id_h;
	unsigned long ns;

	id_h = find_id_handler(p->dialog_to_start_time, (long)d);
	if (!id_h)
		return;

	ns = (unsigned long)id_h->arg;

	unregister_id(p->dialog_to_start_time, (long)d);
	unregister_id(p->start_time_to_dialog, (long)ns);
}

static int win_dialog_timer_timeout_handler(long fd, int *reset_fd,
					    struct plot *p, struct dialog *d)
{
	plotcake_poll_del_fd(fd);
	unregister_id(NULL, fd);
	close(fd); /* new_timerfd() */
	*reset_fd = -1;

	/**
	 * Remove dialog from search-tree before delete dialog.
	 */
	dialog_del_from_window(p, d);

	del_dialog(d);
	return 0;
}

static int win_dialog_help_timer_timeout_handler(long fd, void *arg)
{
	struct plot *p = arg;
	return win_dialog_timer_timeout_handler(fd, &p->help_timerfd, p,
						&p->help);
}

static int win_dialog_llabels_timer_timeout_handler(long fd, void *arg)
{
	struct plot *p = arg;
	return win_dialog_timer_timeout_handler(fd, &p->llabels_timerfd, p,
						&p->llabels);
}

/**
 * Press key 'h', display the help info
 */
static int key_h_handler(int key, void *arg)
{
	struct plot *p = arg;
	__paint_help_win(p, true);
	if (p->help_timerfd != -1) {
		plotcake_poll_del_fd(p->help_timerfd);
		if (find_id_handler(NULL, p->help_timerfd)) {
			unregister_id(NULL, p->help_timerfd);
			close(p->help_timerfd);
		}
		p->help_timerfd = -1;
	}
	p->help_timerfd = new_timerfd(EXPIRED_USECS_HELP * 1000);
	plotcake_poll_add_fd(p->help_timerfd);
	register_id(NULL, p->help_timerfd,
		    win_dialog_help_timer_timeout_handler, p);
	dialog_del_from_window(p, &p->help);
	dialog_add_to_window(p, &p->help);
	return 0;
}

/**
 * Press key 'l', display the label for each line.
 */
static int key_l_handler(int key, void *arg)
{
	struct plot *p = arg;
	__paint_llabels_win(p, true);
	if (p->llabels_timerfd != -1) {
		plotcake_poll_del_fd(p->llabels_timerfd);
		if (find_id_handler(NULL, p->llabels_timerfd)) {
			unregister_id(NULL, p->llabels_timerfd);
			close(p->llabels_timerfd);
		}
		p->llabels_timerfd = -1;
	}
	p->llabels_timerfd = new_timerfd(EXPIRED_USECS_LLABEL * 1000);
	plotcake_poll_add_fd(p->llabels_timerfd);
	register_id(NULL, p->llabels_timerfd,
		    win_dialog_llabels_timer_timeout_handler, p);
	dialog_del_from_window(p, &p->llabels);
	dialog_add_to_window(p, &p->llabels);
	return 0;
}

/**
 * Press key 'r', reset plot
 */
static int key_r_handler(int key, void *arg)
{
	struct plot *p = arg;

	plot_scaling_init(p);
	p->plotshift = 0;
	return 0;
}

/**
 * Press key 't', change curve type
 */
static int key_t_handler(int key, void *arg)
{
	struct plot *p = arg;
	p->curve_type = (p->curve_type + 1) % CURVE_TYPE_MAX;
	return 0;
}

static int key_up_handler(int key, void *arg)
{
	plot_scaling_up(arg);
	return 0;
}

static int key_down_handler(int key, void *arg)
{
	plot_scaling_down(arg);
	return 0;
}

static int plot_shift_timer_timeout_handler(long fd, void *arg)
{
	struct plot *p = arg;
	p->plotshift = 0;
	p->plotshift_timerfd = -1;
	plotcake_poll_del_fd(fd);
	unregister_id(NULL, fd);
	close(fd); /* new_timerfd() */
	return 0;
}

static int create_shift_timerfd(struct plot *p)
{
	if (p->plotshift_timerfd == -1) {
		p->plotshift_timerfd = new_timerfd(EXPIRED_USECS_SHIFT * 1000);
		plotcake_poll_add_fd(p->plotshift_timerfd);
		register_id(NULL, p->plotshift_timerfd,
			    plot_shift_timer_timeout_handler, p);
	}
	return 0;
}

static int key_left_handler(int key, void *arg)
{
	struct plot *p = arg;
	plot_shift_left(p);
	create_shift_timerfd(p);
	return 0;
}

static int key_right_handler(int key, void *arg)
{
	struct plot *p = arg;
	plot_shift_right(p);
	create_shift_timerfd(p);
	return 0;
}

int plot_init(struct plot *p, struct keyboard *kb, const char *file, bool debug,
	      enum x_axis_type x_type, enum ltype_enum axis,
	      enum win_border_type win_border)
{
	int err = 0;

	if (!p || !kb)
		return -EINVAL;

	memset(p, 0, sizeof(struct plot));

	plot_scaling_init(p);

	p->debug = debug;
	p->axis_curve_type = axis;
	p->win_border_type = win_border;
	p->kb = kb;
	if (x_type < X_TIMEVAL || x_type > X_INDEX)
		return -EINVAL;
	p->x_type = x_type;
	p->plotshift_timerfd = -1;
	p->help_timerfd = -1;
	p->llabels_timerfd = -1;

	err = err ?: register_key_handler(kb, 'r', p, key_r_handler);
	err = err ?: register_key_handler(kb, 't', p, key_t_handler);
	err = err ?: register_key_handler(kb, 'h', p, key_h_handler);
	err = err ?: register_key_handler(kb, 'l', p, key_l_handler);
	err = err ?: register_key_handler(kb, KEY_UP, p, key_up_handler);
	err = err ?: register_key_handler(kb, KEY_DOWN, p, key_down_handler);
	err = err ?: register_key_handler(kb, KEY_RIGHT, p, key_right_handler);
	err = err ?: register_key_handler(kb, KEY_LEFT, p, key_left_handler);

	p->dialog_to_start_time = create_id_handler(NULL);
	p->start_time_to_dialog = create_id_handler(ID_CMP_ASCENDING_ORDER);

	if (file && !err)
		err = err ?: load_plot(p, file);

	return err;
}

int plot_destroy(struct plot *p)
{
	release_id_handle(p->dialog_to_start_time);
	release_id_handle(p->start_time_to_dialog);
	free(p->dialog_to_start_time);
	free(p->start_time_to_dialog);
	return 0;
}

/* Get memory bytes that plot already spent */
unsigned long plot_mem_size(const struct plot *p)
{
	unsigned long bytes = sizeof(struct plot);
	for_each_lgroup(p, lg)
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
