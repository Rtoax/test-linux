#include <math.h>
#include <stdio.h>


#if defined(__clang__)
int print_ptr(void *_Nonnull ptr)
#else
int print_ptr(void *ptr)
#endif
{
	return printf("ptr: %p\n", ptr);
}

int main(void)
{
	int i = 1;
	print_ptr(&i);
#if !defined(__clang__)
	/**
	 * Compile error/warning
	 * error: null passed to a callee that requires a non-null argument [-Werror,-Wnonnull]
	 */
	print_ptr(NULL);
#endif
	return 0;
}
