// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <stdlib.h>
#include <unistd.h>
#include "line.h"
#include "plot.h"
#include "loadavg.h"

static void loadavg_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "load1", nextlcolor(C_RED));
	new_line(lg, "load5", nextlcolor(C_GREEN));
	new_line(lg, "load15", nextlcolor(C_BLUE));
}

static void loadavg_update(struct lgroup *lg, void *arg)
{
	double avg[3];
	int i = 0;

	getloadavg(avg, 3);

	for_each_line(lg, line)
	{
		line_add_value(line, avg[i], -1, NULL);
		i++;
	}
}

static void loadavg_plot_debug(const struct lgroup *lg, void *arg)
{
	struct plot *p = lg->plot;
	__plot_debug_llabel(lg, p->bnd.top + 1);
}

static struct lgroup_operations loadavg_ops = {
	.create = loadavg_create,
	.update = loadavg_update,
	.plot_debug = loadavg_plot_debug,
};

struct lgroup lg_loadavg = {
	.name = "loadavg",
	.ops = &loadavg_ops,
};
