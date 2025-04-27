#include <stdio.h>
#include <malloc.h>

#include "malloc_helpers.h"

int main(void)
{
	char *p1 = malloc(1024);
	print_mallinfo();
	free(p1);
	p1 = malloc(2024);
	print_mallinfo();
	free(p1);
}
