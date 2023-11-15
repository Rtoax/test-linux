#include <stdio.h>

int hello(void)
{
	return printf("Hello %s.\n", "World");
}

int main(void)
{
	return hello();
}
