// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
/**
 * Scatter Plot
 */
#include <stdlib.h>
#include <string.h>
#include "scatter.h"

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
	/* TODO: set name from dequeue_legend() */
	memset(new, 0, sizeof(struct scatter));
	snprintf(new->name, sizeof(new->name) - 1, "%s", name);
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
