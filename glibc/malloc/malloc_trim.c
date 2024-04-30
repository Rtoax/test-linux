#include <stdio.h>
#include <malloc.h>

#include "helpers.h"

int main(void)
{
	char *p1, *p2;
	p1 = malloc(1024);
	(void)p1;
	print_mallinfo();
	p2 = malloc(2024);
	(void)p2;
	print_mallinfo();
	malloc_trim(0);
	print_mallinfo();
}

