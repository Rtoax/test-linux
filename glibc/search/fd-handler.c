#include <errno.h>
#include <search.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct fd_handler {
	int fd;
	void *arg;
	int (*handler)(int fd, void *arg);
};

static void *fd_handler_root = NULL;

int my_handler(int fd, void *arg)
{
	printf("handle %d\n", fd);
	return 0;
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

static void free_fd_handler(void *p)
{
	struct fd_handler *fd = p;
	printf("free %d\n", fd->fd);
	free(p);
}

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

int main(void)
{
	srand(time(NULL));

	for (unsigned int i = 0; i < 12; i++) {
		register_fd(i, my_handler, NULL);
	}

	for (unsigned int i = 0; i < 12; i++) {
		handle_fd(12 - 1 - i);
	}

	twalk(fd_handler_root, walk_action);
	unregister_fd(3);
	unregister_fd(8);
	unregister_fd(9);
	twalk(fd_handler_root, walk_action);

	tdestroy(fd_handler_root, free_fd_handler);
	exit(EXIT_SUCCESS);
}
