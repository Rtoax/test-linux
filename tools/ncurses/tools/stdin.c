// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <unistd.h>
#include <sys/sysinfo.h>
#include "plot.h"
#include "stdin.h"

static void stdin_create(struct lgroup *lg, void *arg)
{
}

static void stdin_update(struct lgroup *lg, void *arg)
{
}

static const struct lgroup_operations stdin_ops = {
	.create = stdin_create,
	.update = stdin_update,
};

struct lgroup lg_stdin = {
	.ops = stdin_ops,
};
