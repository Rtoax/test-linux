#include <stdio.h>
#include <unistd.h>

int foo(int a, int b)
{
	return a + b;
}

int main(int argc, char *argv[])
{
	printf("The result is: %d\n", foo(3, 5));
	return 0;
}
