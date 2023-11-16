#include <stdio.h>


#define __my_nonnull__(params) __attribute__((__nonnull__ params))
#define my_nonnull(params) __attribute__((nonnull params))

extern void print_ptr(void *p1, void *p2) my_nonnull((1, 2));

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

