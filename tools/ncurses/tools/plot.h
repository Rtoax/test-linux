// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include "config.h"
#include "keyboard.h"
#include "line.h"
#include "utils.h"

/**
 * Scaling plotting values, different from @plotscaling.
 */
enum curve_type {
	CURVE_TYPE_NONE = 0,
	CURVE_TYPE_LOGARITHMIC,
	CURVE_TYPE_LOGARITHMIC10,
	CURVE_TYPE_EXPONENTIAL,
	CURVE_TYPE_DELTA,
	CURVE_TYPE_MAX,
};

struct plot {
	char title[128];
	char *label_x;
	char *label_y;
	/**
	 * max indicates the maximum value your terminal has reached during the
	 * entire program run (you can use the mouse to drag and adjust the
	 * terminal size).
	 *
	 * `heightmax` represents the maximum height of the terminal window, and
	 * `widthmax` represents the maximum width of the terminal window.
	 */
	int heightmax, widthmax;
	/* Current terminal size */
	int height, width;
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
	struct {
		int top, bottom, left, right;
	} bnd, bnd_prev_max;
	struct lgroup *lghead, *lgtail;

	int lgcount;
	unsigned long redrawcount;

	enum curve_type curve_type;

	struct keyboard *kb;

	/**
	 * Some information needs to be displayed for a longer time, so we set
	 * a timeout.
	 */
	struct {
		unsigned long help, llabel, shift;
	} expired_usec;

	/**
	 * When something happens internally, such as a change in the drawing
	 * boundary, we need to redraw, rather than letting external conditions
	 * trigger a redraw.
	 */
	bool need_redraw;

#define PLOT_INF0_FMT                                                      \
	"plot(redraw=%ld, %.3f MiB, win[%d,%d], max[%d,%d], plot[%d,%d], " \
	"scale %d, shft %ld/%ld)"
#define PLOT_INF0_ARG(p)                                                \
	p->redrawcount, plot_mem_size(p) * 1. / 1024 / 1024, p->height, \
		p->width, p->heightmax, p->widthmax, p->plotheight,     \
		p->plotwidth, p->plotscaling, p->plotshift, plot_shift(p)
};

#define for_each_lgroup(plt, iter)                                       \
	for (struct lgroup *iter = ((struct plot *)(plt))->lghead; iter; \
	     iter = iter->next)

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

int plot_init(struct plot *p, struct keyboard *k, const char *file, bool debug);
unsigned long plot_mem_size(const struct plot *p);

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

int plot_add_lgroup(struct plot *p, struct lgroup *lg, void *lg_ops_arg);
struct lgroup *plot_lgroup(const struct plot *p, int idx);

void plot_update_size(struct plot *p, bool init);

void plot_create_data(struct plot *p);
void plot_update_data(struct plot *p);
void plot_help(const struct plot *p);
void plot_llabel(const struct plot *p);
void plot_redraw(struct plot *p, bool debug);

void init_flavor(void);
chtype getflavor(enum lcolor_enum color);

void __plot_debug_llabel(const struct lgroup *lg, int height);
