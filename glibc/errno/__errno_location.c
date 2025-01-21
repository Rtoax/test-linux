#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(void)
{
	extern int *__errno_location(void);
	printf("__errno_location = %p\n", __errno_location);

#ifdef LIBC___ERRNO_LOCATION_SYMADDR
	printf("LIBC___ERRNO_LOCATION_SYMADDR = 0x%x\n", LIBC___ERRNO_LOCATION_SYMADDR);
	/* We could use this to get libc.so.6 load virtual address */
	printf("libc.so.6 load address 0x%lx\n",
		(unsigned long)__errno_location - LIBC___ERRNO_LOCATION_SYMADDR);
#endif

	return 0;
}
