// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <assert.h>
#include <errno.h>
#include <float.h>
#include <malloc.h>
#include <math.h>
#include <ncurses.h>
#include <string.h>
#include "line.h"
#include "plot.h"

static char **llabels = NULL;
static int nr_llabels = 0;
static int idx_llabels = -1;

/**
 * Since this program is single-thread, we could set line name with a global
 * list.
 */
int enqueue_llabel(const char *name)
{
	if (!name)
		return -EINVAL;

	for (int i = 0; i < nr_llabels; i++) {
		if (!strcmp(name, llabels[i])) {
			fprintf(stderr,
				"ERROR: line label '%s' already exist.\n",
				name);
			return -EEXIST;
		}
	}

	nr_llabels++;
	llabels = (char **)realloc(llabels, nr_llabels * sizeof(char *));

	/* FIXME: memleak here */
	llabels[nr_llabels - 1] = strdup(name);
	return 0;
}

const char *dequeue_llabel(void)
{
	if (nr_llabels <= 0 || idx_llabels >= nr_llabels)
		return NULL;
	return llabels[++idx_llabels];
}

static int dequeue_value_from_head(struct line *l)
{
	if (!l || !l->head)
		return 0;

	int v = l->head->y_v.v;

	/* update max */
	if (l->max && l->max == l->head) {
		struct value *tmp = l->max = l->head->next;
		while (tmp) {
			if (tmp->y_v.v > l->max->y_v.v)
				l->max = tmp;
			tmp = tmp->next;
		}
	}
	/* update min */
	if (l->min && l->min == l->head) {
		struct value *tmp = l->min = l->head->next;
		while (tmp) {
			if (tmp->y_v.v < l->min->y_v.v)
				l->min = tmp;
			tmp = tmp->next;
		}
	}
	l->count--;
	struct value *head = l->head;
	l->head = head->next;

	/* refresh x axis start time value */
	if (l->head) {
		l->x_range.start.tv = l->head->x_v.tv;
		l->x_range.start.idx = l->head->x_v.idx;
	} else {
		memset(&l->x_range.start.tv, 0, sizeof(struct timeval));
		l->x_range.start.idx = 0;
	}

	free(head);
	return v;
}

static int enqueue_value_to_tail(struct line *l, double v,
				 struct x_axis_value *x)
{
	struct value *new = malloc(sizeof(struct value));

	new->y_v.v = v;
	new->y_v.log_v = signed_log_trans(v);
	new->y_v.log10_v = signed_log10_trans(v);
	new->y_v.exp_v = exp(v);

	/* set newest time value */
	if (x) {
		memcpy(&new->x_v.tv, &x->tv, sizeof(struct timeval));
	} else {
		gettimeofday(&new->x_v.tv, NULL);
	}

	l->x_range.end.tv = new->x_v.tv;
	if (l->count == 0) {
		l->x_range.start.tv = new->x_v.tv;
	}

	/* set newest index */
	if (x) {
		new->x_v.idx = x->idx;
	} else {
		new->x_v.idx = l->count;
	}

	l->x_range.end.idx = new->x_v.idx;
	if (l->count == 0) {
		l->x_range.start.idx = new->x_v.idx;
	}

	new->next = NULL;

	if (!l->head) {
		l->head = new;
		l->count = 1;
	} else {
		l->tail->next = new;
		l->count++;
	}

	if (!l->max) {
		l->max = new;
	} else {
		if (l->max->y_v.v < v)
			l->max = new;
	}
	if (!l->min) {
		l->min = new;
	} else {
		if (l->min->y_v.v > v)
			l->min = new;
	}

	l->tail = new;
	return 0;
}

double line_range_avg(struct line *l, int start, int len)
{
	int i = 0, n = 0;
	double sum = 0;
	struct value *v = l->head;
	if (start < 0)
		start = 0;
	while (v) {
		if (i >= start && i < start + len) {
			n++;
			sum += v->y_v.v;
		}
		i++;
		v = v->next;
	}
	assert(n != 0 && "line_range_avg: not found values in range");
	return sum / n;
}

