// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <malloc.h>
#include <ncurses.h>
#include "value.h"

int dequeue_val(struct values *vals)
{
	if (!vals || !vals->head)
		return 0;
	int v = vals->head->v;
	/* update max */
	if (vals->max && vals->max == vals->head) {
		struct value *tmp = vals->max = vals->head->next;
		while (tmp) {
			if (tmp->v > vals->max->v)
				vals->max = tmp;
			tmp = tmp->next;
		}
	}
	/* update min */
	if (vals->min && vals->min == vals->head) {
		struct value *tmp = vals->min = vals->head->next;
		while (tmp) {
			if (tmp->v < vals->min->v)
				vals->min = tmp;
			tmp = tmp->next;
		}
	}
	vals->count--;
	vals->head = vals->head->next;
	return v;
}

int enqueue_val(struct values *vals, double v)
{
	struct value *new = malloc(sizeof(struct value));
	new->v = v;
	gettimeofday(&new->tv, NULL);
	new->next = NULL;

	if (!vals->head) {
		vals->head = new;
		vals->count = 1;
	} else {
		vals->tail->next = new;
		vals->count++;
	}

	if (!vals->max) {
		vals->max = new;
	} else {
		if (vals->max->v < v)
			vals->max = new;
	}
	if (!vals->min) {
		vals->min = new;
	} else {
		if (vals->min->v > v)
			vals->min = new;
	}

	vals->tail = new;
	return 0;
}
