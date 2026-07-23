// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "line.h"
#include "plot.h"
#include "loadavg.h"

static int loadavg_create_lines(struct lgroup *lg, void *arg)
{
	int n = 0;
	n = new_line(lg, "load1", nextlcolor(C_RED)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	n = new_line(lg, "load5", nextlcolor(C_GREEN)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	n = new_line(lg, "load15", nextlcolor(C_BLUE)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
done:
	return n;
}

static void loadavg_update_data(struct lgroup *lg, void *arg)
{
	double avg[3];
	int i = 0;

	/* or use sysinfo(2) */
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
	.create_lines = loadavg_create_lines,
	.update_data = loadavg_update_data,
	.plot_debug = loadavg_plot_debug,
};

struct lgroup lg_loadavg = {
	.name = "loadavg",
	.ops = &loadavg_ops,
};
