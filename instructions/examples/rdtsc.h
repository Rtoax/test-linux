#pragma once

#include <stdint.h>

#include "utils.h"

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

/* clock */
struct clock {
	const char const *name;
	uint64_t (*read)(void);
	uint64_t (*read_strict)(void);
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

struct clock clock_rdtsc = {
	.name = "rdtsc",
	.read = rdtsc_read,
	.read_strict = rdtsc_read_strict,
};

