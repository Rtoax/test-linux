// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include "config.h"

struct plot;
struct lgroup_operations;

struct lgroup {
	const char name[64];
	int id;
	struct line *head, *tail;
	int count; /* number of lines */
	struct lgroup_operations *ops;
	struct lgroup *next;
	struct plot *plot; /* belongs to */
};

struct lgroup_operations {
	void *arg; /* pass to every fn */
	void (*create_lines)(struct lgroup *self, void *arg);
	void (*update_data)(struct lgroup *self, void *arg);
	void (*plot_debug)(const struct lgroup *self, void *arg);
};

#define for_each_line(lg, iter)                                       \
	for (struct line *iter = ((struct lgroup *)(lg))->head; iter; \
	     iter = iter->next)

int lgroup_add_line(struct lgroup *lg, struct line *l);
struct line *lgroup_line(const struct lgroup *lg, int idx);
