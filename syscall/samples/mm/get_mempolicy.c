#include <stdio.h>
#include <errno.h>
#include <numaif.h>

int tl_numa_available(void)
{
	if (get_mempolicy(NULL, NULL, 0, 0, 0) < 0 && (errno == ENOSYS || errno == EPERM))
		return -1;
	return 0;
}

int main(void)
{
	int ret;

	ret = tl_numa_available();
	printf("tl_numa_available return %d\n", ret);

	return 0;
}
