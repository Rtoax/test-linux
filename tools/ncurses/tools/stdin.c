// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <ctype.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include "plot.h"
#include "stdin.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static char *skip(char *buf)
{
	while (*buf != '\0' && isspace(buf[0]))
		buf++;
	return buf;
}

static void __add_line(struct lgroup *lg, int i)
{
	char name[64] = { 0 };
	snprintf(name, 64, "line%d", i);
	/* TODO: if stdin, auto select line type */
	if (i < get_nr_ltypes())
		new_line(lg, name, i % C_MAX);
	else {
		int idx = (i - get_nr_ltypes()) / C_MAX;
		idx %= LINE_TYPE_MAX;
		new_line_ops(lg, name, i % C_MAX, ldraw_type2ops(idx));
	}
}

static void stdin_create(struct lgroup *lg, void *arg)
{
	int i;
	struct stdin_arg *a = arg;

	for (i = 0; i < a->nline; i++)
		__add_line(lg, i);
}

static void stdin_update(struct lgroup *lg, void *arg)
{
	int i;
	struct stdin_arg *a = arg;
	double *values = malloc(sizeof(double) * a->nline);
	char *buf = a->line_buff;
	struct plot *p = lg->plot;

	if (*buf == '\0')
		return;

	for (i = 0; i < a->nline && *buf != '\0'; i++) {
		buf = skip(buf);

		double v = strtod(buf, &buf);
		values[i] = v;
	}

	/* found more values, we could apped new line */
	while (*buf != '\0') {
		buf = skip(buf);
		if (!isdigit(*buf)) {
			if (*buf != '\0')
				plot_warning(p, "stdin data syntax error: %s",
					     a->line_buff);
			break;
		}

		__add_line(lg, i);

		values = realloc(values, sizeof(double) * ++a->nline);
		values[i++] = strtod(buf, &buf);
	}

	i = 0;
	for_each_line(lg, line)
	{
		line_add(line, values[i]);
		i++;
	}
	free(values);
}

static void stdin_plot_debug(const struct lgroup *lg, void *arg)
{
	struct stdin_arg *a = arg;
	struct plot *p = lg->plot;
	int i;

	mvprintw(0, p->bnd.left + 1, "stdin: '%s'", a->line_buff);

	i = 0;
	for_each_line(lg, line)
	{
		if (line->count <= 0)
			continue;
		mvprintw(a->nline + i + 1, p->bnd.left + 1,
			 "%s: %d - %f - %lf~%lf", line->name, line->count,
			 line->tail->v, line->min->v, line->max->v);
	}
}

static const struct lgroup_operations stdin_ops = {
	.create = stdin_create,
	.update = stdin_update,
	.plot_debug = stdin_plot_debug,
};

struct lgroup lg_stdin = {
	.ops = stdin_ops,
};
