#include <stdio.h>
#include <malloc.h>

#include "prefetch.h"

int main(void)
{
	int i;
	int *arr = malloc(sizeof(int) * 1024);
	for (i = 0; i < 1024; i += 64)
		prefetch(&arr[i]);
	free(arr);
	return 0;
}
