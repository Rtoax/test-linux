// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <stdio.h>
#include "config.h"

enum draw_ops_type_enum {
	LINE_TYPE_DEFAULT = 0,
	LINE_TYPE_BOLD_UNICODE = LINE_TYPE_DEFAULT,
	LINE_TYPE_BOLD_UNICODE_DASHED,
	LINE_TYPE_BOLDBOLD_UNICODE,
	LINE_TYPE_THIN_UNICODE,
	LINE_TYPE_THIN_UNICODE_DASHED,
	LINE_TYPE_AREA_CHART_UNICODE,
	LINE_TYPE_UTF8,
	LINE_TYPE_HEART_UNICODE,
	LINE_TYPE_MAX,
};

struct draw_operations {
	const char name[64];
	void (*horizon)(const struct plot *p, WINDOW *win, int y, int x, int n);
	void (*vertical)(const struct plot *p, WINDOW *win, int y, int x,
			 int n);
	/* upper left corner */
	void (*ulcorner)(const struct plot *p, WINDOW *win, int y, int x);
	/* lower left corner */
	void (*llcorner)(const struct plot *p, WINDOW *win, int y, int x);
	/* upper right corner */
	void (*urcorner)(const struct plot *p, WINDOW *win, int y, int x);
	/* lower right corner */
	void (*lrcorner)(const struct plot *p, WINDOW *win, int y, int x);
	/* up arrow */
	void (*uarrow)(const struct plot *p, WINDOW *win, int y, int x);
	/* down arrow */
	void (*darrow)(const struct plot *p, WINDOW *win, int y, int x);
	/* right arrow */
	void (*rarrow)(const struct plot *p, WINDOW *win, int y, int x);
};

int draw_ops_print_names(FILE *fp);
bool draw_ops_has_name(const char *name);
enum draw_ops_type_enum draw_ops_name2type(const char *name);
const struct draw_operations *draw_ops_type2ops(enum draw_ops_type_enum t);
const struct draw_operations *draw_ops_name2ops(const char *name);
const char *draw_ops_type2name(enum draw_ops_type_enum t);

int enqueue_draw_ops(enum draw_ops_type_enum t);
enum draw_ops_type_enum dequeue_draw_ops(void);
int get_nr_draw_ops(void);

void reset_draw_ops_queue(void);
