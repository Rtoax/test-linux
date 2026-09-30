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
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <errno.h>
#include <malloc.h>
#include <search.h>
#include <stddef.h>
#include <stdlib.h>
#include "id-handler.h"

static int id_compare_ascend(const void *pa, const void *pb)
{
	const struct id_handler *f1 = pa, *f2 = pb;
	return f1->id - f2->id;
}

static int id_compare_descend(const void *pa, const void *pb)
{
	const struct id_handler *f1 = pa, *f2 = pb;
	return f2->id - f1->id;
}

/**
 * If the handler in the interface is NULL, this default is used.
 */
static struct id_handle_st default_root = { NULL, id_compare_ascend };
#define TRY_SET_DEFAULT_AS_ROOT(h)         \
	do {                               \
		if (!h)                    \
			h = &default_root; \
	} while (0)

id_handle_t id_default_root(void)
{
	return &default_root;
}

/**
 * @return: id_handle_t, release with free(3)
 */
id_handle_t create_id_handler(int (*id_cmp)(const void *, const void *))
{
	id_handle_t h = malloc(sizeof(struct id_handle_st));
	h->root = NULL;
	switch ((unsigned long)id_cmp) {
	case (unsigned long)ID_CMP_ASCENDING_ORDER:
		h->id_cmp = id_compare_ascend;
		break;
	case (unsigned long)ID_CMP_DESCENDING_ORDER:
		h->id_cmp = id_compare_descend;
		break;
	default:
		h->id_cmp = id_cmp;
		break;
	}
	return h;
}

struct id_handler *register_id(id_handle_t handle, long id,
			       int (*handler)(long, void *), void *arg)
{
	struct id_handler *new;

	new = malloc(sizeof(*new));
	new->id = id;
	new->arg = arg;
	new->handler = handler;

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tsearch(new, &handle->root, handle->id_cmp);
	if (p == NULL)
		return NULL;
	if (*p != new) {
		free(new);
		return *p;
	}
#ifdef DEBUG
	fprintf(stderr, "register_id() = %p\n", new);
#endif
	return new;
}

int unregister_id(id_handle_t handle, long id)
{
	struct id_handler h = {
		.id = id,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tfind(&h, &handle->root, handle->id_cmp);
	if (p == NULL)
		return -ENOENT;

	struct id_handler *node = *p;
	/**
	 * tdelete() returns a pointer to the parent of the node deleted, or
	 * NULL if the item was not found. If the deleted node was the root
	 * node, tdelete() returns a dangling pointer that must not be accessed.
	 */
	tdelete(&h, &handle->root, handle->id_cmp);
	free(node);
	return 0;
}

/**
 * @return: return -ENOENT if not found id.
 */
int handle_id(id_handle_t handle, long id)
{
	struct id_handler h = {
		.id = id,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct id_handler **p = tfind(&h, &handle->root, handle->id_cmp);
	if (p == NULL)
		return -ENOENT;
	return (*p)->handler(id, (*p)->arg);
}

struct foreach_closure_arg_st {
	void (*fn)(const struct id_handler *, void *arg);
	void *fn_arg;
	int count;
};

static void __one_handler(const void *nodep, VISIT which, void *closure)
{
	const struct id_handler *handler = *(struct id_handler **)nodep;
	struct foreach_closure_arg_st *arg = closure;

	if (which != postorder && which != leaf)
		return;

	arg->fn(handler, arg->fn_arg);
	arg->count++;
}

int for_each_id(id_handle_t handle,
		void (*fn)(const struct id_handler *, void *arg), void *fn_arg)
{
	struct foreach_closure_arg_st arg = {
		.fn = fn,
		.fn_arg = fn_arg,
		.count = 0,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	twalk_r(handle->root, __one_handler, &arg);
	return arg.count;
}

static void free_id_handler(void *p)
{
#ifdef DEBUG
	struct id_handler *id = p;
	printf("free %ld\n", id->id);
#endif
	free(p);
}

void release_id_handle(id_handle_t handle)
{
	TRY_SET_DEFAULT_AS_ROOT(handle);
	tdestroy(handle->root, free_id_handler);
}

#ifdef TEST_MAIN
#include <time.h>

static void for_each(const struct id_handler *h, void *arg)
{
	printf("%p -> %ld\n", h, h->id);
}

static int my_handler(long id, void *arg)
{
	char *name = arg;
	printf("handle %s has %ld\n", name, id);
	return 0;
}

int main(void)
{
	int n;
	id_handle_t handle1 = create_id_handler(ID_CMP_DESCENDING_ORDER);

	srand(time(NULL));

	for (unsigned int i = 0; i < 12; i++) {
		register_id(NULL, i, my_handler, "[default]");
		register_id(handle1, i, my_handler, "[handle1]");
	}

	for (unsigned int i = 0; i < 12; i++) {
		handle_id(NULL, 12 - 1 - i);
		handle_id(handle1, 12 - 1 - i);
	}

	printf("------------------\n");
	n = for_each_id(NULL, for_each, NULL);
	printf("                  %d\n", n);

	printf("------------------\n");
	unregister_id(NULL, 3);
	unregister_id(NULL, 8);
	unregister_id(NULL, 9);
	n = for_each_id(NULL, for_each, NULL);
	printf("                  %d\n", n);

	printf("------------------\n");
	n = for_each_id(handle1, for_each, NULL);
	printf("                  %d\n", n);

	printf("------------------\n");
	unregister_id(handle1, 8);
	n = for_each_id(handle1, for_each, NULL);
	printf("                  %d\n", n);

	release_id_handle(NULL);
	release_id_handle(handle1);

	free(handle1);

	exit(EXIT_SUCCESS);
}
#endif
