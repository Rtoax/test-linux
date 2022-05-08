/**
 * File: clock_gettime.c
 * Discription: Compare the latency of vDSO, syscall, etc.
 *
 * Author:	Ge Changzhong (gechangzhong@cestc.cn)
 *			Rong Tao (rongtao@cestc.cn)
 *
 * Date: 2022-02-20
 *
 * 2022-03-11 Rong Tao
 *	Add rdtsc clock_gettime() like API.
 *
 * syscall, vDSO, rdtsc latency compare.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX	(1000 * 1000 * 100)
#define longtime(ts)	((ts).tv_sec * 1000000000ULL + (ts).tv_nsec)

typedef enum {
	TEST_SYSCALL,
	TEST_VSYSCALL,
	TEST_VDSO,
#if defined(__x86_64__) && defined(HAVE_DPDK_TSC_FREQ)
	TEST_RDTSC,
#endif
} test_enum;

#if defined(__x86_64__) && defined(HAVE_DPDK_TSC_FREQ)

#include "dpdk/dpdk.h" /* for 'tsc_freq()' */

uint64_t start_tsc = 0;
uint64_t tsc_freq = 0;
struct timespec start_timespec;

/* 读取 TSC */
static inline uint64_t
__rdtsc(void)
{
   unsigned int a, d;
   asm volatile ("rdtsc" : "=a" (a), "=d"(d));
   return ((unsigned long) a) | (((unsigned long) d) << 32);
}

/**
 * 获取程序启动时的 tsc 和 timespec
 * 用来计算 clock_gettime() 的时间
 */
static  __attribute__((constructor(101)))
void ____start_record_tsc_and_freq(void)
{
	start_tsc = __rdtsc();
	/* 如果你已经知道CPU TSC freq, 直接赋值亦可 */
	tsc_freq = get_tsc_freq();
	clock_gettime(CLOCK_REALTIME, &start_timespec);
}

/* see 'vdso/test/dpdk' */
int rdtsc_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	/* 计算程序启动至此接口调用的 tsc 差值 */
	uint64_t tsc_diff = __rdtsc() - start_tsc;
#if defined(ACCURATE_TO_SEC)
	/**
	 * 精确到秒
	 */
	uint64_t time_spend_sec = tsc_diff / tsc_freq;
	
	/* 给当前之间赋值 */
	tp->tv_sec = start_timespec.tv_sec + time_spend_sec;
	tp->tv_nsec = start_timespec.tv_nsec;
#else
	/**
	 * 精确到纳秒
	 */
	uint64_t time_spend_nsec = tsc_diff * 1000000000ULL / tsc_freq;

	tp->tv_nsec = start_timespec.tv_nsec + time_spend_nsec;

	tp->tv_sec = start_timespec.tv_sec + tp->tv_nsec / 1000000000ULL;
	tp->tv_nsec %= 1000000000ULL;

#endif
	return 0;
}
#endif

/* 使用系统调用 */
int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

/* 系统默认使用 vDSO, 无需单独实现 clock_gettime() 接口 */

void func(int cnt, test_enum te)
{
	struct timespec ts;
	int x;

	int (*test_clock_gettime)(clockid_t, struct timespec *) = NULL;

	switch (te) {
	case TEST_VDSO:
		test_clock_gettime = clock_gettime;
		break;
	case TEST_SYSCALL:
		test_clock_gettime = sys_clock_gettime;
		break;
#if defined(__x86_64__) && defined(HAVE_DPDK_TSC_FREQ)
	case TEST_RDTSC:
		test_clock_gettime = rdtsc_clock_gettime;
		break;
#endif
	case TEST_VSYSCALL:
	default:
		assert(0 && "Not support.");
		break;
	}

	for (x = 0; x < cnt; x++) {
		/**
		 * See vsyscall/vdso relate content
		 */
		test_clock_gettime(CLOCK_REALTIME, &ts);
		//printf("%16ld, %16ld\n", ts.tv_sec, ts.tv_nsec);
		/**
		 * Use bpftrace tracing clock_getime, need this
		 */
		//usleep(1);
	}
}

void usage(int argc, char **argv)
{
	printf("Usage: %s [syscall|vdso"
#if defined(__x86_64__) && defined(HAVE_DPDK_TSC_FREQ)
		"|rdtsc"
#endif
		"]\n", argv[0]);
}

int main(int argc, char *argv[])
{
	struct timespec start, end;
	unsigned long long diff_ns;
	test_enum te = TEST_SYSCALL;

	if (argc < 2) {
		usage(argc, argv);
		exit(1);
	}

	if (!strcmp(argv[1], "vdso")) {
		te = TEST_VDSO;
	} else if (!strcmp(argv[1], "syscall")) {
		te = TEST_SYSCALL;
#if defined(__x86_64__) && defined(HAVE_DPDK_TSC_FREQ)
	} else if (!strcmp(argv[1], "rdtsc")) {
		te = TEST_RDTSC;
#endif
	} else {
		usage(argc, argv);
		exit(1);
	}

	clock_gettime(CLOCK_MONOTONIC, &start);
	func(MAX, te);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	diff_ns = longtime(end) - longtime(start);

	printf("diff %lld, (%llf nspc)\n", diff_ns, diff_ns*1.0L / MAX);

	return 0;
}


