// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <ctype.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "plot.h"
#include "stdin.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static char *skip(char *buf)
{
	while (*buf != '\0' && isspace(*buf))
		buf++;
	return buf;
}

static void __add_line(struct lgroup *lg, int i)
{
	char name[64] = { 0 };
	snprintf(name, 64, "line%d", i);
	enum lcolor_enum color = nextcolor(i);

	if (i < get_nr_ltypes())
		new_line(lg, name, color);
	else {
		int idx = (i - get_nr_ltypes()) / C_MAX;
		idx %= LINE_TYPE_MAX;
		new_line_ops(lg, name, color, ldraw_type2ops(idx));
	}
}

static void stdin_create(struct lgroup *lg, void *arg)
{
	int i;
	struct stdin_arg *a = arg;

	for (i = 0; i < a->nline; i++)
		__add_line(lg, i);
}

static void __stdin_add_data(struct lgroup *lg, struct stdin_arg *a, char *buf)
{
	int i, narg;
	double *values = malloc(sizeof(double) * a->nline);

	if (*buf == '\0')
		return;

	for (i = 0; i < a->nline && *buf != '\0'; i++) {
		buf = skip(buf);
		values[i] = strtod(buf, &buf);
		buf = skip(buf);
	}

	/* found more values, we could apped new line */
	while (*buf != '\0') {
		buf = skip(buf);
		if (!isdigit(*buf))
			break;

		__add_line(lg, i);

		values = realloc(values, sizeof(double) * ++a->nline);
		values[i++] = strtod(buf, &buf);
	}
	narg = i;

	i = 0;
	for_each_line(lg, line)
	{
		/**
		 * The number of data items read from stdin may change. If it
		 * is less than the previous number, then we need to add the old
		 * data. If it's more than before, we've already added lines
		 * above it.
		 */
		if (i < narg) {
			line_add_value(line, values[i], -1);
		} else {
			line_add_value(line, line->tail->v, -1);
		}
		i++;
	}
	free(values);
}

static void __stdin_update(struct lgroup *lg, struct stdin_arg *a)
{
	char *buf = strdup(a->line_buff);

	if (!buf)
		return;

	char *s = buf;

	/**
	 * The buf could be "0.49 0.64 0.68\n0.49 0.64 0.68\n", split it by '\n'
	 * first.
	 */
	while (s && *s != '\0') {
		char *ln_end = strchr(s, '\n');
		if (ln_end) {
			*ln_end = '\0';
			__stdin_add_data(lg, a, s);
			s = ln_end + 1;
		} else {
			__stdin_add_data(lg, a, s);
			s = NULL;
		}
	}
	free(buf);
}

static void stdin_update(struct lgroup *lg, void *arg)
{
	__stdin_update(lg, arg);
}

static void stdin_plot_debug(const struct lgroup *lg, void *arg)
{
	struct stdin_arg *a = arg;
	struct plot *p = lg->plot;
	int i;
	char *buf = strdup(a->line_buff);
	char *s = buf;

	/**
	 * Each stdin string ends with a newline character, but this affects
	 * the output of other content when printing debug information.
	 * Therefore, the newline character is replaced with a ';'.
	 */
	while (s && *s) {
		if (*s == '\n')
			*s = ';';
		s++;
	}

	mvprintw(0, p->bnd.left + 1, "lgroup cnt %d, arg nline %d", lg->count,
		 a->nline);
	mvprintw(1, p->bnd.left + 1, "stdin: '%s'", buf);

	i = 0;
	for_each_line(lg, line)
	{
		if (line->count <= 0)
			mvprintw(i + 2, p->bnd.left + 1, "%s: %ld", line->name,
				 line->count);
		else
			mvprintw(i + 2, p->bnd.left + 1,
				 "%s: %ld - %f - %lf~%lf", line->name,
				 line->count, line->tail->v, line->min->v,
				 line->max->v);
		i++;
	}
	free(buf);
}

static struct lgroup_operations stdin_ops = {
	.create = stdin_create,
	.update = stdin_update,
	.plot_debug = stdin_plot_debug,
};

struct lgroup lg_stdin = {
	.ops = &stdin_ops,
};
