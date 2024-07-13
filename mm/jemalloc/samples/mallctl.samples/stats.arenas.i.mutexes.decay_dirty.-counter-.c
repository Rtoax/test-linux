#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "counter.h"

//stats.arenas.<i>.mutexes.decay_dirty.{counter} (counter specific type) r- [--enable-stats]
//	Statistics on arena.<i>.decay_dirty mutex (arena scope; decay for dirty pages related). {counter} is one of the
//	counters in mutex profiling counters.

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


void jemalloc_stats_arenas_i_mutexes_decay_dirty_counter()
{
	unsigned narenas, i, j, k;

	size_t mib[6];
	size_t len, miblen;
	uint64_t value;

	len = 32;

	jemalloc_arena_narenas(&narenas);

	miblen = 6;

	je_mallctlnametomib(CNT_STRING("stats.arenas.0.mutexes.decay_dirty.", counter_string[0]), mib, &miblen);

	for (i = 0; i < narenas; i++) {

		len = 32; //检测返回的结果是不是 8

		mib[2] = i;

		for (k = 0; k < NR_COUNTER; k++) {
			mib[5] = k;
			je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

			/* Do something... */
			printf("stats.arenas.%d.mutexes.decay_dirty.%-20s = %d,(%d)\n", i, counter_string[k], value, len);
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
	jemalloc_stats_arenas_i_mutexes_decay_dirty_counter();

#if 0

#define LOOP_COUNTER(name) {	\
		size_t mib[6];		  \
		size_t miblen = 6;	  \
		je_mallctlnametomib("stats.arenas.0.mutexes.decay_dirty."#name, mib, &miblen);\
		printf("%s ", #name);	   \
		while(miblen){			  \
			printf("%d.", mib[6-miblen--]);\
		}miblen=6;printf("\n");};
		LOOP_COUNTER(num_ops);
		LOOP_COUNTER(num_spin_acq);
		LOOP_COUNTER(num_wait);
		LOOP_COUNTER(max_wait_time);
		LOOP_COUNTER(total_wait_time);
		LOOP_COUNTER(max_num_thds);
		LOOP_COUNTER(num_owner_switch);
#endif


}

