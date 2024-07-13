#include <stdio.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.allocated (uint64_t) r- [--enable-stats]
//	Get the total number of bytes ever allocated by the calling thread. This counter has the potential to wrap around; it
//	is up to the application to appropriately interpret the counter in such cases.

void get_jemalloc_thread_allocated(uint64_t *value)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("thread.allocated", value, &size, NULL, 0);
}

void *thread_routine(void *arg)
{

	uint64_t value = 1;

	get_jemalloc_thread_allocated(&value);
	printf("value = %ld\n", value);

	char *str = je_malloc(1025);

	sleep(pthread_self()/55%3);

	get_jemalloc_thread_allocated(&value);
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



