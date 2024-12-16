#include <stdio.h>

#define __const __attribute__((const))

int square(int a) __const;
int square(int a)
{
	return a * a;
}

int main(int argc, char *argv[])
{
	int a = 5;
	printf("%d\n", square(5));
	printf("%d\n", square(a));
	printf("%d\n", square(argc));
	return 0;
}
