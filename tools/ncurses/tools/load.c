// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <stdlib.h>
#include <unistd.h>
#include "value.h"
#include "plot.h"
#include "load.h"

static void loadavg_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "load1", nextcolor(C_RED));
	new_line(lg, "load5", nextcolor(C_GREEN));
	new_line(lg, "load15", nextcolor(C_BLUE));
}

static void loadavg_update(struct lgroup *lg, void *arg)
{
	double avg[3];
	int i = 0;

	getloadavg(avg, 3);

	for_each_line(lg, line)
	{
		line_add_value(line, avg[i], -1);
		i++;
	}
}

static void loadavg_plot_debug(const struct lgroup *lg, void *arg)
{
	struct plot *p = lg->plot;
	int i = 0;
	for_each_line(lg, ln)
	{
		mvprintw(i + 1, p->bnd.left + 1, "%s: cnt=%ld %lf~%lf",
			 ln->name, ln->count, ln->min->v, ln->max->v);
		i++;
	}
}

static struct lgroup_operations loadavg_ops = {
	.create = loadavg_create,
	.update = loadavg_update,
	.plot_debug = loadavg_plot_debug,
};

struct lgroup lg_loadavg = {
	.ops = &loadavg_ops,
};
