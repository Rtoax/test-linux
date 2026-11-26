// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <ncursesw/panel.h>

enum data_color_enum {
	C_GREEN,
	C_RED,
	C_CYAN,
	C_WHITE,
	C_MAGENTA,
	C_BLUE,
	C_YELLOW,
	C_MAX,
	C_UNKNOWN = C_MAX,
};

void init_flavor(bool transparent_bg);
chtype getflavor(enum data_color_enum color);

const char *color_name(enum data_color_enum e);
int enqueue_data_color(enum data_color_enum c);
enum data_color_enum dequeue_data_color(void);
void reset_data_color_queue(void);
int get_nr_data_colors(void);
int data_color_print_names(FILE *fp);
enum data_color_enum data_color_name2num(const char *name);
bool data_color_hasname(const char *name);
enum data_color_enum nextdata_color(enum data_color_enum c);
