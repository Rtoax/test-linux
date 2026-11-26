// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "plot.h"
#include "stdin.h"
#include "log.h"

bool stdin_buf_is_scatter_format(const char *buf)
{
	const char *s = stdin_buf_skip_whitespace(buf);
	return *s == '(';
}

void stdin_update_scatter(struct lgroup *lg, struct stdin_arg *arg, char *buf)
{
	pc_debug("Scatter parse: %s\n", buf);
	/* TODO */
}
