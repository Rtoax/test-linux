/**
 * Test pointer multi-dimension
 */
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include "c_helpers.h"

struct test_struct {
	int i;
};

static struct test_struct *test = NULL;

void test_struct_ptr(void)
{
	alloc_mem((void **)&test, 1024);
	if (test == NULL) {
		fprintf(stderr, "alloc failed.\n");
	}
	memset(test, 'A', 1024);
}

void pass_ptr_ptr(struct test_struct **p)
{
	struct test_struct *t = *p;
	t->i = 1;
}

int main(void)
{
	struct test_struct orig = { .i = 10, };
	struct test_struct *pt = &orig;
	pass_ptr_ptr(&pt);
	return 0;
}
