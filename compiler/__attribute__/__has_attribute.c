#include <stdio.h>

#ifndef __has_attribute
# warning "Not define __has_attribute()"
# define __has_attribute(x) 0
#endif

int main(void)
{
#if __has_attribute(optimize)
	printf("has optimize\n");
#endif
#if __has_attribute(unused)
	printf("has unused\n");
#endif
	return 0;
}
