#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

#include "dpdk.h"

/**
 * Macro to align a value to the multiple of given value. The resultant
 * value will be of the same type as the first parameter and will be no lower
 * than the first parameter.
 */
#define RTE_ALIGN_MUL_CEIL(v, mul) \
	((((v) + (typeof(v))(mul) - 1) / ((typeof(v))(mul))) * (typeof(v))(mul))

/**
 * Macro to align a value to the multiple of given value. The resultant
 * value will be of the same type as the first parameter and will be no higher
 * than the first parameter.
 */
#define RTE_ALIGN_MUL_FLOOR(v, mul) \
	(((v) / ((typeof(v))(mul))) * (typeof(v))(mul))

/**
 * Macro to align value to the nearest multiple of the given value.
 * The resultant value might be greater than or less than the first parameter
 * whichever difference is the lowest.
 */
#define RTE_ALIGN_MUL_NEAR(v, mul)			  \
	({						  \
		typeof(v) ceil = RTE_ALIGN_MUL_CEIL(v, mul);	\
		typeof(v) floor = RTE_ALIGN_MUL_FLOOR(v, mul);  \
		(ceil - (v)) > ((v) - floor) ? floor : ceil;	\
	})

static inline uint64_t __rdtsc(void)
{
	unsigned int a, d;
	asm volatile ("rdtsc" : "=a" (a), "=d"(d));
	return ((unsigned long) a) | (((unsigned long) d) << 32);
}

uint64_t get_tsc_freq(void)
{
#ifdef CLOCK_MONOTONIC_RAW
#define NS_PER_SEC 1E9
#define CYC_PER_10MHZ 1E7

	struct timespec sleeptime = {.tv_nsec = NS_PER_SEC / 10 }; /* 1/10 second */

	struct timespec t_start, t_end;
	uint64_t tsc_hz;

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &t_start) == 0) {
		uint64_t ns, end, start = __rdtsc();
		nanosleep(&sleeptime,NULL);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
		end = __rdtsc();
		ns = ((t_end.tv_sec - t_start.tv_sec) * NS_PER_SEC);
		ns += (t_end.tv_nsec - t_start.tv_nsec);

		double secs = (double)ns/NS_PER_SEC;
		tsc_hz = (uint64_t)((end - start)/secs);
		/* Round up to 10Mhz. 1E7 ~ 10Mhz */
		return RTE_ALIGN_MUL_NEAR(tsc_hz, CYC_PER_10MHZ);
	}
#endif
	return 0;
}

/**
 * $ gcc dpdk.c -DTEST
 * $ sudo ./a.out
 * Freq: 1600000000
 */
#ifdef TEST
#include <stdio.h>

int main(int argc, char *argv[])
{
	uint64_t freq = get_tsc_freq();

	printf("Freq: %ld\n", freq);

	return 0;
}
#endif
