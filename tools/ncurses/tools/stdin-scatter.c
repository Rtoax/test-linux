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

bool stdin_buf_is_scatter_format(const char *buf)
{
	const char *s = stdin_buf_skip_whitespace(buf);
	/* FIXME: more accurate match */
	return *s == '(';
}

static void __stdin_scatter_add_data(struct plot *p, struct stdin_arg *a,
				     char *buf)
{
	pc_debug("Scatter handle %s\n", buf);
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

			__stdin_scatter_add_data(p, arg, s);

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
			__stdin_scatter_add_data(p, arg, s);
			s = NULL;
		}
	}
}
