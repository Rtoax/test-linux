/**
 * BST - Binary Search Tree
 * see tsearch(3)
 */
#include <search.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * glibc glibc-2.29.9000-225-g7b807a35a8dc
 * commit 7b807a35a8dc ("misc: Add twalk_r function")
 */
#if __GLIBC_PREREQ(2, 29)
#define USE_TWALK_R 1
#endif

static void *root = NULL;

static void *xmalloc(size_t n)
{
	void *p;

	p = malloc(n);
	if (p)
		return p;
	fprintf(stderr, "insufficient memory\n");
	exit(EXIT_FAILURE);
}

static int compare(const void *pa, const void *pb)
{
	if (*(int *)pa < *(int *)pb)
		return -1;
	if (*(int *)pa > *(int *)pb)
		return 1;
	return 0;
}

#ifdef USE_TWALK_R
static void walk_action(const void *nodep, VISIT which, void *closure)
#else
static void walk_action(const void *nodep, VISIT which, int depth)
#endif
{
	int *datap;

	switch (which) {
	case preorder:
		break;
	case postorder:
		datap = *(int **)nodep;
		printf("%6d\n", *datap);
		break;
	case endorder:
		break;
	case leaf:
		datap = *(int **)nodep;
		printf("%6d\n", *datap);
		break;
	}
}

int main(void)
{
	int *ptr;
	int **val;

	srand(time(NULL));
	for (unsigned int i = 0; i < 12; i++) {
		ptr = xmalloc(sizeof(*ptr));
		*ptr = rand() & 0xff;
		val = tsearch(ptr, &root, compare);
		if (val == NULL)
			exit(EXIT_FAILURE);
		if (*val != ptr)
			free(ptr);
	}
#ifdef USE_TWALK_R
	twalk_r(root, walk_action, NULL);
#else
	twalk(root, walk_action);
#endif
	tdestroy(root, free);
	exit(EXIT_SUCCESS);
}
