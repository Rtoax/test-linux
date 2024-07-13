#include <stdio.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.peak.read (uint64_t) r- [--enable-stats]
//	Get an approximation of the maximum value of the difference between the number of bytes allocated and the number of
//	bytes deallocated by the calling thread since the last call to thread.peak.reset, or since the thread's creation if
//	it has not called thread.peak.reset. No guarantees are made about the quality of the approximation, but jemalloc
//	currently endeavors to maintain accuracy to within one hundred kilobytes.
//申请和free的差值


void get_jemalloc_thread_peak_read(uint64_t *value)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("thread.peak.read", value, &size, NULL, 0);
}

void *thread_routine(void *arg)
{

	uint64_t value = 1;

	get_jemalloc_thread_peak_read(&value);
	printf("value = %ld\n", value);

	char *str = je_malloc(1025);

	sleep(pthread_self()/55%3);

	get_jemalloc_thread_peak_read(&value);
	printf("value = %ld\n", value);

	sleep(pthread_self()/55%3);

	je_free(str);

	get_jemalloc_thread_peak_read(&value);
	printf("value = %ld\n", value);

	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	int nr_thread = 4, ithread;
	pthread_t threadids[nr_thread];

	for(ithread=0;ithread<nr_thread;ithread++){
		pthread_create(&threadids[ithread], NULL, thread_routine, NULL);
	}

	for(ithread=0;ithread<nr_thread;ithread++){
		pthread_join(threadids[ithread], NULL);
	}
}




