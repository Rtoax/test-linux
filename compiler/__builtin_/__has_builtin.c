#include <stdio.h>

#ifndef __has_builtin
# error "Not define __has_builtin()"
# define __has_builtin(x) 0
#endif

int main(void)
{
#if __has_builtin(__builtin_prefetch)
	printf("has __builtin_prefetch\n");
#endif
	return 0;
}
