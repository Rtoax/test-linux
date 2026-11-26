// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
/**
 * Scatter Plot
 */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "scatter.h"
#include "legend.h"
#include "draw.h"

struct scatter *sp_get_scatter_from_name(const struct scatter_plotting *sp,
					 const char *name)
{
	for_each_scatter(sp, s)
	{
		if (!strcmp(s->name, name))
			return s;
	}
	return NULL;
}

static struct scatter *__create_scatter(const char *name, int color)
{
	struct scatter *new = malloc(sizeof(struct scatter));
	const char *arg_name = dequeue_legend();
	memset(new, 0, sizeof(struct scatter));
	snprintf(new->name, sizeof(new->name) - 1, "%s", arg_name ?: name);
	new->color = color;
	return new;
}

int sp_add_scatter(struct scatter_plotting *sp, struct scatter *s)
{
	if (!sp->schead) {
		sp->schead = s;
		sp->sccount = 1;
	} else {
		sp->sctail->next = s;
		sp->sccount++;
	}
	sp->sctail = s;
	s->id = sp->sccount;
	s->sp = sp;
	return 0;
}

struct scatter *new_scatter_ops(struct scatter_plotting *sp, const char *name,
				int color, const struct draw_operations *ops)
{
	struct scatter *old, *new;

	old = sp_get_scatter_from_name(sp, name);
	if (old)
		return NULL;

	new = __create_scatter(name, color);
	new->ops = ops;

	sp_add_scatter(sp, new);

	return new;
}

struct scatter *new_scatter(struct scatter_plotting *sp, const char *name,
			    int color)
{
	return new_scatter_ops(sp, name, color,
			       draw_ops_type2ops(dequeue_draw_ops()));
}

static int enqueue_point_to_tail(struct scatter *s, double x, double y)
{
	struct __point *new = malloc(sizeof(struct __point));

	memset(new, 0, sizeof(struct __point));

	set___value(&new->x, x);
	set___value(&new->y, y);

	new->next = NULL;

	if (!s->head) {
		s->head = new;
		s->count = 1;
	} else {
		s->tail->next = new;
		s->count++;
	}

	if (!s->max_x) {
		s->max_x = &new->x;
	} else {
		if (s->max_x->v < x)
			s->max_x = &new->x;
	}
	if (!s->min_x) {
		s->min_x = &new->x;
	} else {
		if (s->min_x->v > x)
			s->min_x = &new->x;
	}
	if (!s->max_y) {
		s->max_y = &new->y;
	} else {
		if (s->max_y->v < y)
			s->max_y = &new->y;
	}
	if (!s->min_y) {
		s->min_y = &new->y;
	} else {
		if (s->min_y->v > y)
			s->min_y = &new->y;
	}

	s->tail = new;
	return 0;
}

#if 0
int dequeue_point_from_head(struct scatter *s)
{
	if (!s || !s->head)
		return -EINVAL;

	/* update max x */
	if (s->max_x && s->max_x == &s->head->x) {
		struct __point *tmp = s->head->next;
		s->max_x = tmp ? &tmp->x : NULL;
		while (tmp) {
			if (s->max_x->v < tmp->x.v)
				s->max_x = &tmp->x;
			tmp = tmp->next;
		}
	}

	return 0;
}
#endif

void scatter_add_point(struct scatter *s, double x, double y)
{
	enqueue_point_to_tail(s, x, y);
}
