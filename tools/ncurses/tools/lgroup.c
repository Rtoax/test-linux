// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
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
	l->lg = lg;
	return 0;
}

/* Get lgroup's line from index */
struct line *lgroup_line(const struct lgroup *lg, int idx)
{
	for_each_line(lg, ln)
	{
		if (ln->id == idx)
			return ln;
	}
	return NULL;
}
