#include <stdio.h>

int main(void)
{
	unsigned long ul = 0;

	if (ul == (unsigned long)NULL)
		printf("0 == (unsigned long)NULL\n");

	if ((void*)0 == NULL)
		printf("void *0 == NULL\n");

	return 0;
}
