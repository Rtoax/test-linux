// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <unistd.h>
#include <sys/sysinfo.h>
#include "plot.h"
#include "stdin.h"

static void stdin_create(struct lgroup *lg, void *arg)
{
	int i;
	struct stdin_arg *a = arg;
	char name[64];

	for (i = 0; i < a->nline; i++) {
		snprintf(name, 64, "line%d", i);
		new_line(lg, name, i % C_MAX);
	}
}

static void stdin_update(struct lgroup *lg, void *arg)
{
	struct stdin_arg *a = arg;
	char *buf = a->line_buff;
	(void)buf;
	/* TODO */
}

static const struct lgroup_operations stdin_ops = {
	.create = stdin_create,
	.update = stdin_update,
};

struct lgroup lg_stdin = {
	.ops = stdin_ops,
};
