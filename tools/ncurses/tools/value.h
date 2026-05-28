// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <sys/time.h>
#include <time.h>
#include "config.h"

struct lgroup;
struct ldraw_ops;

struct value {
	double v;
	struct timeval tv;
	struct value *next;
};

struct line {
	const char *name;
	int color; /* C_RED, ... */
	struct value *head, *tail, *max, *min;
	int count; /* number of value */
	struct line *next; /* maybe line in group */
	struct lgroup *lg; /* belongs to */
	struct ldraw_ops *ops;
};

struct ldraw_ops {
	void (*hline)(struct line *ln);
	void (*vline)(struct line *ln);
	void (*ulcorner)(struct line *ln); /* upper left corner */
	/* TODO */
};

#define for_each_value(l, iter)                                     \
	for (struct value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

struct lgroup_operations {
	void *arg; /* pass to every fn */
	void (*create)(struct lgroup *self, void *arg);
	void (*update)(struct lgroup *self, void *arg);
};

struct plot;
struct lgroup {
	struct line *head, *tail;
	int count; /* number of lines */
	struct lgroup_operations ops;
	struct lgroup *next;
	struct plot *plot; /* belongs to */
};

#define for_each_line(lg, iter)                                       \
	for (struct line *iter = ((struct lgroup *)(lg))->head; iter; \
	     iter = iter->next)

int enqueue_lname(const char *name);
const char *dequeue_lname(void);

int dequeue_val(struct line *l);
int enqueue_val(struct line *l, double v);
void line_add(struct line *l, double v);

struct line *new_line(struct lgroup *lg, const char *name, int color);

int lgroup_add(struct lgroup *lg, struct line *l);
