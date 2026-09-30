// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * Supports handler functions for rapid lookup and retrieval of file
 * descriptors.
 *
 * +----+--------+
 * |id1 |handler1|
 * +----+--------+
 * |id2 |handler2|
 * +----+--------+
 * |... |  ...   |
 * +----+--------+
 * |idN |handlerN|
 * +----+--------+
 */
#include <errno.h>
#include <malloc.h>
#include <search.h>
#include <stddef.h>
#include <stdlib.h>
#include "id-handler.h"

struct id_handler {
	long id;
	void *arg;
	/**
	 * handler return will pass to handle_id()
	 */
	int (*handler)(long id, void *arg);
};

/**
 * If the handler in the interface is NULL, this default is used.
 */
static id_handle_t default_root = NULL;
#define TRY_SET_DEFAULT_AS_ROOT(h)         \
	do {                               \
		if (!h)                    \
			h = &default_root; \
	} while (0)

id_handle_t id_default_root(void)
{
	return default_root;
}

static int id_compare(const void *pa, const void *pb)
{
	const struct id_handler *f1 = pa, *f2 = pb;
	if (f1->id < f2->id)
		return -1;
	if (f1->id > f2->id)
		return 1;
	return 0;
}

struct id_handler *register_id(id_handle_t *handle, long id,
			       int (*handler)(long, void *), void *arg)
{
	struct id_handler *new;

	new = malloc(sizeof(*new));
	new->id = id;
	new->arg = arg;
	new->handler = handler;

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tsearch(new, handle, id_compare);
	if (p == NULL)
		return NULL;
	if (*p != new) {
		free(new);
		return *p;
	}
	return new;
}

int unregister_id(id_handle_t *handle, long id)
{
	struct id_handler h = {
		.id = id,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tfind(&h, handle, id_compare);
	if (p == NULL)
		return -ENOENT;

	struct id_handler *node = *p;
	/**
	 * tdelete() returns a pointer to the parent of the node deleted, or
	 * NULL if the item was not found. If the deleted node was the root
	 * node, tdelete() returns a dangling pointer that must not be accessed.
	 */
	tdelete(&h, handle, id_compare);
	free(node);
	return 0;
}

/**
 * @return: return -ENOENT if not found id.
 */
int handle_id(id_handle_t *handle, long id)
{
	struct id_handler h = {
		.id = id,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tfind(&h, handle, id_compare);
	if (p == NULL)
		return -ENOENT;
	return (*p)->handler(id, (*p)->arg);
}

static void free_id_handler(void *p)
{
#ifdef DEBUG
	struct id_handler *id = p;
	printf("free %ld\n", id->id);
#endif
	free(p);
}

void release_id_handle(id_handle_t *handle)
{
	TRY_SET_DEFAULT_AS_ROOT(handle);
	tdestroy(*handle, free_id_handler);
}

#ifdef TEST_MAIN
#include <time.h>

static void walk_action(const void *nodep, VISIT which, int depth)
{
	const struct id_handler *handler = *(void **)nodep;

	switch (which) {
	case preorder:
		break;
	case postorder:
		printf("%6ld\n", handler->id);
		break;
	case endorder:
		break;
	case leaf:
		printf("%6ld\n", handler->id);
		break;
	}
}

static int my_handler(long id, void *arg)
{
	char *name = arg;
	printf("handle %s has %ld\n", name, id);
	return 0;
}

int main(void)
{
	id_handle_t handle1;

	srand(time(NULL));

	for (unsigned int i = 0; i < 12; i++) {
		register_id(NULL, i, my_handler, "[default]");
		register_id(&handle1, i, my_handler, "[handle1]");
	}

	for (unsigned int i = 0; i < 12; i++) {
		handle_id(NULL, 12 - 1 - i);
		handle_id(&handle1, 12 - 1 - i);
	}

	printf("------------------\n");
	twalk(id_default_root(), walk_action);
	unregister_id(NULL, 3);
	unregister_id(NULL, 8);
	unregister_id(NULL, 9);
	printf("------------------\n");
	twalk(id_default_root(), walk_action);

	printf("------------------\n");
	twalk(handle1, walk_action);
	unregister_id(&handle1, 8);
	printf("------------------\n");
	twalk(handle1, walk_action);

	release_id_handle(NULL);
	release_id_handle(&handle1);
	exit(EXIT_SUCCESS);
}
#endif
