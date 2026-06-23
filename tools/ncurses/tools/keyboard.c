// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"
#include "plot.h"

static struct key_handler *handlers = NULL;
static int nr_handlers = 0;

int keyboard_init(struct keyboard *k)
{
	memset(k, 0, sizeof(*k));
	return 0;
}

static int key_cmp(const void *k1, const void *k2)
{
	return ((struct key_handler *)k1)->key -
	       ((struct key_handler *)k2)->key;
}

int register_key_handler(int key, void *arg, key_handler_fn handler)
{
	struct key_handler *news, *new;

	news = realloc(handlers, sizeof(struct key_handler) * ++nr_handlers);
	assert(news && "Alloc key handler failed");

	handlers = news;
	new = &handlers[nr_handlers - 1];

	new->key = key;
	new->arg = arg;
	new->handler = handler;

	qsort(handlers, nr_handlers, sizeof(struct key_handler), key_cmp);

	return 0;
}

int exec_key_handler(int key)
{
	struct key_handler *handler, find = {
		.key = key,
	};
	handler = bsearch(&find, handlers, nr_handlers,
			  sizeof(struct key_handler), key_cmp);
	if (!handler) {
		return -ENOENT;
	}
	handler->handler(key, handler->arg);
	return 0;
}
