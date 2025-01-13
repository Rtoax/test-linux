#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
	int *a;

	a = malloc(12);
	a = realloc(a, 20);
	free(a);
	a = NULL;

	a = realloc(NULL, 20);
	a[1] = 9;
	free(a);

	return 0;
}
