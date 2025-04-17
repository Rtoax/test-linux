#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>

void demo1(void)
{
	size_t i;
	size_t page_size;
	int alloc_size;
	char *mem = NULL;

	page_size = getpagesize();
	alloc_size = 1024 * page_size;
	mem = malloc(alloc_size);
	assert(mem);

/* FIXME: error: 'mem' may be used uninitialized */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	mlock(mem, alloc_size);
#pragma GCC diagnostic pop

	for (i = 0; i < alloc_size; i += page_size)
		mem[i] = 0;

	munlock(mem, alloc_size);
	free(mem);
}

void demo2(void)
{
	int *a = malloc(10 * sizeof(int));
	assert(a);
	printf("%p, %p\n", a, a + 10);

	a[9] = 20;

	mlock(a + 10, 10);

	a = realloc(a, 20);
	assert(a);

	a[18] = 11;
	a[10] = 10;
	a[2] = 12;

	printf("a[10] = %d\n", a[10]);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overread"
	munlock(a + 10, 10);
#pragma GCC diagnostic pop

	free(a);
}

int main(void)
{
	demo1();
	demo2();
	return 0;
}
