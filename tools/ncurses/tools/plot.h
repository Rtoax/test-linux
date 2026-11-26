// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <ncursesw/panel.h>
#include <stdarg.h>
#include <stdbool.h>
#include "config.h"
#include "keyboard.h"
#include "line.h"
#include "color.h"
#include "utils.h"
#include "dialog.h"
#include "id-handler.h"
#include "draw.h"
#include "scatter.h"

enum plot_type_enum {
	PLOT_TYPE_LINE,
	PLOT_TYPE_SCATTER,
};

struct plot {
	char title[128];
	char label_x[64];
	char label_y[64];

	bool debug;

	/* Current terminal size */
	int horizontal, vertical;
	/**
	 * The size of the drawing area, excluding boundaries, axes, line
	 * labels.
	 */
	int plotheight, plotwidth;
	/**
	 * The scaling factor for the drawing. The default value is 1, which
	 * means no scaling. It only supports zoomed-out display, similar to
	 * viewing "Global Routes" in map software.
	 */
	int plotscaling;
	/**
	 * As the amount of data increases, we may need to view historical data.
	 * @plotshift records the number of points moved to the left, and this
	 * number of points will be scaled by @plotscaling.
	 */
	unsigned long plotshift;
	int plotshift_timerfd;

	struct {
		int top, bottom, left, right;
/* Initial plot boundary */
#define BND_TOP(p) (p->vertical_plotting ? 7 : 1)
#define BND_BOTTOM(p) (p->vertical_plotting ? 6 : 4)
#define BND_LEFT(p) (p->vertical_plotting ? 3 : 7)
#define BND_RIGHT(p) (p->vertical_plotting ? 6 : 6)
	} bnd, bnd_prev_max;

	/**
	 * Generally, the x-axis is horizontal and the y-axis is vertical; when
	 * plotting in a vertical orientation, the axes are swapped.
	 */
	bool vertical_plotting;

	/**
	 * Although line and scatter plots are distinct types, the program does
	 * not know which one will be used during its initial setup phase;
	 * therefore, a 'struct' is used here instead of a 'union'.
	 */
	struct {
		enum plot_type_enum plot_type;
		struct line_plotting __line; /* PLOT_TYPE_LINE */
		struct scatter_plotting __scatter; /* PLOT_TYPE_SCATTER */
	};

	unsigned long redrawcount;

	enum math_trans_enum math_trans;

	struct keyboard *kb;

	/**
	 * When something happens internally, such as a change in the drawing
	 * boundary, we need to redraw, rather than letting external conditions
	 * trigger a redraw.
	 */
	bool need_redraw;

	enum draw_ops_type_enum axis_curve_type;

#ifdef DEBUG
#define PLOT_DEBUG0_DIALOG_FMT ", dialog:%d:%d:%d:%d"
#define PLOT_DEBUG0_DIALOG_ARG(p)                                          \
	, id_handle_count(p->dialog_to_start_time),                        \
		id_handle_count(p->start_time_to_dialog), p->help_timerfd, \
		p->llabels_timerfd
#define PLOT_DEBUG0_X_FMT ", %s:%d"
#define PLOT_DEBUG0_X_ARG(p) , ln_x_type_str(p->__line.x_type), p->__line.x_type
#define PLOT_DEBUG0_BND_FMT ", [(%d,%d,%d,%d)(%d,%d,%d,%d)]"
#define PLOT_DEBUG0_BND_ARG(p)                                  \
	, p->bnd.top, p->bnd.bottom, p->bnd.left, p->bnd.right, \
		p->bnd_prev_max.top, p->bnd_prev_max.bottom,    \
		p->bnd_prev_max.left, p->bnd_prev_max.right
#else
#define PLOT_DEBUG0_DIALOG_FMT
#define PLOT_DEBUG0_DIALOG_ARG(p)
#define PLOT_DEBUG0_X_FMT
#define PLOT_DEBUG0_X_ARG(p)
#define PLOT_DEBUG0_BND_FMT
#define PLOT_DEBUG0_BND_ARG(p)
#endif

#define PLOT_INF0_FMT                                          \
	"plot(redraw=%ld, %.3f MiB, win[%d,%d], plot[%d,%d], " \
	"scale %d, shft %ld/%ld" PLOT_DEBUG0_X_FMT             \
		PLOT_DEBUG0_DIALOG_FMT PLOT_DEBUG0_BND_FMT ")"
#define PLOT_INF0_ARG(p)                                                     \
	p->redrawcount, plot_mem_size(p) * 1. / MiB, plot_height(p),         \
		plot_width(p), p->plotheight, p->plotwidth, p->plotscaling,  \
		p->plotshift,                                                \
		plot_shift(p) PLOT_DEBUG0_X_ARG(p) PLOT_DEBUG0_DIALOG_ARG(p) \
			PLOT_DEBUG0_BND_ARG(p)

