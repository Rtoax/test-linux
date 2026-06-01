// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <float.h>
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include "value.h"
#include "plot.h"

static char **llabels = NULL;
static int nr_llabels = 0;
static int idx_llabels = -1;

static enum ltype_enum *ltypes = NULL;
static int nr_ltypes = 0;
static int idx_ltypes = -1;

static enum lcolor_enum *lcolors = NULL;
static int nr_lcolors = 0;
static int idx_lcolors = -1;

/**
 * Since this program is single-thread, we could set line name with a global
 * list.
 */
int enqueue_llabel(const char *name)
{
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

int enqueue_ltype(enum ltype_enum t)
{
	nr_ltypes++;
	ltypes = (enum ltype_enum *)realloc(
		ltypes, nr_ltypes * sizeof(enum ltype_enum));
	ltypes[nr_ltypes - 1] = t;
	return 0;
}

int get_nr_ltypes(void)
{
	return nr_ltypes;
}

enum ltype_enum dequeue_ltype(void)
{
	if (nr_ltypes <= 0 || idx_ltypes >= nr_ltypes)
		return LINE_TYPE_DEFAULT;
	return ltypes[++idx_ltypes];
}

int enqueue_lcolor(enum lcolor_enum c)
{
	nr_lcolors++;
	lcolors = (enum lcolor_enum *)realloc(
		lcolors, nr_lcolors * sizeof(enum lcolor_enum));
	lcolors[nr_lcolors - 1] = c;
	return 0;
}

int get_nr_lcolors(void)
{
	return nr_lcolors;
}

/**
 * @return: return C_UNKNOWN if not enough.
 */
enum lcolor_enum dequeue_lcolor(void)
{
	if (nr_lcolors <= 0 || idx_lcolors >= nr_lcolors)
		return C_UNKNOWN;
	return lcolors[++idx_lcolors];
}

enum lcolor_enum nextcolor(enum lcolor_enum c)
{
	enum lcolor_enum color = dequeue_lcolor();
	if (color != C_UNKNOWN)
		return color;
	return c % C_MAX;
}

const static char *color_names[C_MAX] = {
	[C_GREEN] = "green",   [C_RED] = "red",		[C_CYAN] = "cyan",
	[C_WHITE] = "white",   [C_MAGENTA] = "magenta", [C_BLUE] = "blue",
	[C_YELLOW] = "yellow",
};

/**
 * @return: return C_UNKNOWN if not found.
 */
enum lcolor_enum color_name2n(const char *name)
{
	for (int i = 0; i < C_MAX; i++)
		if (!strncasecmp(color_names[i], name, strlen(name)))
			return i;
	/**
	 * print error to stderr, hint to stdout.
	 */
	fprintf(stderr, "ERROR: not support color '%s', please use:\n", name);
	for (int i = 0; i < C_MAX; i++) {
		fprintf(stdout, "\t%s\n", color_names[i]);
	}
	return C_UNKNOWN;
}

bool hascolor_name(const char *name)
{
	return color_name2n(name) != C_UNKNOWN;
}

int dequeue_val(struct line *l)
{
	if (!l || !l->head)
		return 0;
	int v = l->head->v;
	/* update max */
	if (l->max && l->max == l->head) {
		struct value *tmp = l->max = l->head->next;
		while (tmp) {
			if (tmp->v > l->max->v)
				l->max = tmp;
			tmp = tmp->next;
		}
	}
	/* update min */
	if (l->min && l->min == l->head) {
		struct value *tmp = l->min = l->head->next;
		while (tmp) {
			if (tmp->v < l->min->v)
				l->min = tmp;
			tmp = tmp->next;
		}
	}
	l->count--;
	struct value *head = l->head;
	l->head = head->next;
	free(head);
	return v;
}

int enqueue_val(struct line *l, double v)
{
	struct value *new = malloc(sizeof(struct value));
	new->v = v;
	gettimeofday(&new->tv, NULL);
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
		if (l->max->v < v)
			l->max = new;
	}
	if (!l->min) {
		l->min = new;
	} else {
		if (l->min->v > v)
			l->min = new;
	}

	l->tail = new;
	return 0;
}

double line_range_max(struct line *l, int start, int len)
{
	int i = 0;
	double max = -DBL_MAX;
	struct value *v = l->head;
	if (start < 0)
		start = 0;
	while (v) {
		if (i >= start && i < start + len) {
			if (max < v->v)
				max = v->v;
		}
		i++;
		v = v->next;
	}
	return max;
}

double line_range_min(struct line *l, int start, int len)
{
	int i = 0;
	double min = DBL_MAX;
	struct value *v = l->head;
	if (start < 0)
		start = 0;
	while (v) {
		if (i >= start && i < start + len) {
			if (min > v->v)
				min = v->v;
		}
		i++;
		v = v->next;
	}
	return min;
}

void line_add(struct line *l, double v)
{
	const struct plot *p = l->lg->plot;

	enqueue_val(l, v);

	/**
	 * Due to the limited width of the screen, we removed unnecessary
	 * history records and keep the old values as mach as possible.
	 */
	for (int i = p->widthmax - 2; i < l->count; i++)
		dequeue_val(l);
}

static struct line *__create_line(const char *name, int color)
{
	struct line *new = malloc(sizeof(struct line));
	const char *arg_name = dequeue_llabel();

	memset(new, 0, sizeof(struct line));

	/* FIXME: memleak here */
	new->name = arg_name ?: strdup(name);
	new->color = color;

	return new;
}

static int lgroup_add(struct lgroup *lg, struct line *l)
{
	if (!lg->head) {
		lg->head = l;
		lg->count = 1;
	} else {
		lg->tail->next = l;
		lg->count++;
	}
	lg->tail = l;
	l->lg = lg;
	return 0;
}

struct line *new_line_ops(struct lgroup *lg, const char *name, int color,
			  const struct ldraw_ops *ops)
{
	struct line *new = __create_line(name, color);
	new->ops = ops;
	lgroup_add(lg, new);
	return new;
}

struct line *new_line(struct lgroup *lg, const char *name, int color)
{
	return new_line_ops(lg, name, color, ldraw_type2ops(dequeue_ltype()));
}
