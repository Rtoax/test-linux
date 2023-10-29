#include <stdio.h>

void clean_up(void)
{
	printf("clean up\n");
}

void __attribute__((cleanup(clean_up)))
fun(void)
{
	printf("fun\n");
}

int main(void)
{
	fun();
	return 0;
}