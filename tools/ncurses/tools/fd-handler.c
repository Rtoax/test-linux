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
#include "utils.h"
#include "fd-handler.h"

struct fd_handler {
	int fd;
	void *arg;
	/**
	 * handler return will pass to handle_fd()
	 */
	int (*handler)(int fd, void *arg);
};

static void *fd_handler_root = NULL;

static int fd_compare(const void *pa, const void *pb)
{
	const struct fd_handler *f1 = pa, *f2 = pb;
	if (f1->fd < f2->fd)
		return -1;
	if (f1->fd > f2->fd)
		return 1;
	return 0;
}

struct fd_handler *register_fd(int fd, int (*handler)(int, void *), void *arg)
{
	struct fd_handler *new;

	new = malloc(sizeof(*new));
	new->fd = fd;
	new->arg = arg;
	new->handler = handler;

	struct fd_handler **p = tsearch(new, &fd_handler_root, fd_compare);
	if (p == NULL)
		return NULL;
	if (*p != new) {
		free(new);
		return *p;
	}
	return new;
}

int unregister_fd(int fd)
{
	struct fd_handler h = {
		.fd = fd,
	};

	struct fd_handler **p = tfind(&h, &fd_handler_root, fd_compare);
	if (p == NULL)
		return -ENOENT;

	struct fd_handler *node = *p;
	/**
	 * tdelete() returns a pointer to the parent of the node deleted, or
	 * NULL if the item was not found. If the deleted node was the root
	 * node, tdelete() returns a dangling pointer that must not be accessed.
	 */
	tdelete(&h, &fd_handler_root, fd_compare);
	free(node);
	return 0;
}

/**
 * @return: return -ENOENT if not found fd.
 */
int handle_fd(int fd)
{
	struct fd_handler h = {
		.fd = fd,
	};
	struct fd_handler **p = tfind(&h, &fd_handler_root, fd_compare);
	if (p == NULL)
		return -ENOENT;
	return (*p)->handler(fd, (*p)->arg);
}

void release_fd_handlers(void)
{
	tdestroy(fd_handler_root, free);
}
