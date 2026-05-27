// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include "value.h"

int dequeue_val(struct line *l)
{
	if (!l || !l->head)
		return 0;
	int v = l->head->v;
	/* update max */
	if (l->max && l->max == l->head) {
		struct value *tmp = l->max = l->head->next;
		while (tmp) {
			if (tmp->v > l->max->v)
				l->max = tmp;
			tmp = tmp->next;
		}
	}
	/* update min */
	if (l->min && l->min == l->head) {
		struct value *tmp = l->min = l->head->next;
		while (tmp) {
			if (tmp->v < l->min->v)
				l->min = tmp;
			tmp = tmp->next;
		}
	}
	l->count--;
	struct value *head = l->head;
	l->head = head->next;
	free(head);
	return v;
}

int enqueue_val(struct line *l, double v)
{
	struct value *new = malloc(sizeof(struct value));
	new->v = v;
	gettimeofday(&new->tv, NULL);
	new->next = NULL;

	if (!l->head) {
		l->head = new;
		l->count = 1;
	} else {
		l->tail->next = new;
		l->count++;
	}

	if (!l->max) {
		l->max = new;
	} else {
		if (l->max->v < v)
			l->max = new;
	}
	if (!l->min) {
		l->min = new;
	} else {
		if (l->min->v > v)
			l->min = new;
	}

	l->tail = new;
	return 0;
}

static struct line *__init_line(struct line *l, const char *name, int color)
{
	struct line *new = l ?: malloc(sizeof(struct line));
	memset(new, 0, sizeof(struct line));
	/* TODO: memleak */
	new->name = strdup(name);
	new->color = color;
	return new;
}

struct line *new_line(struct lgroup *lg, const char *name, int color)
{
	struct line *new = __init_line(NULL, name, color);
	lgroup_add(lg, new);
	return new;
}

int lgroup_add(struct lgroup *lg, struct line *l)
{
	if (!lg->head) {
		lg->head = l;
		lg->count = 1;
	} else {
		lg->tail->next = l;
	}
	lg->count++;
	lg->tail = l;
	return 0;
}
