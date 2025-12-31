/**
 * Test with vvar_fault.bt
 */
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

int main(int argc, char *argv[])
{
	struct timespec ts;

	/**
	 * 1. sys_clock_gettime(2) will not call vvar_fault.
	 */
	sleep(4);
	sys_clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("Call syscall clock_gettime(2).\n");

	/**
	 * 2. When vDSO call happened, vvar_fault executed.
	 */
	sleep(4);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("Call vDSO clock_gettime(2).\n");

	/**
	 * 3. When vDSO call happened, vvar_fault executed.
	 */
	sleep(4);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("Call vDSO clock_gettime(2) again.\n");

	return 0;
}
