// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <sys/time.h>
#include <time.h>
#include "config.h"

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
};

#define for_each_value(l, iter)                                     \
	for (struct value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

struct line_group;

struct lg_operations {
	void (*create)(struct line_group *self, void *arg);
	void (*update)(struct line_group *self, void *arg);
};

struct line_group {
	struct line *head, *tail;
	int count; /* number of lines */
	struct lg_operations ops;
};

#define for_each_line(lg, iter)                                           \
	for (struct line *iter = ((struct line_group *)(lg))->head; iter; \
	     iter = iter->next)

int dequeue_val(struct line *l);
int enqueue_val(struct line *l, double v);

struct line *new_line(struct line_group *lg, const char *name, int color);
struct line *init_line(struct line *l, const char *name, int color);

int line_group_add(struct line_group *lg, struct line *l);
