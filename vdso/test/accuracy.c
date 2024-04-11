#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>


int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

unsigned long sys_nsecs(void)
{
	struct timespec start;
	sys_clock_gettime(CLOCK_MONOTONIC_COARSE, &start);
	return (start.tv_sec * 1E9 + start.tv_nsec);
}

unsigned long vdso_nsecs(void)
{
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC_COARSE, &start);
	return (start.tv_sec * 1E9 + start.tv_nsec);
}

void test(char *name, unsigned long (*nsecs)(void))
{
	unsigned long start, end, cnt;

	cnt = 0;
	start = end = nsecs();
	/* 5ms */
	while (end - start < 5000000) {
		cnt++;
		end = nsecs();
	}
	printf("%-8s %-16ld %-16ld\n", name, end - start, cnt);
}

int main(int argc, char *argv[])
{
	test("syscall", sys_nsecs);
	test("vdso", vdso_nsecs);
	return 0;
}

