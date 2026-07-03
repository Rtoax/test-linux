// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <unistd.h>
#include <sys/sysinfo.h>
#include "ram.h"
#include "plot.h"

static void ram_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "total", nextlcolor(C_RED));
	new_line(lg, "free", nextlcolor(C_GREEN));
	new_line(lg, "shared", nextlcolor(C_BLUE));
	new_line(lg, "buff", nextlcolor(C_CYAN));
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
		line_add_value(line, mem[i] * 1.0 / 1024 / 1024 / 1024, -1,
			       NULL);
		i++;
	}
}

static void ram_plot_debug(const struct lgroup *lg, void *arg)
{
	struct plot *p = lg->plot;
	__plot_debug_llabel(lg, p->bnd.top + 1);
}

static struct lgroup_operations ram_ops = {
	.create = ram_create,
	.update = ram_update,
	.plot_debug = ram_plot_debug,
};

struct lgroup lg_ram = {
	.name = "ram",
	.ops = &ram_ops,
};
