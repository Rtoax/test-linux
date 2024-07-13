#include <stdio.h>
#include <jemalloc/jemalloc.h>

//
//----------------------------------------------------------------------------------------------------------------------------
//stats.mutexes.background_thread.{counter} (counter specific type) r- [--enable-stats]
//	Statistics on background_thread mutex (global scope; background_thread related). {counter} is one of the counters in
//	mutex profiling counters.

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


void get_jemalloc_stats_mutexes_background_thread_counter()
{
	uint64_t value64 = 1;
	uint32_t value32 = 1;

	size_t size64 = sizeof(value64);
	size_t size32 = sizeof(value32);

	je_mallctl("stats.mutexes.background_thread.num_ops", &value64, &size64, NULL, 0);
	printf("num_ops = %ld\n", value64);

	je_mallctl("stats.mutexes.background_thread.num_spin_acq", &value64, &size64, NULL, 0);
	printf("num_spin_acq = %ld\n", value64);

	je_mallctl("stats.mutexes.background_thread.num_wait", &value64, &size64, NULL, 0);
	printf("num_wait = %ld\n", value64);

	je_mallctl("stats.mutexes.background_thread.max_wait_time", &value64, &size64, NULL, 0);
	printf("max_wait_time = %ld\n", value64);

	je_mallctl("stats.mutexes.background_thread.total_wait_time", &value64, &size64, NULL, 0);
	printf("total_wait_time = %ld\n", value64);

	je_mallctl("stats.mutexes.background_thread.max_num_thds", &value32, &size32, NULL, 0);
	printf("max_num_thds = %d\n", value32);

	je_mallctl("stats.mutexes.background_thread.num_owner_switch", &value64, &size64, NULL, 0);
	printf("num_owner_switch = %ld\n", value64);


}

int main(int argc,char **argv)
{
	get_jemalloc_stats_mutexes_background_thread_counter();
}






