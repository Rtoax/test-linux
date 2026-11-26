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
#include "color.h"

static const char *verstring = GIT_REPO " " MY_VERSION;

static int __paint_help_win(struct plot *p, bool init);
static int __paint_llabels_win(struct plot *p, bool init);

int plot_height(const struct plot *p)
{
	return p->vertical_plotting ? p->horizontal : p->vertical;
}

int plot_width(const struct plot *p)
{
	return p->vertical_plotting ? p->vertical : p->horizontal;
}

void plot_update_size(struct plot *p, bool init)
{
	if (init) {
		p->bnd.top = BND_TOP(p);
		p->bnd.bottom = BND_BOTTOM(p);
		p->bnd.left = BND_LEFT(p);
		p->bnd.right = BND_RIGHT(p);
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
		p->bnd.top = p->bnd.top > p->bnd_prev_max.top ?
				     p->bnd.top :
				     p->bnd_prev_max.top;
		p->bnd.bottom = p->bnd.bottom > p->bnd_prev_max.bottom ?
					p->bnd.bottom :
					p->bnd_prev_max.bottom;
	}

	getmaxyx(p->win, p->vertical, p->horizontal);

	p->plotheight = plot_height(p) - p->bnd.bottom - p->bnd.top;
	p->plotwidth = plot_width(p) - p->bnd.left - p->bnd.right;

	/**
	 * When refreshing or modifying the drawing type, the boundary size may
	 * change. We need to reset the maximum value to avoid excessive blank
	 * space at the boundary.
	 */
	switch (p->kb->current_key) {
	case 'r':
	case 's':
	case 't':
	case 'x': /* 'x' need update in vertical plotting mode */
		p->bnd.top = p->bnd_prev_max.top;
		p->bnd.bottom = p->bnd_prev_max.bottom;
		p->bnd.left = p->bnd_prev_max.left;
		p->bnd.right = p->bnd_prev_max.right;
		p->need_redraw = true;
		break;
	}

	p->bnd_prev_max.top = BND_TOP(p);
	p->bnd_prev_max.bottom = BND_BOTTOM(p);
	p->bnd_prev_max.left = BND_LEFT(p);
	p->bnd_prev_max.right = BND_RIGHT(p);
}

void __plot_warning(const struct plot *p, char *fmt, ...)
{
	char buff[256];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buff, 256, fmt, va);
	va_end(va);
	attron(getflavor(C_RED) | A_BOLD);
	mvaddstr(plot_height(p) / 2, (plot_width(p) - strlen(buff)) / 2, buff);
	attroff(getflavor(C_RED) | A_BOLD);
}

int get_plot_value_heigh(const struct plot *p, double min, double max, double v)
{
	double span = .0f, diff = .0f;
	int ret;

	if (max == min || max == 0.0 || max < min) {
		diff = 0;
		span = 1;
	} else {
		diff = v - min;
		span = max - min;
	}

	int val = diff * (p->plotheight - 2) / span;

	if (p->vertical_plotting) {
		ret = p->bnd.bottom + 1 + val;
	} else {
		ret = p->plotheight + p->bnd.top - 1 - val;
	}

	return ret;
}

bool enabled_stacked_line_chart(const struct plot *p)
{
	if (p->plot_type == PLOT_TYPE_LINE)
		return p->__line.enable_stacked_line_chart;
	return false;
}

void set_stacked_line_chart(struct plot *p, bool t)
{
	if (p->plot_type == PLOT_TYPE_LINE)
		p->__line.enable_stacked_line_chart = t;
}

static void __draw_title(const struct plot *p)
{
	char buf[sizeof(p->title) + 128];
	int col = p->vertical_plotting ? plot_height(p) : plot_width(p);

	if (p->math_trans == MATH_TRANS_LOGARITHMIC)
		snprintf(buf, sizeof(buf), "%s (signed logarithmic)", p->title);
	else if (p->math_trans == MATH_TRANS_LOGARITHMIC10)
		snprintf(buf, sizeof(buf), "%s (base-10 signed logarithmic)",
			 p->title);
	else if (p->math_trans == MATH_TRANS_EXPONENTIAL)
		snprintf(buf, sizeof(buf), "%s (base-e exponential)", p->title);
	else if (p->math_trans == MATH_TRANS_DELTA &&
		 !enabled_stacked_line_chart(p))
		snprintf(buf, sizeof(buf), "%s (delta)", p->title);
	else
		snprintf(buf, sizeof(buf), "%s", p->title);

	if (enabled_stacked_line_chart(p)) {
		strncat(buf, "[stacked]", sizeof(buf) - strlen(buf) - 1);
	}

	wattron(p->win, getflavor(C_BLUE) | A_BOLD);
	mvaddstr(0, (col - strlen(buf)) / 2, buf);
	wattroff(p->win, getflavor(C_BLUE) | A_BOLD);

	if (p->debug) {
		char buf2[64];
		snprintf(buf2, sizeof(buf2), "<pid:%d>", getpid());
		mvaddstr(1, (col - strlen(buf2)) / 2, buf2);
	}
}

