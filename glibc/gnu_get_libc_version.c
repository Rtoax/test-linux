/**
 * glibc:
 * char *__libc_version;
 * char *__libc_release;
 */
#include <stdio.h>
#include <gnu/libc-version.h>

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
# if __GLIBC_PREREQ(2, 16)
#  include <sys/auxv.h>
# endif
#endif

int main(void)
{
	puts(gnu_get_libc_version());
	puts(gnu_get_libc_release());
	printf("__GLIBC__ = %d\n", __GLIBC__);
	printf("__GLIBC_MINOR__ = %d\n", __GLIBC_MINOR__);
	return 0;
}
