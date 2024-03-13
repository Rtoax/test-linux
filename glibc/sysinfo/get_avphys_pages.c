#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>


int main(void)
{
	long int ret;

	ret = getpagesize();
	printf("getpagesize() = %ld\n", ret);

	ret = sysconf(_SC_PHYS_PAGES);
	printf("sysconf(_SC_PHYS_PAGES) = %ld\n", ret);

	ret = sysconf(_SC_AVPHYS_PAGES);
	printf("sysconf(_SC_AVPHYS_PAGES) = %ld\n", ret);

	ret = get_phys_pages();
	printf("get_phys_pages() = %ld\n", ret);

	ret = get_avphys_pages();
	printf("get_avphys_pages() = %ld\n", ret);

	return 0;
}
