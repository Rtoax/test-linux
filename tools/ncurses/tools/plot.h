// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include "config.h"
#include "keyboard.h"
#include "value.h"
#include "utils.h"

/**
 * Scaling plotting values, different from @plotscaling.
 */
enum numerical_scaling {
	NS_NONE = 0,
	NS_LOGARITHMIC,
	NS_LOGARITHMIC10,
	NS_EXPONENTIAL,
	NS_MAX,
};

struct plot {
	char *title;
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
	struct {
		int top, bottom, left, right;
	} bnd, bnd_prev_max;
	struct lgroup *lghead, *lgtail;

	int lgcount;
	unsigned long redrawcount;

	enum numerical_scaling v_scaling;

	struct keyboard *kb;

	/**
	 * If this value is greater than the current time, help information
	 * will be displayed.
	 */
	unsigned long help_expired_usec;
	unsigned long llabel_expired_usec;

	/**
	 * When something happens internally, such as a change in the drawing
	 * boundary, we need to redraw, rather than letting external conditions
	 * trigger a redraw.
	 */
	bool need_redraw;

#define PLOT_INF0_FMT \
	"plot: redraw=%ld mem(%.3f MiB) win(%d,%d) max(%d,%d) plot(%d,%d) scale(%d)"
#define PLOT_INF0_ARG(p)                                                \
	p->redrawcount, plot_mem_size(p) * 1. / 1024 / 1024, p->height, \
		p->width, p->heightmax, p->widthmax, p->plotheight,     \
		p->plotwidth, p->plotscaling
};

#define for_each_lg(plt, iter)                                           \
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

void plot_init(struct plot *p, struct keyboard *k);
unsigned long plot_mem_size(const struct plot *p);

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

int plot_add_lgrp(struct plot *p, struct lgroup *lg, void *lg_ops_arg);

void plot_update_size(struct plot *p, bool init);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);

void plot_create_data(struct plot *p);
void plot_update_data(struct plot *p);
void plot_help(const struct plot *p);
void plot_llabel(const struct plot *p);
void plot_redraw(struct plot *p, bool debug);

void init_flavor(void);
