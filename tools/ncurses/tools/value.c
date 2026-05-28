// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include "value.h"
#include "plot.h"

static char **lnames = NULL;
static int nr_lnames = 0;
static int idx_lnames = -1;

/**
 * Since this program is single-thread, we could set line name with a global
 * list.
 */
int enqueue_lname(const char *name)
{
	nr_lnames++;
	lnames = (char **)realloc(lnames, nr_lnames * sizeof(char *));
	/* FIXME: memleak here */
	lnames[nr_lnames - 1] = strdup(name);
	return 0;
}

const char *dequeue_lname(void)
{
	if (nr_lnames <= 0 || idx_lnames >= nr_lnames)
		return NULL;
	return lnames[++idx_lnames];
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

void line_add(struct line *l, double v)
{
	const struct plot *p = l->lg->plot;

	enqueue_val(l, v);

	/**
	 * Due to the limited width of the screen, we removed unnecessary
	 * history records. TODO: maybe we should keep the old values.
	 */
	for (int i = p->plotwidth - 2; i < l->count; i++)
		dequeue_val(l);
}

static struct line *__create_line(const char *name, int color)
{
	struct line *new = malloc(sizeof(struct line));
	const char *arg_name = dequeue_lname();

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
	}
	lg->count++;
	lg->tail = l;
	l->lg = lg;
	return 0;
}

struct line *new_line(struct lgroup *lg, const char *name, int color,
		      struct ldraw_ops *ops)
{
	struct line *new = __create_line(name, color);
	new->ops = ops;
	lgroup_add(lg, new);
	return new;
}