const char *get_plot_xlabel(const struct plot *p)
{
	return p->label_x[0] != '\0' ?
		       p->label_x :
		       (p->plot_type == PLOT_TYPE_LINE ?
				ln_x_label_str(p->__line.x_type) :
				"x" /* TODO: for scatter */);
}

static void __draw_axes(const struct plot *p)
{
	const struct draw_operations *ops =
		draw_ops_type2ops(p->axis_curve_type);
	const char *labelx = get_plot_xlabel(p);

	if (p->vertical_plotting) {
		/* x axis */
		ops->vertical(p, p->win, p->bnd.left, p->bnd.bottom,
			      p->plotwidth);
		ops->darrow(p, p->win, p->plotwidth + p->bnd.left,
			    p->bnd.bottom);
		/* y axis */
		ops->horizon(p, p->win, p->bnd.left, p->bnd.bottom,
			     p->plotheight);
		ops->rarrow(p, p->win, p->bnd.left,
			    p->plotheight + p->bnd.bottom);
		/* [0,0] corner */
		ops->ulcorner(p, p->win, p->bnd.left, p->bnd.bottom);
		/* y axis labels */
		mvaddstr(p->bnd.left - 2,
			 p->plotheight + p->bnd.bottom + p->bnd.top -
				 strlen(p->label_y),
			 p->label_y);
		/* x axis labels */
		mvaddstr(p->plotwidth + p->bnd.left + 1, 1, labelx);
	} else {
		/* x axis */
		ops->horizon(p, p->win, p->plotheight + p->bnd.top, p->bnd.left,
			     p->plotwidth);
		ops->rarrow(p, p->win, p->plotheight + p->bnd.top,
			    p->plotwidth + p->bnd.left);
		/* y axis */
		ops->vertical(p, p->win, p->bnd.top, p->bnd.left,
			      p->plotheight);
		ops->uarrow(p, p->win, p->bnd.top, p->bnd.left);
		/* [0,0] corner */
		ops->llcorner(p, p->win, p->plotheight + p->bnd.top,
			      p->bnd.left);

		/* x/y axis labels */
		mvaddstr(p->bnd.top - 1, p->bnd.left, p->label_y);
		/**
		 * If an x-axis label is set, display it directly; otherwise,
		 * adjust the x-axis label based on the type.
		 */
		mvaddstr(p->plotheight + p->bnd.top + 1,
			 p->plotwidth + p->bnd.left, labelx);
	}
}

static void __draw_footer(const struct plot *p)
{
	char hostname[64];
	char ts[128] = { 0 };
	time_t sec;
	struct tm *tm;
	int h, w;

	sec = time(NULL);
	tm = localtime(&sec);
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\0';

	gethostname(hostname, sizeof(hostname));

	if (p->vertical_plotting) {
		h = plot_width(p);
		w = plot_height(p);
	} else {
		h = plot_height(p);
		w = plot_width(p);
	}

	mvaddstr(h - 2, w - strlen(ts) - strlen(hostname) - 2, ts);
	mvaddstr(h - 2, w - strlen(hostname) - 1, hostname);

	mvaddstr(h - 1, w - strlen(verstring) - 1, verstring);

	if (p->debug) {
		mvprintw(h - 2, 0, PLOT_INF0_FMT, PLOT_INF0_ARG(p));
		mvprintw(h - 1, 0, KEYBOARD_INF0_FMT, KEYBOARD_INF0_ARG(p->kb));
	}
}

