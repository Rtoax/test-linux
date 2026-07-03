// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"
#include "plot.h"

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

static struct key_handler *find_handler(struct keyboard *k, int key)
{
	struct key_handler find = {
		.key = key,
	};

	return bsearch(&find, k->handlers, k->nr_handlers,
		       sizeof(struct key_handler), key_cmp);
}

int register_key_handler(struct keyboard *k, int key, void *arg,
			 key_handler_fn handler)
{
	struct key_handler *news, *new;

	if (!k)
		return -EINVAL;

	/* already register */
	if (find_handler(k, key))
		return -EEXIST;

	news = realloc(k->handlers,
		       sizeof(struct key_handler) * ++k->nr_handlers);
	assert(news && "Alloc key handler failed");

	k->handlers = news;
	new = &k->handlers[k->nr_handlers - 1];

	new->key = key;
	new->arg = arg;
	new->handler = handler;

	qsort(k->handlers, k->nr_handlers, sizeof(struct key_handler), key_cmp);

	return 0;
}

int exec_key_handler(struct keyboard *k, int key)
{
	if (!k)
		return -EINVAL;

	struct key_handler *handler = find_handler(k, key);
	if (!handler) {
		return -ENOENT;
	}
	return handler->handler(key, handler->arg);
}
