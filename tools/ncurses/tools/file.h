// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <stdbool.h>
#include "line.h"

int save_plot(const struct plot *p, const char *filename, bool debug);
int load_plot(struct plot *p, const char *file, bool debug);

extern struct lgroup lg_file;
