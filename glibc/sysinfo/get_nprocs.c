#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>


int main(void)
{
	long int ret;

	/* processors available */
	ret = sysconf(_SC_NPROCESSORS_ONLN);
	printf("sysconf(_SC_NPROCESSORS_ONLN) = %ld\n", ret);

	ret = get_nprocs();
	printf("get_nprocs() = %ld\n", ret);

	/* processors configured */
	ret = sysconf(_SC_NPROCESSORS_CONF);
	printf("sysconf(_SC_NPROCESSORS_CONF) = %ld\n", ret);

	ret = get_nprocs_conf();
	printf("get_nprocs_conf() = %ld\n", ret);

	return 0;
}
