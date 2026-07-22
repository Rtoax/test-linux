// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"

struct value {
	double v;
	double log_v; /* = sign(v) * log(1 + |v|) */
	double log10_v; /* = sign(v) * log10(1 + |v|) */
	double exp_v; /* = exp(v) */
	struct {
		/* x axis value type */
		union {
			struct timeval tv;
			/* TODO: add more */
		};
	} x_axis;
	struct value *next;
};

/**
 * if value don't have next value, NaN returned, use isnan() check.
 */
static inline double delta_v(struct value *v)
{
	if (v->next)
		return v->next->v - v->v;
	else
		return nan("NAN");
}

/**
 * For unbounded data streams generated in real time (containing negative, zero,
 * and positive numbers), directly taking log(x) of the original value will
 * result in a mathematical error or infinity (because x≤0 is meaningless).
 *
 * Scheme: Signed logarithmic transformation
 *
 *     y = sign(x) * log(1 + |x|)
 */
static inline double signed_log_trans(double x)
{
	int sign = signbit(x) ? -1 : 1;
	return sign * log(1 + fabs(x));
}

static inline double signed_log10_trans(double x)
{
	int sign = signbit(x) ? -1 : 1;
	return sign * log10(1 + fabs(x));
}
