#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

int compare(const void *x, const void *y)
{
	const int _x = *(int *)x;
	const int _y = *(int *)y;
	return (_x - _y);
}

int demo(void)
{
	int array[5] = {35, 12, 54 ,78, 99};
	size_t nelem = 5;
	int key = 12;

	/* linear search of an array */
	void *result = lfind(&key, array, &nelem, sizeof(int), compare);
	if (result)
		printf("Number %d found, result=%p\n", key, result);
	else
		printf("Number %d not found, result=%p\n", key, result);
	return 0;
}

int main(void)
{
	demo();
	return 0;
}
