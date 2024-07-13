#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "counter.h"

//stats.arenas.<i>.bins.<j>.mutex.{counter} (counter specific type) r- [--enable-stats]
//	Statistics on arena.<i>.bins.<j> mutex (arena bin scope; bin operation related). {counter} is one of the counters in
//	mutex profiling counters.
//
//	num_ops (uint64_t): Total number of lock acquisition operations on this mutex.
//
//	num_spin_acq (uint64_t): Number of times the mutex was spin-acquired. When the mutex is currently locked and cannot
//		be acquired immediately, a short period of spin-retry within jemalloc will be performed. Acquired through spin
//		generally means the contention was lightweight and not causing context switches.
//
//
//	num_wait (uint64_t): Number of times the mutex was wait-acquired, which means the mutex contention was not solved by
//		spin-retry, and blocking operation was likely involved in order to acquire the mutex. This event generally implies
//		higher cost / longer delay, and should be investigated if it happens often.
//
//
//	max_wait_time (uint64_t): Maximum length of time in nanoseconds spent on a single wait-acquired lock operation. Note
//		that to avoid profiling overhead on the common path, this does not consider spin-acquired cases.
//
//
//	total_wait_time (uint64_t): Cumulative time in nanoseconds spent on wait-acquired lock operations. Similarly, spin-
//		acquired cases are not considered.
//
//
//	max_num_thds (uint32_t): Maximum number of threads waiting on this mutex simultaneously. Similarly, spin-acquired
//		cases are not considered.
//
//
//	num_owner_switch (uint64_t): Number of times the current mutex owner is different from the previous one. This event
//		does not generally imply an issue; rather it is an indicator of how often the protected data are accessed by
//		different threads.
//
//	num_ops		   0
//	num_wait		  1
//	num_spin_acq	  2
//	num_owner_switch  3
//	total_wait_time   4
//	max_wait_time	 5
//	max_num_thds	  6

void jemalloc_arena_narenas(unsigned *pnarenas)
{
	size_t len;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_arenas_nbins(unsigned *pnbins)
{
	size_t len;

	len = sizeof(*pnbins);
	je_mallctl("arenas.nbins", pnbins, &len, NULL, 0);
	printf("arenas.nbins = %d.\n", *pnbins);

}


void jemalloc_stats_arenas_i_bins_j_mutex_counter()
{
	unsigned narenas, i, j, k;
	unsigned nbins;

	size_t mib[7];
	size_t len, miblen;
	uint64_t value;

	len = 32;

	jemalloc_arena_narenas(&narenas);
	jemalloc_arenas_nbins(&nbins);

	miblen = 7;

#if 0

#define LOOP_COUNTER(name) \
	je_mallctlnametomib("stats.arenas.0.bins.0.mutex."#name, mib, &miblen);\
	printf("%s ", #name);\
	while(miblen){\
		printf("%d.", mib[7-miblen--]);\
	}miblen=7;printf("\n");
	LOOP_COUNTER(num_ops);
	LOOP_COUNTER(num_spin_acq);
	LOOP_COUNTER(num_wait);
	LOOP_COUNTER(max_wait_time);
	LOOP_COUNTER(total_wait_time);
	LOOP_COUNTER(max_num_thds);
	LOOP_COUNTER(num_owner_switch);
#endif

	je_mallctlnametomib(CNT_STRING("stats.arenas.0.bins.0.mutex.", counter_string[0]), mib, &miblen);

	for (i = 0; i < narenas; i++) {
		for (j = 0; j < nbins; j++) {

			len = 32; //检测返回的结果是不是 8

			mib[2] = i;
			mib[4] = j;

			for (k = 0; k < NR_COUNTER; k++) {
				mib[6] = k;
				je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

				/* Do something... */
				printf("stats.arenas.%d.bins.%d.mutex.%-20s = %d,(%d)\n", i, j, counter_string[k], value, len);
			}
		}
	}
}


void jemalloc_test()
{
	char *str1 = je_malloc(1234);
	char *str2 = je_malloc(12121234);
	char *str3 = je_malloc(1234);
}


int main()
{
	unsigned narenas;
	jemalloc_test();
	jemalloc_stats_arenas_i_bins_j_mutex_counter();

}
