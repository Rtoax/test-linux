/**
 * The  malloc_trim() function attempts to release free memory from the heap.
 * by calling brk(2), sbrk(2) or madvise(2) with suitable arguments.
 *
 * $ sudo strace -e trace=madvise,brk ./malloc_trim
 */
#include <stdio.h>
#include <malloc.h>

#include "helpers.h"

int main(void)
{
	char *p1, *p2;

	p1 = malloc(1024);
	printf("p1 %p\n", p1);

	print_mallinfo();

	p2 = malloc(2024);
	printf("p2 %p\n", p2);

	print_mallinfo();

	printf("release free memory from the heap\n");
	malloc_trim(0);

	print_mallinfo();

	return 0;
}

