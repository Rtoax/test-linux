// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <string.h>
#include "line.h"
#include "lgroup.h"

int lgroup_add_line(struct lgroup *lg, struct line *l)
{
	if (!lg->head) {
		lg->head = l;
		lg->count = 1;
	} else {
		lg->tail->next = l;
		lg->count++;
	}
	lg->tail = l;

	l->id = lg->count;
	l->lg = lg;
	return 0;
}

/* Get lgroup's line from index */
struct line *lgroup_get_line_from_id(const struct lgroup *lg, int id)
{
	for_each_line(lg, ln)
	{
		if (ln->id == id)
			return ln;
	}
	return NULL;
}

struct line *lgroup_get_line_from_name(const struct lgroup *lg,
				       const char *name)
{
	for_each_line(lg, ln)
	{
		if (!strcmp(ln->name, name))
			return ln;
	}
	return NULL;
}
