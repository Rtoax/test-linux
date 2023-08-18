/**
 * Test pointer multi-dimension
 */
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>


struct test_struct {
	int i;
};


void *alloc_mem_internal(void **ptr, size_t size)
{
	void *p = realloc(*ptr, size);
	*ptr = p;
	return p;
}

void *alloc_mem(void **ptr, size_t size)
{
	return alloc_mem_internal(ptr, size);
}

void test_struct_ptr(void)
{
	struct test_struct *test = NULL;

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
