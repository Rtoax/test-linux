#include <stdio.h>

#ifndef __MUSL__
#error "Not define __MUSL__"
#endif

int main(void)
{
	printf("musl libc version: %d.%d\n", __MUSL_VERSION_MAJOR__,
	       __MUSL_VERSION_MINOR__);
	return 0;
}
