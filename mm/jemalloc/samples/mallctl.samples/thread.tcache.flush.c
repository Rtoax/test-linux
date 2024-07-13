#include <stdio.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.tcache.flush (void) --
//	Flush calling thread's thread-specific cache (tcache). This interface releases all cached objects and internal data
//	structures associated with the calling thread's tcache. Ordinarily, this interface need not be called, since
//	automatic periodic incremental garbage collection occurs, and the thread cache is automatically discarded when a
//	thread exits. However, garbage collection is triggered by allocation activity, so it is possible for a thread that
//	stops allocating/deallocating to retain its cache indefinitely, in which case the developer may find manual flushing
//	useful.


void get_jemalloc_thread_tcache_flush()
{
	je_mallctl("thread.tcache.flush", NULL, NULL, NULL, 0);
}

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
	get_jemalloc_thread_tcache_flush();

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






