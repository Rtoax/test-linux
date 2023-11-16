#include <stdio.h>
#include "__nonnull.h"


int __nonnull((1)) print_ptr(void *ptr)
{
	return printf("ptr: %p\n", ptr);
}

int main(void)
{
	int i = 0;
	print_ptr(&i);
	/* error: argument 1 null where non-null expected [-Werror=nonnull] */
	//print_ptr(NULL);
	return 0;
}
