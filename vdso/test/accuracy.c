/**
 * Get syscall/vdso clock_gettime() accuracy
 *
 * Copyright 2024 Rong Tao.
 *
 * 2024-04-11	Rong Tao	Create this.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>

/* 5ms */
unsigned long diff_ns = 5000000;

int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

unsigned long sys_nsecs(clockid_t clockid)
{
	struct timespec start;
	sys_clock_gettime(clockid, &start);
	return (start.tv_sec * 1E9 + start.tv_nsec);
}

unsigned long vdso_nsecs(clockid_t clockid)
{
	struct timespec start;
	clock_gettime(clockid, &start);
	return (start.tv_sec * 1E9 + start.tv_nsec);
}

void test(char *name, unsigned long (*nsecs)(clockid_t), clockid_t clockid)
{
	unsigned long start, end, cnt;

	cnt = 0;
	start = end = nsecs(clockid);
	while (end - start < diff_ns) {
		cnt++;
		end = nsecs(clockid);
	}
	printf("%-48s %-16ld %-16ld\n", name, end - start, cnt);
}

int main(int argc, char *argv[])
{
	fprintf(stderr, "%s [ns (default:%ld)]\n", argv[0], diff_ns);

	if (argc > 1) {
		diff_ns = strtoul(argv[1], NULL, 10);
		fprintf(stderr, "change ns to %ld\n", diff_ns);
	}

	printf("%-48s %-16s %-16s\n", "NAME", "DIFF(ns)", "COUNT");
	printf("%-48s %-16s %-16s\n", "----", "--------", "-----");
	test("syscall REALTIME", sys_nsecs, CLOCK_REALTIME);
#if defined(__x86_64__) /* aarch64 run this clockid is too slow. */
	test("syscall REALTIME_ALARM", sys_nsecs, CLOCK_REALTIME_ALARM);
#endif
	test("syscall REALTIME_COARSE", sys_nsecs, CLOCK_REALTIME_COARSE);
	test("syscall MONOTONIC", sys_nsecs, CLOCK_MONOTONIC);
	test("syscall MONOTONIC_COARSE", sys_nsecs, CLOCK_MONOTONIC_COARSE);
	test("syscall MONOTONIC_RAW", sys_nsecs, CLOCK_MONOTONIC_RAW);
	test("syscall PROCESS_CPUTIME_ID", sys_nsecs, CLOCK_PROCESS_CPUTIME_ID);
	test("vdso    REALTIME", vdso_nsecs, CLOCK_REALTIME);
#if defined(__x86_64__)
	test("vdso    REALTIME_ALARM", vdso_nsecs, CLOCK_REALTIME_ALARM);
#endif
	test("vdso    REALTIME_COARSE", vdso_nsecs, CLOCK_REALTIME_COARSE);
	test("vdso    MONOTONIC", vdso_nsecs, CLOCK_MONOTONIC);
	test("vdso    MONOTONIC_COARSE", vdso_nsecs, CLOCK_MONOTONIC_COARSE);
	test("vdso    MONOTONIC_RAW", vdso_nsecs, CLOCK_MONOTONIC_RAW);
	test("vdso    PROCESS_CPUTIME_ID", vdso_nsecs, CLOCK_PROCESS_CPUTIME_ID);
	return 0;
}

