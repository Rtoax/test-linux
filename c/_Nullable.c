#include <math.h>
#include <stdio.h>


#if defined(__clang__)
int print_ptr(void *_Nullable ptr)
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
	print_ptr(NULL);
	return 0;
}
