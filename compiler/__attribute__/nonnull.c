#include <stdio.h>


#define __my_nonnull1__ __attribute__((nonnull))
#define __my_nonnull2__(params) __attribute__((__nonnull__ params))
#define __my_nonnull3__(params) __attribute__((nonnull params))

extern void print_ptr1(void *p1, void *p2) __my_nonnull3__((1, 2));

extern void *my_memcpy(void *dest, const void *src, size_t len)
	__attribute__((nonnull(1, 2)));

__attribute__((nonnull(1)))
void fun(char *str)
{
	if(str != NULL)
		printf("%s\n", str);
	return;
}

/**
 * if ptr: warning: ‘nonnull’ attribute only applies to function types
 */
void __my_nonnull1__ fun2(char *ptr)
{
	return;
}

int main(void)
{
	fun("asdf");
	fun(NULL);

	return 0;
}

