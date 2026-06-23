// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include "value.h"

struct plot_file_operations {
	const char *name;
	int (*save)(const struct plot *p);
};

struct file_arg {
	const char *filename;
	// TODO
};

int save_plot(const struct plot *p);

extern struct lgroup lg_file;
