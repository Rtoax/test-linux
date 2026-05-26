// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <unistd.h>
#include "ram.h"
#include "plot.h"

static void ram_create(struct lgroup *lg, void *arg)
{
}

static void ram_update(struct lgroup *lg, void *arg)
{
}

struct lgroup lg_ram = {
	.ops.create = ram_create,
	.ops.update = ram_update,
};
