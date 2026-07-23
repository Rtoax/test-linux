// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include "line.h"

struct stdin_arg {
	int nline;
	/**
	 * Line buffer string format, values splited by whitespace, and groups
	 * splited by '\n'. formats:
	 *
	 * 1. format: double1 double2 double3 ...
	 *    examples:
	 *       "0.49 0.64 0.68"
	 *       "0.49 0.64 0.68\n"
	 *       "0.49 0.64 0.68\n0.49 0.64 0.68\n"
	 */
	char *line_buff;
};

extern struct lgroup lg_stdin;
extern struct lgroup lg_stdin_no_ops;
