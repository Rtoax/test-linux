#pragma once
/**
 * 从奔腾系列开始，Intel x86 处理器中增加了一个 64 位时间戳寄存器 TSC
 * 每经过一个时钟周期，该寄存器+1，及其重启时，该寄存器将清空。
 *
 * rdtsc 指一条机器指令，用于读取该时间戳寄存器中的值。
 *
 * 查询CPU主频：
 * $ cat /proc/cpuinfo | grep cpu | grep  MHz | sed -e 's/.*:[^0-9]//'
*/

#include <stdint.h>

#include "utils.h"

unsigned long timer_get_ticks(void)
{
	union {
		unsigned long tsc_64;
		struct {
			unsigned int lo_32;
			unsigned int hi_32;
		};
	} tsc;

	__asm volatile("rdtsc" : "=a" (tsc.lo_32), "=d" (tsc.hi_32));

	 return ((unsigned long)tsc.tsc_64);
}

/**
 * Return the current value of the fine-grain CPU cycle counter
 * (accessed via the RDTSC instruction).
 */
/**
 * RDTSC - Read Time-Stamp Counter
 *
 * The RDTSC instruction is not a serializing instruction. It does not
 * necessarily wait until all previous instructions have been executed before
 * reading the counter.
 *
 * link: https://www.felixcloutier.com/x86/rdtsc
 */
static inline __always_inline__
uint64_t rdtsc()
{
	uint32_t lo, hi;

	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));

	return (((uint64_t)hi << 32) | lo);
}

static inline __always_inline__
uint64_t rdtsc_fence()
{
	uint32_t lo, hi;

	__asm__ __volatile__("lfence; rdtsc" : "=a" (lo), "=d" (hi));

	return (((uint64_t)hi << 32) | lo);
}

/**
 * RDTSCP - Read Time-Stamp Counter and Processor ID
 *
 * The RDTSCP instruction is not a serializing instruction, but it does wait
 * until all previous instructions have executed and all previous loads are
 * globally visible.
 *
 * link: https://www.felixcloutier.com/x86/rdtscp
 */
static inline __always_inline__
uint64_t rdtscp(uint32_t *aux)
{
	uint32_t lo, hi;
	uint32_t rcx;

	__asm__ __volatile__("rdtscp" : "=a" (lo), "=d" (hi), "=c" (rcx) : : );

	/**
	 * if $ taskset -c 1 ./rdtscp_user
	 * then rcx = 1
	 */
	*aux = rcx;

	return (((uint64_t)hi << 32) | lo);
}
static inline __always_inline__
uint64_t rdtscp_ignore_rcx(void)
{
	uint32_t lo, hi;

	__asm__ __volatile__("rdtscp" : "=a" (lo), "=d" (hi) : : "%rcx" );

	return (((uint64_t)hi << 32) | lo);
}
/**
 * https://blog.dynox.cn/?p=1658
 */
static inline __always_inline__
uint64_t __rdtsc_ia32(void)
{
	return __builtin_ia32_rdtsc();
}
static inline __always_inline__
uint64_t __rdtscp_ia32(unsigned int *__A)
{
	return __builtin_ia32_rdtscp(__A);
}

/* clock */
struct clock {
	const char *name;
	uint64_t (*read)(void);
};

static inline __always_inline__
uint64_t rdtsc_read(void)
{
	return rdtsc();
}

static inline __always_inline__
uint64_t rdtsc_read_strict(void)
{
	return rdtsc_fence();
}

static inline __always_inline__
uint64_t rdtscp_read(void)
{
	return rdtsc_fence();
}

static inline __always_inline__
uint64_t vdso_monotonic(void)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (uint64_t)t.tv_sec * 1000000000ULL + (uint64_t)t.tv_nsec;
}

static inline __always_inline__
uint64_t vdso_realtime(void)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return (uint64_t)t.tv_sec * 1000000000ULL + (uint64_t)t.tv_nsec;
}

static inline __always_inline__
uint64_t vdso_gettimeofday(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (uint64_t)t.tv_sec * 1000000000ULL + (uint64_t)t.tv_usec * 1000ULL;
}

struct clock clock_rdtsc = {
	.name = "rdtsc",
	.read = rdtsc_read,
};

struct clock clock_rdtsc_fence = {
	.name = "rdtsc-fence",
	.read = rdtsc_read_strict,
};

struct clock clock_rdtscp = {
	.name = "rdtscp",
	.read = rdtscp_read,
};

struct clock clock_monotonic = {
	.name = "vdso-monotonic",
	.read = vdso_monotonic,
};

struct clock clock_realtime = {
	.name = "vdso-realtime",
	.read = vdso_realtime,
};

struct clock clock_gettimeofday = {
	.name = "vdso-gettimeofday",
	.read = vdso_gettimeofday,
};
