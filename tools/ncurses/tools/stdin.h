// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include "line.h"

struct stdin_arg {
	int nline;
	char *line_buff;
};

extern struct lgroup lg_stdin;
extern struct lgroup lg_stdin_no_ops;
