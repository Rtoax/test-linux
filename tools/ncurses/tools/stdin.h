// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include "line.h"

struct stdin_arg {
	int nline;
	/**
	 * Line buffer string format, values splited by whitespace, and groups
	 * splited by '\n'. formats:
	 *
	 * 1. line format: double1 double2 double3 ...
	 *    examples:
	 *       "0.49 0.64 0.68"
	 *       "0.49 0.64 0.68\n"
	 *       "0.49 0.64 0.68\n0.49 0.64 0.68\n"
	 *       "0.49 0.64 0.68;0.49 0.64 0.68\n"
	 *       "0.49 0.64 0.68;0.49 0.64 0.68;"
	 *
	 * 2. scatter format: (x,y) (x,y) (x,y) ...
	 *    examples:
	 *       "(1,1) (2,2)"
	 *       "(1,1) (2,2)\n"
	 *       "(1,1) (2,2)\n(2,2) (3,3)\n"
	 *       "(1,1) (2,2);(2,2) (3,3)\n"
	 *       "(1,1) (2,2);(2,2) (3,3);"
	 */
	char *line_buff;
};

extern struct lgroup lg_stdin;
extern struct lgroup lg_stdin_no_ops;

char *stdin_buf_skip_whitespace(const char *buf);
char *stdin_buf_find_separator(char *start);
char *stdin_buf_skip_ws_sep_ws(const char *buf);

/* Scatter chart */
bool stdin_buf_is_scatter_format(const char *s);
void stdin_update_scatter(struct lgroup *lg, struct stdin_arg *arg, char *buf);
void stdin_debug_scatter(const struct lgroup *lg, struct stdin_arg *arg,
			 char *buf);

void stdin_debug_lines(const struct lgroup *lg, void *arg);
