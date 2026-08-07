// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"

struct x_axis_value {
	/* x axis value type */
	union {
		struct timeval tv;
		/* TODO: add more */
	};
};

struct x_axis_range {
	struct timeval start, end;
};
