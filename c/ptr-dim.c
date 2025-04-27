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

int main(void)
{

	return 0;
}
