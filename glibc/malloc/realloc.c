#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
	int *a = malloc(12);
	a = realloc(a, 20);
	free(a);
	return 0;
}
