#include <stdio.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.idle (void) --
//	Hints to jemalloc that the calling thread will be idle for some nontrivial period of time (say, on the order of
//	seconds), and that doing some cleanup operations may be beneficial. There are no guarantees as to what specific
//	operations will be performed; currently this flushes the caller's tcache and may (according to some heuristic) purge
//	its associated arena.



void get_jemalloc_thread_idle()
{
	je_mallctl("thread.idle", NULL, NULL, NULL, 0);
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
	get_jemalloc_thread_idle();

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







