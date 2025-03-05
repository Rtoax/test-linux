/**
 * The  malloc_trim() function attempts to release free memory from the heap.
 * by calling brk(2), sbrk(2) or madvise(2) with suitable arguments.
 *
 * $ sudo strace -e trace=madvise,brk ./malloc_trim
 *
 * trim: 修剪, 消减
 */
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#include "helpers.h"

int main(void)
{
	char *p1, *p2;
	size_t size = getpagesize();

	p1 = malloc(size);
	printf("p1 %p\n", p1);

	print_mallinfo();

	p2 = malloc(size);
	printf("p2 %p\n", p2);

	print_mallinfo();

	printf("release free memory from the heap\n");
	malloc_trim(size * 2);

	print_mallinfo();

	free(p1);
	free(p2);
	return 0;
}