enum range_op {
	RANGE_OP_MAX,
	RANGE_OP_MIN,
	RANGE_OP_DELTA_MAX, /* see delta_v() */
	RANGE_OP_DELTA_MIN, /* see delta_v() */
};

static double __line_range_rslt(struct line *l, int start, int interval,
				int len, enum range_op op)
{
	int i = 0;
	double rslt;

	switch (op) {
	case RANGE_OP_MAX:
	case RANGE_OP_DELTA_MAX:
		rslt = -DBL_MAX;
		break;
	case RANGE_OP_MIN:
	case RANGE_OP_DELTA_MIN:
		rslt = DBL_MAX;
		break;
	}

	struct value *v = l->head;

	if (start < 0)
		start = 0;

	while (v) {
		if (i >= start && i < start + len) {
			double delta = delta_v(v);
			switch (op) {
			case RANGE_OP_MAX:
				if (rslt < v->y_v.v)
					rslt = v->y_v.v;
				break;
			case RANGE_OP_MIN:
				if (rslt > v->y_v.v)
					rslt = v->y_v.v;
				break;
			case RANGE_OP_DELTA_MAX:
				if (isnan(delta)) {
					break;
				}
				if (rslt < delta)
					rslt = delta;
				break;
			case RANGE_OP_DELTA_MIN:
				if (isnan(delta)) {
					break;
				}
				if (rslt > delta)
					rslt = delta;
				break;
			}
		}
		if (i < start) {
			i++;
			v = v->next;
		} else {
			for (int j = 0; j < interval; j++) {
				v = v->next;
				if (!v)
					goto end_loop;
			}
			i += interval;
		}
	}
end_loop:
	return rslt;
}

double line_range_max(struct line *l, int start, int interval, int len)
{
	return __line_range_rslt(l, start, interval, len, RANGE_OP_MAX);
}

double line_range_delta_max(struct line *l, int start, int interval, int len)
{
	return __line_range_rslt(l, start, interval, len, RANGE_OP_DELTA_MAX);
}

double line_range_min(struct line *l, int start, int interval, int len)
{
	return __line_range_rslt(l, start, interval, len, RANGE_OP_MIN);
}

double line_range_delta_min(struct line *l, int start, int interval, int len)
{
	return __line_range_rslt(l, start, interval, len, RANGE_OP_DELTA_MIN);
}

/**
 * @limit: max length of line (number of values), if < 0, means no limit.
 */
void line_add_value(struct line *l, double v, long limit,
		    struct x_axis_value *x)
{
	enqueue_value_to_tail(l, v, x);

	/**
	 * Due to the limited width of the screen or size of memory, we
	 * removed unnecessary history records and keep the old values as
	 * much as possible.
	 */
	if (limit < 0)
		return;
	for (long i = limit; i < l->count; i++)
		dequeue_value_from_head(l);
}

static struct line *__create_line(const char *name, int color)
{
	struct line *new = malloc(sizeof(struct line));
	const char *arg_name = dequeue_llabel();

	memset(new, 0, sizeof(struct line));

	set_line_name(new, arg_name ?: name);
	new->color = color;

	return new;
}

/**
 * If the line is already exist in line group, return NULL.
 */
struct line *new_line_ops(struct lgroup *lg, const char *name, int color,
			  const struct draw_operations *ops)
{
	struct line *old, *new;

	old = lgroup_get_line_from_name(lg, name);
	if (old)
		return NULL;

	new = __create_line(name, color);
	new->ops = ops;

	lgroup_add_line(lg, new);

	return new;
}

struct line *new_line(struct lgroup *lg, const char *name, int color)
{
	return new_line_ops(lg, name, color,
			    draw_ops_type2ops(dequeue_draw_ops()));
}

