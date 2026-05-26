// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <sys/time.h>
#include <time.h>

struct value {
	double v;
	struct timeval tv;
	struct value *next;
};

struct line {
	struct value *head, *tail, *max, *min;
	int count; /* number of value */
};

#define for_each_value(l, iter)                                     \
	for (struct value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

int dequeue_val(struct line *l);
int enqueue_val(struct line *l, double v);