	WINDOW *win; /* equal to stdscr */

	struct dialog help, llabels;
	int help_timerfd, llabels_timerfd;

	/**
	 * We can use the dialog object to retrieve the timestamp of its last
	 * display and locate specific dialogs based on that time. By sorting
	 * based on time, we can control the rendering order (z-axis-order) of
	 * the dialogs.
	 */
	id_handle_t dialog_to_start_time;
	id_handle_t start_time_to_dialog;

	enum win_border_type win_border_type;
};

#define plot_scaling_init(p)                          \
	do {                                          \
		struct plot *___p = (struct plot *)p; \
		___p->plotscaling = 1;                \
	} while (0)

#define plot_scaling_up(p)                            \
	do {                                          \
		struct plot *___p = (struct plot *)p; \
		___p->plotscaling++;                  \
	} while (0)
#define plot_scaling_down(p)                          \
	do {                                          \
		struct plot *___p = (struct plot *)p; \
		if (___p->plotscaling > 1) {          \
			___p->plotscaling--;          \
		}                                     \
	} while (0)

#define plot_shift_left(p)                            \
	do {                                          \
		struct plot *___p = (struct plot *)p; \
		___p->plotshift++;                    \
	} while (0)

#define plot_shift_right(p)                           \
	do {                                          \
		struct plot *___p = (struct plot *)p; \
		if (___p->plotshift >= 1)             \
			___p->plotshift--;            \
	} while (0)

#define plot_shift(p)                                 \
	({                                            \
		struct plot *___p = (struct plot *)p; \
		___p->plotshift * ___p->plotscaling;  \
	})

static inline void set_plot_title(struct plot *p, const char *title)
{
	/* already set title */
	if (p->title[0] != '\0')
		return;
	snprintf(p->title, sizeof(p->title) - 1, "%s", title);
}

const char *get_plot_xlabel(const struct plot *p);

static inline void set_plot_xlabel(struct plot *p, const char *label)
{
	/* already set x label */
	if (p->label_x[0] != '\0')
		return;
	snprintf(p->label_x, sizeof(p->label_x) - 1, "%s", label);
}

static inline void set_plot_ylabel(struct plot *p, const char *label)
{
	/* already set y label */
	if (p->label_y[0] != '\0')
		return;
	snprintf(p->label_y, sizeof(p->label_y) - 1, "%s", label);
}

int plot_init(struct plot *p, struct keyboard *kb, const char *file, bool debug,
	      enum ln_x_type x_type, enum draw_ops_type_enum axis,
	      enum win_border_type win_border);
int plot_destroy(struct plot *p);
unsigned long plot_mem_size(const struct plot *p);

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

void plot_update_size(struct plot *p, bool init);

void plot_update_lines(struct plot *p);
void plot_redraw(struct plot *p);

int plot_height(const struct plot *p);
int plot_width(const struct plot *p);

int get_plot_value_heigh(const struct plot *p, double min, double max,
			 double v);

bool enabled_stacked_line_chart(const struct plot *p);
void set_stacked_line_chart(struct plot *p, bool t);
