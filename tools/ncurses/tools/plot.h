// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include "config.h"
#include "value.h"

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
	/* The size of the drawing area (excluding boundaries, axes, etc.) */
	int plotheight, plotwidth;
	struct {
		int top, bottom, left, right;
	} bnd, bnd_prev_max;
	struct lgroup *lghead, *lgtail;

	int lgcount;
	unsigned long redrawcount;

	/* Scaling plotting */
	enum {
		T_NONE = 0,
		T_LOGARITHMIC,
		T_LOGARITHMIC10,
		T_EXPONENTIAL,
	} v_scaling;

	/**
	 * record previous keyboard event.
	 */
	struct {
		unsigned long count;
		unsigned long key_left_count, key_right_count;
		unsigned long key_h_count, key_l_count, key_enter_count;
		int key; /* read from STDIN/getch() or /dev/tty */
	} keyboard;
};

#define for_each_lg(plt, iter)                                           \
	for (struct lgroup *iter = ((struct plot *)(plt))->lghead; iter; \
	     iter = iter->next)

void plot_init(struct plot *p);

#define plot_warning(p, fmt...) __plot_warning(p, fmt)
void __plot_warning(const struct plot *p, char *fmt, ...);

int plot_add(struct plot *p, struct lgroup *lg, void *lg_ops_arg);

void plot_update_size(struct plot *p, bool init);
void plot_draw_axes(const struct plot *p);
void plot_draw_title(const struct plot *p);

void plot_create_data(struct plot *p);
void plot_update_data(struct plot *p);
void plot_redraw(struct plot *p, bool debug);

void init_flavor(void);
