// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "config.h"
#include "color.h"

static chtype colors[C_MAX] = { 0 };

static enum data_color_enum *data_colors = NULL;
static int nr_data_colors = 0;
static int idx_data_colors = -1;

const char *color_names[C_MAX] = {
	[C_GREEN] = "green",   [C_RED] = "red",		[C_CYAN] = "cyan",
	[C_WHITE] = "white",   [C_MAGENTA] = "magenta", [C_BLUE] = "blue",
	[C_YELLOW] = "yellow",
};

void init_flavor(bool transparent_bg)
{
	if (has_colors()) {
		int bg = COLOR_BLACK;
		start_color();

		if (transparent_bg) {
			use_default_colors();
			bg = -1;
		}
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

chtype getflavor(enum data_color_enum color)
{
	return colors[color];
}

int enqueue_data_color(enum data_color_enum c)
{
	if (c >= C_MAX || c < C_GREEN)
		return -EINVAL;

	nr_data_colors++;
	data_colors = (enum data_color_enum *)realloc(
		data_colors, nr_data_colors * sizeof(enum data_color_enum));
	data_colors[nr_data_colors - 1] = c;
	return 0;
}

int get_nr_data_colors(void)
{
	return nr_data_colors;
}

/**
 * @return: return C_UNKNOWN if not enough.
 */
enum data_color_enum dequeue_data_color(void)
{
	if (nr_data_colors <= 0 || idx_data_colors >= nr_data_colors)
		return C_UNKNOWN;
	return data_colors[++idx_data_colors];
}

enum data_color_enum nextdata_color(enum data_color_enum c)
{
	enum data_color_enum color = dequeue_data_color();
	if (color != C_UNKNOWN)
		return color;
	return c % C_MAX;
}

const char *color_name(enum data_color_enum e)
{
	if (e >= 0 && e < C_MAX)
		return color_names[e];
	return "unknown";
}

int data_color_print_names(FILE *fp)
{
	for (int i = 0; i < C_MAX; i++) {
		fprintf(fp, "\t%s\n", color_name(i));
	}
	return 0;
}

/**
 * @return: return C_UNKNOWN if not found.
 */
enum data_color_enum data_color_name2num(const char *name)
{
	for (int i = 0; i < C_MAX; i++)
		if (!strncasecmp(color_name(i), name, strlen(name)))
			return i;
	/**
	 * print error to stderr, hint to stdout.
	 */
	fprintf(stderr, "ERROR: not support color '%s', please use:\n", name);
	data_color_print_names(stdout);
	return C_UNKNOWN;
}

bool data_color_hasname(const char *name)
{
	return data_color_name2num(name) != C_UNKNOWN;
}
