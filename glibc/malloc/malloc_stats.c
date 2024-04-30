#include <stdio.h>
#include <malloc.h>


int main(void)
{
	char *p1 = malloc(1039);

	malloc_stats();

	free(p1);
}

