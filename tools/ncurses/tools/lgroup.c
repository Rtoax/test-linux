// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <assert.h>
#include <string.h>
#include "line.h"
#include "lgroup.h"
#include "plot.h"

int plot_add_lgroup(struct plot *p, struct lgroup *lg, void *lg_ops_arg)
{
	if (!p->__line.lghead) {
		p->__line.lghead = lg;
		p->__line.lgcount = 1;
	} else {
		p->__line.lgtail->next = lg;
		p->__line.lgcount++;
	}
	p->__line.lgtail = lg;
	lg->plot = p;
	lg->id = p->__line.lgcount;
	if (lg->ops) {
		lg->ops->arg = lg_ops_arg;
	}

	assert(!(!lg->ops && lg_ops_arg) && "not allow none-ops with ops arg");
	return 0;
}

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
