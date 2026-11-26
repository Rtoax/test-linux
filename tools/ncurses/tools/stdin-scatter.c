// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "plot.h"
#include "stdin.h"
#include "log.h"
#include "legend.h"

struct double_pair {
	double x, y;
};

bool stdin_buf_is_scatter_format(const char *buf)
{
	const char *s = stdin_buf_skip_whitespace(buf);
	/* FIXME: more accurate match */
	return *s == '(';
}

/**
 * @buf: format: "  ( x , y ) ( x, y)  "
 */
static void __add_dataset(struct plot *p, struct stdin_arg *a, char *buf)
{
	char *s = buf, *d_end;
	int npair = 0;
	struct double_pair *dps;

	if (!buf || !p || !a)
		return;

	dps = malloc(sizeof(struct double_pair) * a->nline);

	pc_debug("Scatter handle %s\n", buf);

	/**
	 * Parse an "(x,y)" for each loop
	 */
	while (s && *s != '\0') {
		s = stdin_buf_skip_whitespace(s);
		if (!s || *s != '(')
			continue;

		s++; /* skip '(' */

		s = stdin_buf_skip_whitespace(s);

		d_end = strchr(s, ',');
		if (!d_end)
			continue;
		*d_end = '\0';

		dps[npair].x = strtod(s, &s);

		s = d_end + 1; /* skip ',' */

		s = stdin_buf_skip_whitespace(s);

		d_end = strchr(s, ')');
		if (!d_end)
			continue;

		*d_end = '\0';

		dps[npair].y = strtod(s, &s);

		s = d_end + 1; /* skip ')' */

		s = stdin_buf_skip_whitespace(s);

		pc_debug("dps[%d] = (%lf,%lf)\n", npair, dps[npair].x,
			 dps[npair].y);

		dps = realloc(dps, sizeof(struct double_pair) * ++a->nline);
		npair++;
	}

	/* TODO: create a scatter serial */

	free(dps);
}

void stdin_update_scatter(struct lgroup *lg, struct stdin_arg *arg, char *buf)
{
	struct plot *p = lg->plot;
	char *s = stdin_buf_skip_whitespace(buf);
	static bool is_scatter_plot = false;

	pc_debug("Scatter parsing: %s\n", buf);

	if (!is_scatter_plot) {
		is_scatter_plot = true;
		p->plot_type = PLOT_TYPE_SCATTER;
		reset_legend_queue();

		/* scatter plot no need line struct anymore */
		for_each_lgroup(&p->__line, g)
		{
			for_each_line(g, ln)
			{
				struct line *l = ln;
				ln = ln->next;
				free_line(l);
				if (!ln)
					break;
			}
			/* No need free lgroup right now. */
		}

		arg->nline = 1;
	}

	while (s && *s != '\0') {
		/**
		 * Scatter buffer format:
		 * 1. "(1,1)\n(1,1)\n(1,1)"
		 * 2. "(1,1); (1,1)\n(1,1)"
		 * 3. "(1,1); (1,1); (1,1)"
		 */
		char *d_end = stdin_buf_find_separator(s);
		if (d_end) {
			/**
			 * "(1,1)\0(1,1)\n(1,1)"
			 *  ^
			 *  s
			 */
			*d_end = '\0';

			__add_dataset(p, arg, s);

			/**
			 * "(1,1)\0(1,1)\n(1,1)"
			 *         ^
			 *         s
			 */
			s = d_end + 1;
		} else {
			/**
			 * "(1,1)\0(1,1)\n(1,1)"
			 *                ^
			 *                s
			 */
			__add_dataset(p, arg, s);
			s = NULL;
		}
	}
}
