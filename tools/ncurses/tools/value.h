// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "config.h"
#include "axis.h"

enum math_trans_enum {
	MATH_TRANS_NONE = 0,
	MATH_TRANS_LOGARITHMIC,
	MATH_TRANS_LOGARITHMIC10,
	MATH_TRANS_EXPONENTIAL,
	MATH_TRANS_DELTA,
	MATH_TRANS_MAX,
};

struct __value {
	double v;
	double log_v; /* = sign(v) * log(1 + |v|) */
#define __LOG_V(v, real_v) "s*log(1+|%.3f|)=%.3f", v, real_v
	double log10_v; /* = sign(v) * log10(1 + |v|) */
#define __LOG10_V(v, real_v) "s*log10(1+|%.3f|)=%.3f", v, real_v
	double exp_v; /* = exp(v) */
#define __EXP_V(v, real_v) "exp(%.3f)=%.3f", v, real_v
};

struct value {
	struct __value y_v;
	struct x_axis_value x_v;
	struct value *next;
};

/**
 * if value don't have next value, NaN returned, use isnan() check.
 */
static inline double delta_v(const struct value *v)
{
#define __DELTA_V(next_v, v, real_v) "delta(%.3f-%.3f)=%.3f", next_v, v, real_v
	if (v->next)
		return v->next->y_v.v - v->y_v.v;
	else
		/* see __paint_line() check */
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
static inline double __signed_log_trans(double x, double (*fn)(double x))
{
	int sign = signbit(x) ? -1 : 1;
	return sign * fn(1 + fabs(x));
}

static inline double signed_log_trans(double x)
{
	return __signed_log_trans(x, log);
}

static inline double signed_log10_trans(double x)
{
	return __signed_log_trans(x, log10);
}

double get_trans_value(const struct value *v, enum math_trans_enum trans);
