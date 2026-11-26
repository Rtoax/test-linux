// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#include <errno.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "ram.h"
#include "plot.h"
#include "utils.h"

static int ram_create_lines(struct lgroup *lg, void *arg)
{
	int n = 0;
	struct sysinfo si;

	sysinfo(&si);

	n = new_line(lg, "total", nextdata_color(C_RED)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	n = new_line(lg, "free", nextdata_color(C_GREEN)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	n = new_line(lg, "shared", nextdata_color(C_BLUE)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	n = new_line(lg, "buff", nextdata_color(C_CYAN)) ? n + 1 : -EEXIST;
	if (n < 0)
		goto done;
	if (si.totalswap > 0) {
		n = new_line(lg, "totalswap", nextdata_color(C_YELLOW)) ?
			    n + 1 :
			    -EEXIST;
		if (n < 0)
			goto done;
		n = new_line(lg, "freeswap", nextdata_color(C_MAGENTA)) ?
			    n + 1 :
			    -EEXIST;
		if (n < 0)
			goto done;
	}
done:
	return n;
}

static void ram_update_lines(struct lgroup *lg, void *arg)
{
	struct sysinfo si;
	int i = 0;
	unsigned long mem[6] = { 0 };

	sysinfo(&si);

	mem[0] = si.totalram;
	mem[1] = si.freeram;
	mem[2] = si.sharedram;
	mem[3] = si.bufferram;
	mem[4] = si.totalswap;
	mem[5] = si.freeswap;

	for_each_line(lg, line)
	{
		/* Bytes to GiB */
		line_add_value(line, mem[i] * 1.0 / GiB, -1, NULL);
		i++;
	}
}

static void ram_debug_lines(const struct lgroup *lg, void *arg)
{
	struct plot *p = lg->plot;
	__paint_debug_ln_label(
		lg, (p->vertical_plotting ? p->bnd.left : p->bnd.top) + 1,
		(p->vertical_plotting ? p->bnd.bottom : p->bnd.left) + 1);
}

static struct lgroup_operations ram_ops = {
	.create_lines = ram_create_lines,
	.update_lines = ram_update_lines,
	.debug_lines = ram_debug_lines,
};

struct lgroup lg_ram = {
	.name = "ram",
	.ops = &ram_ops,
};
