#include <stdio.h>

#pragma GCC target("no-avx")
int fun(void)
{
	printf("fun\n");
	return 0;
}

int main(void)
{
	fun();
	printf("main\n");
	return 0;
}
