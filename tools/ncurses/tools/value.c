// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <string.h>
#include "value.h"

void set___value(struct __value *v, double x)
{
	v->v = x;
	v->log_v = signed_log_trans(x);
	v->log10_v = signed_log10_trans(x);
	v->exp_v = exp(x);
}

double get_trans_value(const struct ln_value *v, enum math_trans_enum trans)
{
	double val = v->y_v.v;

	if (trans == MATH_TRANS_LOGARITHMIC)
		val = v->y_v.log_v;
	else if (trans == MATH_TRANS_LOGARITHMIC10)
		val = v->y_v.log10_v;
	else if (trans == MATH_TRANS_EXPONENTIAL)
		val = v->y_v.exp_v;
	else if (trans == MATH_TRANS_DELTA)
		val = delta_v(v);

	return val;
}
