// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include "value.h"

int save_plot(const struct plot *p, const char *filename);
int load_plot(struct plot *p, const char *file);

extern struct lgroup lg_file;
