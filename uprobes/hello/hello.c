#include <stdio.h>

int print_hello(int a)
{
	printf("Hello World. %d\n", a);
	return 0;
}

int main(void)
{
	print_hello(3);
	return 0;
}
