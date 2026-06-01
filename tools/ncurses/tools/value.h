// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <stdbool.h>
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

enum ltype_enum {
	LINE_TYPE_DEFAULT = 0,
	LINE_TYPE_BOLD_UNICODE = LINE_TYPE_DEFAULT,
	LINE_TYPE_BOLD_UNICODE_DASHED,
	LINE_TYPE_BOLDBOLD_UNICODE,
	LINE_TYPE_THIN_UNICODE,
	LINE_TYPE_THIN_UNICODE_DASHED,
	LINE_TYPE_UTF8,
	LINE_TYPE_HEART_UNICODE,
	LINE_TYPE_MAX,
};

struct line {
	const char *name;
	int color; /* C_RED, ... */
	struct value *head, *tail, *max, *min;
	int count; /* number of value */
	struct line *next; /* maybe line in group */
	struct lgroup *lg; /* belongs to */
	const struct ldraw_ops *ops;
};

struct ldraw_ops {
	char *name;
	void (*horizon)(struct line *ln, int y, int x);
	void (*vertical)(struct line *ln, int y, int x, int n);
	void (*ulcorner)(struct line *ln, int y, int x); /* upper left corner */
	void (*llcorner)(struct line *ln, int y, int x); /* lower left corner */
	void (*urcorner)(struct line *ln, int y,
			 int x); /* upper right corner */
	void (*lrcorner)(struct line *ln, int y,
			 int x); /* lower right corner */
};

#define for_each_value(l, iter)                                     \
	for (struct value *iter = ((struct line *)(l))->head; iter; \
	     iter = iter->next)

struct lgroup_operations {
	void *arg; /* pass to every fn */
	void (*create)(struct lgroup *self, void *arg);
	void (*update)(struct lgroup *self, void *arg);
	void (*plot_debug)(const struct lgroup *self, void *arg);
};

struct plot;
struct lgroup {
	struct line *head, *tail;
	int count; /* number of lines */
	struct lgroup_operations *ops;
	struct lgroup *next;
	struct plot *plot; /* belongs to */
};

#define for_each_line(lg, iter)                                       \
	for (struct line *iter = ((struct lgroup *)(lg))->head; iter; \
	     iter = iter->next)

extern const struct ldraw_ops unicode_bold_line_ops;
extern const struct ldraw_ops unicode_bold_dashed_line_ops;
extern const struct ldraw_ops unicode_line_ops;
extern const struct ldraw_ops unicode_dashed_line_ops;
extern const struct ldraw_ops *ldraw_operations[LINE_TYPE_MAX];

bool ldraw_hasname(const char *name);
enum ltype_enum ldraw_name2type(const char *name);
const struct ldraw_ops *ldraw_type2ops(enum ltype_enum t);
const struct ldraw_ops *ldraw_name2ops(const char *name);
const char *ldraw_type2name(enum ltype_enum t);

int enqueue_llabel(const char *name);
const char *dequeue_llabel(void);
int enqueue_ltype(enum ltype_enum t);
enum ltype_enum dequeue_ltype(void);
int get_nr_ltypes(void);
int enqueue_lcolor(enum lcolor_enum c);
enum lcolor_enum dequeue_lcolor(void);
int get_nr_lcolors(void);
enum lcolor_enum color_name2n(const char *name);
bool hascolor_name(const char *name);
enum lcolor_enum nextcolor(enum lcolor_enum c);

int dequeue_val(struct line *l);
int enqueue_val(struct line *l, double v);
void line_add(struct line *l, double v);
double line_range_max(struct line *l, int start, int len);
double line_range_min(struct line *l, int start, int len);

struct line *new_line(struct lgroup *lg, const char *name, int color);
struct line *new_line_ops(struct lgroup *lg, const char *name, int color,
			  const struct ldraw_ops *ops);
