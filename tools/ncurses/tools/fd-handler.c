// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * Supports handler functions for rapid lookup and retrieval of file
 * descriptors.
 *
 * +----+--------+
 * |fd1 |handler1|
 * +----+--------+
 * |fd2 |handler2|
 * +----+--------+
 * |... |  ...   |
 * +----+--------+
 * |fdN |handlerN|
 * +----+--------+
 *
 * see also test-linux/glibc/search/fd-handler.c
 */
#include <errno.h>
#include <malloc.h>
#include <search.h>
#include <stddef.h>
#include <stdlib.h>
#include "fd-handler.h"

struct fd_handler {
	int fd;
	void *arg;
	/**
	 * handler return will pass to handle_fd()
	 */
	int (*handler)(int fd, void *arg);
};

/**
 * If the handler in the interface is NULL, this default is used.
 */
static fd_handle_t default_root = NULL;
#define TRY_SET_DEFAULT_AS_ROOT(h)         \
	do {                               \
		if (!h)                    \
			h = &default_root; \
	} while (0)

fd_handle_t fd_default_root(void)
{
	return default_root;
}

static int fd_compare(const void *pa, const void *pb)
{
	const struct fd_handler *f1 = pa, *f2 = pb;
	if (f1->fd < f2->fd)
		return -1;
	if (f1->fd > f2->fd)
		return 1;
	return 0;
}

struct fd_handler *register_fd(fd_handle_t *handle, int fd,
			       int (*handler)(int, void *), void *arg)
{
	struct fd_handler *new;

	new = malloc(sizeof(*new));
	new->fd = fd;
	new->arg = arg;
	new->handler = handler;

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct fd_handler **p = tsearch(new, handle, fd_compare);
	if (p == NULL)
		return NULL;
	if (*p != new) {
		free(new);
		return *p;
	}
	return new;
}

int unregister_fd(fd_handle_t *handle, int fd)
{
	struct fd_handler h = {
		.fd = fd,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct fd_handler **p = tfind(&h, handle, fd_compare);
	if (p == NULL)
		return -ENOENT;

	struct fd_handler *node = *p;
	/**
	 * tdelete() returns a pointer to the parent of the node deleted, or
	 * NULL if the item was not found. If the deleted node was the root
	 * node, tdelete() returns a dangling pointer that must not be accessed.
	 */
	tdelete(&h, handle, fd_compare);
	free(node);
	return 0;
}

/**
 * @return: return -ENOENT if not found fd.
 */
int handle_fd(fd_handle_t *handle, int fd)
{
	struct fd_handler h = {
		.fd = fd,
	};

	TRY_SET_DEFAULT_AS_ROOT(handle);

	struct fd_handler **p = tfind(&h, handle, fd_compare);
	if (p == NULL)
		return -ENOENT;
	return (*p)->handler(fd, (*p)->arg);
}

static void free_fd_handler(void *p)
{
#ifdef DEBUG
	struct fd_handler *fd = p;
	printf("free %d\n", fd->fd);
#endif
	free(p);
}

void release_fd_handle(fd_handle_t *handle)
{
	TRY_SET_DEFAULT_AS_ROOT(handle);
	tdestroy(*handle, free_fd_handler);
}

#ifdef TEST_MAIN
#include <time.h>

static void walk_action(const void *nodep, VISIT which, int depth)
{
	const struct fd_handler *handler = *(void **)nodep;

	switch (which) {
	case preorder:
		break;
	case postorder:
		printf("%6d\n", handler->fd);
		break;
	case endorder:
		break;
	case leaf:
		printf("%6d\n", handler->fd);
		break;
	}
}

static int my_handler(int fd, void *arg)
{
	printf("handle %d\n", fd);
	return 0;
}

int main(void)
{
	srand(time(NULL));

	for (unsigned int i = 0; i < 12; i++) {
		register_fd(NULL, i, my_handler, NULL);
	}

	for (unsigned int i = 0; i < 12; i++) {
		handle_fd(NULL, 12 - 1 - i);
	}

	twalk(fd_default_root(), walk_action);
	unregister_fd(NULL, 3);
	unregister_fd(NULL, 8);
	unregister_fd(NULL, 9);
	twalk(fd_default_root(), walk_action);

	release_fd_handle(NULL);
	exit(EXIT_SUCCESS);
}
#endif