static void paint_lgroup(struct plot *p, const struct lgroup *lg)
{
	double max, min, max_stacked, min_stacked;
	int start = -1;
	int draw_len = p->plotwidth * p->plotscaling;
	unsigned long shift = plot_shift(p);
	bool first_line = true;
	unsigned long max_nr_values = 0;

	max = max_stacked = -DBL_MAX;
	min = min_stacked = DBL_MAX;

	/**
	 * Since we are not drawing all the data for the entire curve, we need
	 * to first obtain the maximum and minimum values of the data for the
	 * plotting portion.
	 */
	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;

		if (max_nr_values < l->count)
			max_nr_values = l->count;

		/**
		 * If the amount of data is insufficient to fill a screen, then
		 * @shift is meaningless, so clear it.
		 */
		const int _nvs =
			(l->count + p->plotscaling - 1) / p->plotscaling;
		if (p->plotwidth > _nvs) {
			p->plotshift = shift = 0;
		}

		start = l->count - draw_len - shift;

		double _max, _min;
		if (p->math_trans == MATH_TRANS_DELTA &&
		    !enabled_stacked_line_chart(p)) {
			_max = line_range_delta_max(l, start, p->plotscaling,
						    draw_len);
			_min = line_range_delta_min(l, start, p->plotscaling,
						    draw_len);
		} else {
			_max = line_range_max(l, start, p->plotscaling,
					      draw_len);
			_min = line_range_min(l, start, p->plotscaling,
					      draw_len);
		}

		switch (p->math_trans) {
		case MATH_TRANS_LOGARITHMIC:
			_max = signed_log_trans(_max);
			_min = signed_log_trans(_min);
			break;
		case MATH_TRANS_LOGARITHMIC10:
			_max = signed_log10_trans(_max);
			_min = signed_log10_trans(_min);
			break;
		case MATH_TRANS_EXPONENTIAL:
			_max = exp(_max);
			_min = exp(_min);
			break;
		case MATH_TRANS_DELTA:
		case MATH_TRANS_NONE:
		default:
			break;
		}

		if (enabled_stacked_line_chart(p)) {
			if (first_line) {
				max_stacked = _max;
				min_stacked = _min;
				first_line = false;
			} else {
				max_stacked += _max;
				if (min_stacked > min_stacked + _min) {
					min_stacked += _min;
				}
			}
		}

		max = max < _max ? _max : max;
		min = min > _min ? _min : min;
	}

	/* draw zero y line if needed */
	if (enabled_stacked_line_chart(p)) {
		paint_y0_line(p, min_stacked, max_stacked);
	} else {
		paint_y0_line(p, min, max);
	}

	double *stacked_line = NULL;
	if (enabled_stacked_line_chart(p)) {
		size_t sz = max_nr_values * sizeof(double);
		stacked_line = (double *)malloc(sz);
		memset(stacked_line, 0x0, sz);
	}

	if (enabled_stacked_line_chart(p)) {
		first_line = true;
	}

	for_each_line(lg, l)
	{
		if (l->count <= 0)
			continue;
		__paint_line(p, lg, l, start, draw_len, shift,
			     enabled_stacked_line_chart(p) ? max_stacked : max,
			     enabled_stacked_line_chart(p) ? min_stacked : min,
			     stacked_line, first_line);
		first_line = false;
	}

	if (enabled_stacked_line_chart(p)) {
		free(stacked_line);
	}

	if (p->debug && lg->ops && lg->ops->plot_debug)
		lg->ops->plot_debug(lg, lg->ops->arg);
}

/**
 * need call werase() before, and call doupdate() after
 */
static void __paint_plot(struct plot *p)
{
	__draw_title(p);
	__draw_axes(p);

	for_each_lgroup(&p->__line, lg)
	{
		paint_lgroup(p, lg);
	}

	__draw_footer(p);

	move(0, 0);
}

/**
 * return the number of lines be created.
 */
