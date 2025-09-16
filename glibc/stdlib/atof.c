#include <stdio.h>
#include <stdlib.h>

void test_atoi(void)
{
	char *null = NULL;
	/* Segfault here */
	printf("%d\n", atoi(null));
}

int main(int argc, char *argv[])
{
	char *a = "123abc";

	printf("%d\n", atoi(a));
	printf("%f\n", atof(a));
	printf("%ld\n", atol(a));
	printf("%Ld\n", atoll(a));

	return 0;
}
