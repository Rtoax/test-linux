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

	struct ldraw_ops *ldraw_operations[] = {
		&unicode_bold_line_ops,
		&unicode_bold_dashed_line_ops,
		&unicode_line_ops,
		&unicode_line_dashed_line_ops,
	};
	new_line(lg, name, i % C_MAX,
		 ldraw_operations[(i / C_MAX) % ARRAY_SIZE(ldraw_operations)]);
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

#ifdef DEBUG
	mvprintw(0, p->bnd.left + 1, "stdin: '%s'", a->line_buff);
#endif

	if (*buf == '\0')
		return;

	for (i = 0; i < a->nline && *buf != '\0'; i++) {
		buf = skip(buf);

		double v = strtod(buf, &buf);
		values[i] = v;
#ifdef DEBUG
		mvprintw(i + 1, p->bnd.left + 1, "- %lf", values[i]);
#endif
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
#ifdef DEBUG
		mvprintw(a->nline + i + 1, p->bnd.left + 1,
			 "- %d - %f - %lf~%lf", line->count, values[i],
			 line->min->v, line->max->v);
#endif
	}
	free(values);
}

static const struct lgroup_operations stdin_ops = {
	.create = stdin_create,
	.update = stdin_update,
};

struct lgroup lg_stdin = {
	.ops = stdin_ops,
};
