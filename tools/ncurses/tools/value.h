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

struct values {
	struct value *head, *tail, *max, *min;
	int count; /* number of value */
};

#define for_each_value(vals, iter)                                       \
	for (struct value *iter = ((struct values *)(vals))->head; iter; \
	     iter = iter->next)

int dequeue_val(struct values *vals);
int enqueue_val(struct values *vals, double v);
