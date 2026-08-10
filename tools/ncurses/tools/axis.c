// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "axis.h"

const char *x_axis_range_str(struct x_axis_range *r, char buf[64])
{
	strftime(buf, 64, "%T", localtime(&r->start.tv_sec));
	strcat(buf, "~");
	strftime(buf + strlen(buf), 64 - strlen(buf), "%T",
		 localtime(&r->end.tv_sec));
	return buf;
}
