#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mcheck.h>

int main(void)
{
	int *a = malloc(12);
	mtrace();
	free(a);
	return 0;
}
