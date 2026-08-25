// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "axis.h"

const static char *__x_axis_type_str[] = { "x-timeval", "x-index" };

const char *x_axis_type_str(enum x_axis_type type)
{
	if (type < X_TIMEVAL || type > X_INDEX)
		return "unknown";
	return __x_axis_type_str[type];
}

/**
 * @return: enum x_axis_type
 */
int get_x_axis_type(const char *type)
{
	int ret;

	if (!strcmp("x-timeval", type))
		ret = X_TIMEVAL;
	else if (!strcmp("x-index", type))
		ret = X_INDEX;
	else {
		fprintf(stderr, "ERROR: unknown x axis type '%s'.\n", type);
		ret = -EINVAL;
	}
	return ret;
}

const char *x_axis_range_str(enum x_axis_type t, struct x_axis_range *r,
			     char buf[64])
{
	switch (t) {
	case X_TIMEVAL:
		strftime(buf, 64, "%T", localtime(&r->start.tv.tv_sec));
		strcat(buf, "~");
		strftime(buf + strlen(buf), 64 - strlen(buf), "%T",
			 localtime(&r->end.tv.tv_sec));
		break;
	case X_INDEX:
	default:
		snprintf(buf, 64, "%ld~%ld", r->start.idx, r->end.idx);
		break;
	}
	return buf;
}
