// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <unistd.h>
#include <sys/sysinfo.h>
#include "ram.h"
#include "plot.h"

static void ram_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "total", C_RED, &unicode_bold_line_ops);
	new_line(lg, "free", C_GREEN, &unicode_bold_line_ops);
	new_line(lg, "shared", C_BLUE, &unicode_bold_line_ops);
	new_line(lg, "buff", C_CYAN, &unicode_bold_line_ops);
}

static void ram_update(struct lgroup *lg, void *arg)
{
	struct sysinfo si;
	int i = 0;
	unsigned long mem[4] = { 0 };

	sysinfo(&si);

	mem[0] = si.totalram;
	mem[1] = si.freeram;
	mem[2] = si.sharedram;
	mem[3] = si.bufferram;

	for_each_line(lg, line)
	{
		line_add(line, mem[i] * 1.0 / 1024 / 1024 / 1024);
		i++;
	}
}

static const struct lgroup_operations ram_ops = {
	.create = ram_create,
	.update = ram_update,
};

struct lgroup lg_ram = {
	.ops = ram_ops,
};