int paint_y0_line(const struct plot *p, double min, double max)
{
	if (min > 0 || max < 0) {
		return 0;
	}
	double h = get_plot_value_heigh(p, min, max, 0);

	attron(A_DIM);
	for (int i = 0; i < p->plotwidth - 1; i++) {
		if (p->vertical_plotting) {
			mvwprintw(p->win, p->bnd.left + 1 + i, h, "|");
		} else {
			mvwprintw(p->win, h, p->bnd.left + 1 + i, "-");
		}
	}
	attroff(A_DIM);
	return 0;
}

/**
 * @start: start point of line.
 * @len: number of value to plot.
 * @max and @min is algorithm value, in the case of a logarithmic plot, 'max'
 * is already a logarithmic value.
 */
void __paint_line(struct plot *p, const struct lgroup *lg,
		  const struct line *ln, int start, int len, int shift,
		  double max, double min, double *stacked_line, bool first_line)
{
	int iv;
	int prev_h = -1;
	bool is_last_v = false;
	chtype color = getflavor(ln->color);

	const long ln_shift_count = ln->count - shift;
	const int nvs = (ln_shift_count + p->plotscaling - 1) / p->plotscaling;

	iv = -1;
	for_each_value(ln, v)
	{
		iv++;
		/**
		 * The number of data points may be greater than the horizontal
		 * size of the plotting area, so it is necessary to first skip
		 * the data points that exceed the plotting area.
		 *
		 * line: |------------------------| line count
		 *
		 *                      <--shift--> plotshift * plotscaling
		 *
		 *       |--------------|           @ln_shift_count
		 *
		 * plot:        |=======|           plotwidth * plotscaling
		 *
		 *              ^ start
		 *                      ^ start + len
		 *
		 *     ^^^^^ skip
		 *
		 * see also paint_lgroup().
		 */
		if (iv <= start || iv >= start + len) {
			continue;
		}

		if (iv % p->plotscaling != 0) {
			continue;
		}

		/**
		 * If plot MATH_TRANS_DELTA, the last value will be skipped,
		 * then we need '>=' instead of '>'.
		 */
		if (iv >= start + len - p->plotscaling - 1) {
			is_last_v = true;
		}

		double real_v = get_plot_value(p, v);

		/**
		 * 1. the last value of line may be NaN, see delta_v()
		 */
		if (isnan(real_v)) {
			iv = ln_shift_count;
			goto print_llabel;
		}

		if (stacked_line) {
			if (first_line) {
				stacked_line[iv] = real_v;
			} else {
				stacked_line[iv] += real_v;
			}
		}

		double plot_v;
		if (stacked_line) {
			plot_v = stacked_line[iv];
		} else {
			plot_v = real_v;
		}
		int ivs = (iv + p->plotscaling - 1) / p->plotscaling;

		int h = get_plot_value_heigh(p, min, max, plot_v);
		int w = p->plotwidth + p->bnd.left - (nvs - ivs);

		attron(color);
		if (p->vertical_plotting) {
			ln->ops->vertical(p, p->win, w, h, 1);
		} else {
			ln->ops->horizon(p, p->win, h, w, 1);
		}
		attroff(color);

		/**
		 * Print the corner, like: ---+
		 *                            |
		 *                            +----
		 */
		if (prev_h != -1) {
			attron(color);
			if (prev_h > h) {
				if (p->vertical_plotting) {
					ln->ops->lrcorner(p, p->win, w, prev_h);
					ln->ops->ulcorner(p, p->win, w, h);
					ln->ops->horizon(p, p->win, w, h + 1,
							 prev_h - h - 1);
				} else {
					ln->ops->lrcorner(p, p->win, prev_h, w);
					ln->ops->ulcorner(p, p->win, h, w);
					ln->ops->vertical(p, p->win, h + 1, w,
							  prev_h - h - 1);
				}
			} else if (h > prev_h) {
				if (p->vertical_plotting) {
					ln->ops->llcorner(p, p->win, w, prev_h);
					ln->ops->urcorner(p, p->win, w, h);
					ln->ops->horizon(p, p->win, w,
							 prev_h + 1,
							 h - prev_h - 1);
				} else {
					ln->ops->urcorner(p, p->win, prev_h, w);
					ln->ops->llcorner(p, p->win, h, w);
					ln->ops->vertical(p, p->win, prev_h + 1,
							  w, h - prev_h - 1);
				}
			}
			attroff(color);
		}

		prev_h = h;

		/* set x axis */
		if ((ivs - 1) % (p->vertical_plotting ? 1 : 10) == 0) {
			int y, x, n = 0;
			char buf[32];

			if (p->vertical_plotting) {
				y = w;
				x = 0;
			} else {
				y = plot_height(p) - p->bnd.bottom + 1;
				x = w;
			}
			switch (p->x_type) {
			case X_TIMEVAL:
				timeval_str(&v->x_v.tv, buf);
				n = strlen(buf);
				break;
			case X_INDEX:
				n = snprintf(buf, sizeof(buf), "%ld",
					     v->x_v.idx);
				break;
			default:
				break;
			}
			mvprintw(y, x, "%s", buf);

			/* vertical plotting need update bottom boundary size */
			if (p->vertical_plotting &&
			    p->bnd_prev_max.bottom < n) {
				p->bnd_prev_max.bottom = n;
			}
		}

		/* set y axis */
		char sv[128];
		int nc;
		int sz = sizeof(sv);

		if (p->math_trans == MATH_TRANS_LOGARITHMIC) {
			nc = snprintf(sv, sz, __LOG_V(v->y_v.v, real_v));
		} else if (p->math_trans == MATH_TRANS_LOGARITHMIC10) {
			nc = snprintf(sv, sz, __LOG10_V(v->y_v.v, real_v));
		} else if (p->math_trans == MATH_TRANS_EXPONENTIAL) {
			nc = snprintf(sv, sz, __EXP_V(v->y_v.v, real_v));
		} else if (p->math_trans == MATH_TRANS_DELTA &&
			   !p->enable_stacked_line_chart) {
			nc = snprintf(sv, sz,
				      __DELTA_V(v->next->y_v.v, v->y_v.v,
						real_v));
		} else {
			nc = snprintf(sv, sz, "%.3f", real_v);
		}

		if (p->enable_stacked_line_chart && plot_v != real_v) {
			nc += snprintf(sv + strlen(sv), sz - strlen(sv),
				       "[%.3f]", plot_v);
		}

		/* horizontal plotting need update bottom boundary size */
		if (!p->vertical_plotting && p->bnd_prev_max.left < nc) {
			p->bnd_prev_max.left = nc;
		}

		attron(color);
		if (p->vertical_plotting) {
			if (is_last_v) {
				/**
				 * TODO: Printing should be better here, right
				 * now, we just print last value, however.
				 */
				mvprintw(p->bnd.left - 1, h, "%s", sv);
			}
		} else {
			mvprintw(h, 0, "%s", sv);
		}
		attroff(color);

print_llabel:
		attron(color);
		if (iv + 1 + p->plotscaling > ln_shift_count) {
			if (p->vertical_plotting) {
				int y = p->plotwidth + p->bnd.left;
				mvprintw(y, h, "%s", ln->name);
				if (p->debug) {
					mvprintw(y + 1, h, "%ld", ln->count);
					mvprintw(y + 2, h, "%.1f",
						 ln->min->y_v.v);
					mvprintw(y + 3, h, "%.1f",
						 ln->max->y_v.v);
				}
			} else {
				mvprintw(h, w + 1, "%s", ln->name);
				nc = strlen(ln->name);
				if (p->bnd_prev_max.right < nc)
					p->bnd_prev_max.right = nc;

				if (p->debug) {
					mvprintw(h + 1, w + 1, "%ld",
						 ln->count);
					mvprintw(h + 2, w + 1, "%.1f",
						 ln->min->y_v.v);
					mvprintw(h + 3, w + 1, "%.1f",
						 ln->max->y_v.v);
				}
			}
		}
		attroff(color);
	}
}
