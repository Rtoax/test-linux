/**
 * glibc:
 * char *__libc_version;
 * char *__libc_release;
 */
#include <stdio.h>
#include <features.h>
#include <gnu/libc-version.h>

#define __MY_GLIBC_PREREQ(maj, min) \
	((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))

#if __MY_GLIBC_PREREQ(22, 22) != __GLIBC_PREREQ(22, 22)
#error "Glibc __GLIBC_PREREQ() macro has been changed"
#endif

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