int plot_create_lines(struct plot *p)
{
	int err = 0, n = 0;
	for_each_lgroup(&p->__line, lg)
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
	for_each_lgroup(&p->__line, lg)
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

static void __redraw_id_fn(const struct id_handler *id, void *arg)
{
	struct dialog *_d = id->arg;
	refresh_dialog(_d);
}

void plot_redraw(struct plot *p)
{
	__plot_redraw(p);

	if (p->need_redraw) {
		plot_update_size(p, false);
		__plot_redraw(p);
	}

	wnoutrefresh(p->win);

	for_each_id(p->start_time_to_dialog, __redraw_id_fn, NULL);

	doupdate();

	/* do some reset */
	plot_update_size(p, false);
	p->kb->current_key = 0;
}

static const char *key_helps[] = {
	KEY_HELP_h,	KEY_HELP_l,    KEY_HELP_q,    KEY_HELP_r,
	KEY_HELP_s,	KEY_HELP_t,    KEY_HELP_v,    KEY_HELP_x,
	KEY_HELP_UP,	KEY_HELP_DOWN, KEY_HELP_LEFT, KEY_HELP_RIGHT,
	KEY_HELP_ENTER,
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

	if (p->vertical_plotting) {
		h = p->plotwidth / 2 + p->bnd.left - ARRAY_SIZE(key_helps) / 2;
		w = p->plotheight / 2 + p->bnd.bottom - max_key_help_len() / 2;
	} else {
		h = p->plotheight / 2 + p->bnd.top - ARRAY_SIZE(key_helps) / 2;
		w = p->plotwidth / 2 + p->bnd.left - max_key_help_len() / 2;
	}

	n = sizeof(key_helps) / sizeof(key_helps[0]);

	if (init && win) {
		ret = 2;
	} else if (init && !win) {
		win = newwin(n + 2, max_key_help_len() + 2, h, w);
		new_dialog(&p->help, win);
		ret = 1;
	}

	wattron(win, getflavor(C_BLUE) | A_BOLD);
	set_win_border(win, p->win_border_type);
	mvwprintw(win, 0, 2, "[ HELP ]");
	for (int i = n - 1; i >= 0; i--)
		mvwprintw(win, i + 1, 1, "%s", key_helps[n - i - 1]);
	wattroff(win, getflavor(C_BLUE) | A_BOLD);

	return ret;
}

/**
 * @return: return 0, 1, 2 if success, 0: without drawing, 1: create window,
 *          2: not create window.
 */
static int __paint_llabels_win(struct plot *p, bool init)
{
	int ret = 0, i, nline = 0, h, w;
	int max_name_len = 0;
	WINDOW *win = p->llabels.win;
	const int n = 6;

	/**
	 * If no initialization flag is specified and the window is null, the
	 * drawing process is skipped.
	 */
	if (!init && !win)
		return 0;

	for_each_lgroup(&p->__line, lg)
	{
		nline += lg->count;
		for_each_line(lg, ln)
		{
			int len = strlen(ln->name);
			if (len > max_name_len)
				max_name_len = len;
		}
	}

	if (p->vertical_plotting) {
		h = p->plotwidth / 2 + p->bnd.left - (nline / 2) - 1;
		w = p->plotheight / 2 + p->bnd.bottom - (max_name_len + n) / 2;
	} else {
		h = p->plotheight / 2 + p->bnd.top - (nline / 2) - 1;
		w = p->plotwidth / 2 + p->bnd.left - (max_name_len + n) / 2;
	}

	if (init && win) {
		ret = 2;
	} else if (init && !win) {
		win = newwin(nline + 2, max_name_len + n + 3, h, w);
		new_dialog(&p->llabels, win);
		ret = 1;
	}

	i = 0;
	for_each_lgroup(&p->__line, lg)
	{
		for_each_line(lg, ln)
		{
			wattron(win, getflavor(ln->color) | A_BOLD);
			ln->ops->horizon(p, win, i + 1, 1, n);
			mvwprintw(win, i + 1, n + 1, " %s", ln->name);
			wattroff(win, getflavor(ln->color) | A_BOLD);
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
 * Press key 's', enable/disable stacked line chart
 */
static int key_s_handler(int key, void *arg)
{
	struct plot *p = arg;
	set_stacked_line_chart(p, !enabled_stacked_line_chart(p));
	return 0;
}

/**
 * Press key 't', change curve type
 */
static int key_t_handler(int key, void *arg)
{
	struct plot *p = arg;
	p->math_trans = (p->math_trans + 1) % MATH_TRANS_MAX;
	return 0;
}

/**
 * Press key 'x', change x axis type
 */
static int key_x_handler(int key, void *arg)
{
	struct plot *p = arg;
	p->__line.x_type = (p->__line.x_type + 1) % X_AXIS_TYPE_MAX;
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
	      enum ln_x_type x_type, enum draw_ops_type_enum axis,
	      enum win_border_type win_border)
{
	int err = 0;

	if (!p || !kb)
		return -EINVAL;

	memset(p, 0, sizeof(struct plot));

	plot_scaling_init(p);

	p->plot_type = PLOT_TYPE_LINE;
	p->debug = debug;
	p->axis_curve_type = axis;
	p->win_border_type = win_border;
	p->kb = kb;
	if (x_type < X_TIMEVAL || x_type > X_INDEX)
		return -EINVAL;
	p->__line.x_type = x_type;
	p->plotshift_timerfd = -1;
	p->help_timerfd = -1;
	p->llabels_timerfd = -1;

	err = err ?: register_key_handler(kb, 'r', p, key_r_handler);
	err = err ?: register_key_handler(kb, 's', p, key_s_handler);
	err = err ?: register_key_handler(kb, 't', p, key_t_handler);
	err = err ?: register_key_handler(kb, 'h', p, key_h_handler);
	err = err ?: register_key_handler(kb, 'l', p, key_l_handler);
	err = err ?: register_key_handler(kb, 'x', p, key_x_handler);
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
	for_each_lgroup(&p->__line, lg)
	{
		bytes += sizeof(struct lgroup);
		for_each_line(lg, ln)
		{
			bytes += sizeof(struct line);
			bytes += ln->count * sizeof(struct ln_value);
		}
	}
	return bytes;
}
