// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"

enum ln_x_type {
	X_TIMEVAL,
	X_INDEX,
	X_AXIS_TYPE_MAX,
};

/* x axis value type */
struct ln_x_value {
	struct timeval tv; /* X_TIMEVAL */
	unsigned long idx; /* X_INDEX */
	/* add more x axis value type */
};

struct ln_x_range {
	struct ln_x_value start, end;
};

int get_ln_x_type(const char *type);

const char *ln_x_type_str(enum ln_x_type type);
const char *ln_x_label_str(enum ln_x_type type);
const char *ln_x_range_str(enum ln_x_type t, struct ln_x_range *r,
			   char buf[64]);
