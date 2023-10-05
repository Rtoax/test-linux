/**
 * Module Specific Register - MSR
 */
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/types.h>

#define RTE_EXEC_ENV_LINUX

static int32_t
rdmsr(int msr, uint64_t *val)
{
#ifdef RTE_EXEC_ENV_LINUX
	int fd, ret;

	fd = open("/dev/cpu/0/msr", O_RDONLY);
	if (fd < 0)
		return fd;
	ret = pread(fd, val, sizeof(uint64_t), msr);
	close(fd);
	return ret;
#else
	RTE_SET_USED(msr);
	RTE_SET_USED(val);
	return -1;
#endif
}

int main(void)
{
	uint64_t tsc_hz = 0;
	int32_t ret = rdmsr(0xCE, &tsc_hz);
	printf("MSR(rte = %d) - tsc_hz = %ld\n", ret, tsc_hz);
}
