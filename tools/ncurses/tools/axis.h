// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"

enum x_axis_type {
	X_TIMEVAL,
	X_INDEX,
};

/* x axis value type */
union x_axis_value {
	struct timeval tv;
	unsigned long idx;
	/* add more x axis value type */
};

struct x_axis_range {
	// enum x_axis_type type;
	union {
		struct timeval tv;
		unsigned long idx;
	} start, end;
};

const char *x_axis_type_str(enum x_axis_type type);
int get_x_axis_type(const char *type);

const char *x_axis_range_str(enum x_axis_type t, struct x_axis_range *r,
			     char buf[64]);
