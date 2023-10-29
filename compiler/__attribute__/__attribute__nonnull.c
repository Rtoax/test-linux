#include <stdio.h>

extern void *my_memcpy(void *dest, const void *src, size_t len)
	__attribute__((nonnull(1, 2)));

void __attribute__((noreturn)) __attribute__((nonnull(1)))
fun(char *str)
{
	if(str != NULL)
		printf("%s\n", str);
	return;
}

int main(void)
{
	fun("asdf");
	fun(NULL);

	return 0;
}