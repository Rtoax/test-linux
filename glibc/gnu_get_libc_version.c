#include <stdio.h>
#include <gnu/libc-version.h>

int main (void)
{
	puts(gnu_get_libc_version());
	printf("__GLIBC__ = %d\n", __GLIBC__);
	printf("__GLIBC_MINOR__ = %d\n", __GLIBC_MINOR__);
	return 0;
}
