#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ret = getpagesize();
	printf("getpagesize      = %d\n", ret);
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
