#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>


#ifdef __NR_getpagesize
int sys_getpagesize(void)
{
	return syscall(__NR_getpagesize);
}
#endif

int main(void)
{
	int ret;

	ret = getpagesize();
	printf("getpagesize      = %dBytes (%dKB)\n", ret, ret / 1024);

	ret = sysconf(_SC_PAGESIZE);
	printf("_SC_PAGESIZE     = %d\n", ret);

	/*
	 * Widely available on System V derived systems is a method to get
	 * information about the physical memory the system has. The call
	 */
	ret = sysconf(_SC_PHYS_PAGES);
	printf("_SC_PHYS_PAGES   = %d\n", ret);

	ret = sysconf(_SC_AVPHYS_PAGES);
	printf("_SC_AVPHYS_PAGES = %d\n", ret);

	return 0;
}
