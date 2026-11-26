// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "plot.h"
#include "stdin.h"
#include "log.h"

static char *skip_whitespace(char *buf)
{
	if (!buf)
		return NULL;
	/**
	 * Sometimes `isspace` from `glibc` does not return true for spaces or
	 * tab characters (for example, centos 8 glibc 2.28); therefore, I have
	 * added explicit checks for these. Perhaps we should remove `isspace`
	 * entirely, but since we haven’t encountered any issues yet, I’ll leave
	 * it in for now.
	 */
	while (*buf != '\0' && (isspace(*buf) || *buf == ' ' || *buf == '\t'))
		buf++;
	return buf;
}

/**
 * The buffer be splited by '\n' or ';', such as:
 * 1. "1 2 3\n 1 2 3\n 1 2 3"
 * 2. "1 2 3;  1 2 3\n 1 2 3"
 * 3. "1 2 3;  1 2 3;  1 2 3"
 */
static char *find_separator(char *start)
{
	char *newline, *semicolon;

	start = skip_whitespace(start);
	newline = strchr(start, '\n');
	semicolon = strchr(start, ';');

	if (!newline) {
		return semicolon;
	}
	if (!semicolon) {
		return newline;
	}

	return (newline - semicolon > 0) ? semicolon : newline;
}

static int __add_line(struct lgroup *lg, int i)
{
	char name[64] = { 0 };
	snprintf(name, 64, "line%d", i);
	enum data_color_enum color = nextdata_color(i);

	if (i < get_nr_ltypes())
		return new_line(lg, name, color) ? 0 : -EEXIST;
	else {
		int idx = (i - get_nr_ltypes()) / C_MAX;
		idx %= LINE_TYPE_MAX;
		return new_line_ops(lg, name, color, ltype_type2ops(idx)) ?
			       0 :
			       -EEXIST;
	}
}

static int stdin_create_lines(struct lgroup *lg, void *arg)
{
	int i, err = 0, n = 0;
	struct stdin_arg *a = arg;

	for (i = 0; i < a->nline; i++) {
		err = __add_line(lg, i);
		if (err < 0)
			return err;
		else
			n++;
	}
	return n;
}

static void __stdin_add_data(struct lgroup *lg, struct stdin_arg *a, char *buf)
{
	int i, nval;
	double *values = malloc(sizeof(double) * a->nline);

	/**
	 * It is possible for a buffer to be passed in that contains no data but
	 * does include a delimiter; we need to skip it entirely.
	 *
	 * For examples:
	 * 1. "    \n    "
	 * 2. "  ;     "
	 */
	buf = skip_whitespace(buf);
	if (buf && (*buf == '\n' || *buf == ';')) {
		buf++;
	}
	buf = skip_whitespace(buf);

	if (!buf || *buf == '\0') {
		return;
	}

	pc_debug("Parse stdin: '%s'\n", buf);

	for (i = 0; i < a->nline && *buf != '\0'; i++) {
		buf = skip_whitespace(buf);
		values[i] = strtod(buf, &buf);
		buf = skip_whitespace(buf);
	}

	/* found more values, we should append new line */
	while (*buf != '\0') {
		buf = skip_whitespace(buf);
		/**
		 * Must be a number, of course, be a negative number, or start
		 * with '.'
		 */
		if (!isdigit(*buf) && *buf != '-' && *buf != '.')
			break;

		__add_line(lg, i);

		values = realloc(values, sizeof(double) * ++a->nline);
		values[i++] = strtod(buf, &buf);
	}
	nval = i;

	i = 0;
	for_each_line(lg, line)
	{
		/**
		 * The number of data items read from stdin may change. If it
		 * is less than the previous number, then we need to add the old
		 * data. If it's more than before, we've already added lines
		 * above it.
		 */
		if (i < nval) {
			line_add_value(line, values[i], -1, NULL);
		} else {
			line_add_value(line, line->tail->y_v.v, -1, NULL);
		}
		i++;
	}
	free(values);
}

static void __stdin_update_data(struct lgroup *lg, struct stdin_arg *a)
{
	char *buf = strdup(a->line_buff);

	if (!buf)
		return;

	char *s = buf;

	while (s && *s != '\0') {
		/**
		 * The buffer be splited by '\n' or ';', such as:
		 * 1. "1 2 3\n 1 2 3\n 1 2 3"
		 * 2. "1 2 3;  1 2 3\n 1 2 3"
		 * 3. "1 2 3;  1 2 3;  1 2 3"
		 */
		char *d_end = find_separator(s);
		if (d_end) {
			/**
			 * "1 2 3\0 1 2 3\n 1 2 3"
			 *  ^
			 *  s
			 */
			*d_end = '\0';
			__stdin_add_data(lg, a, s);
			/**
			 * "1 2 3\0 1 2 3\n 1 2 3"
			 *          ^
			 *          s = d_end + 1
			 */
			s = d_end + 1;
		} else {
			/**
			 * "1 2 3\0 1 2 3\0 1 2 3"
			 *                  ^
			 *                  s
			 */
			__stdin_add_data(lg, a, s);
			s = NULL;
		}
	}
	free(buf);
}

static void stdin_update_data(struct lgroup *lg, void *arg)
{
	__stdin_update_data(lg, arg);
}

static void stdin_plot_debug(const struct lgroup *lg, void *arg)
{
	struct stdin_arg *a = arg;
	struct plot *p = lg->plot;
	char *buf = strdup(a->line_buff);
	char *s = buf;
	int x, y;

	/**
	 * Each stdin string ends with a newline character, but this affects
	 * the output of other content when printing debug information.
	 * Therefore, the newline character is replaced with a '\'.
	 */
	while (s && *s) {
		if (*s == '\n')
			*s = '#';
		s++;
	}

	if (p->vertical_plotting) {
		y = p->bnd.left + 1;
		x = p->bnd.bottom + 1;
	} else {
		y = p->bnd.top + 1;
		x = p->bnd.left + 1;
	}

	mvprintw(y, x, "lgroup cnt %d, arg nline %d", lg->count, a->nline);
	mvprintw(y + 1, x, "stdin: '%s'", buf);

	__plot_debug_llabel(
		lg, (p->vertical_plotting ? p->bnd.left : p->bnd.top) + 4,
		(p->vertical_plotting ? p->bnd.bottom : p->bnd.left) + 1);

	free(buf);
}

static struct lgroup_operations stdin_ops = {
	.create_lines = stdin_create_lines,
	.update_data = stdin_update_data,
	.plot_debug = stdin_plot_debug,
};

struct lgroup lg_stdin = {
	.name = "stdin",
	.ops = &stdin_ops,
};

struct lgroup lg_stdin_no_ops = {
	.name = "stdin",
	.ops = NULL,
};
