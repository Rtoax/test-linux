/**
 * BST - Binary Search Tree
 * see tsearch(3)
 */
#include <search.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static void action(const void *nodep, VISIT which, int depth)
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
	twalk(root, action);
	tdestroy(root, free);
	exit(EXIT_SUCCESS);
}
