#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *p1 = malloc(136);
	printf("size %ld.\n", malloc_usable_size(p1));
	return 0;
}

