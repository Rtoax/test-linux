#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void handler(int i)
{
	printf("handler: get abort SIGABRT\n");
	exit(EXIT_FAILURE);
}

void *sleep_thread(void *arg)
{
	for (;;) {
		sleep(1);
		abort();
	}
}

int main(void)
{
	int i;
#define NR_THREAD 10
	pthread_t child[NR_THREAD];

	signal(SIGABRT, handler);

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&child[i], NULL, sleep_thread, NULL);

	sleep(2);

	abort();

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(child[i], NULL);
	return 0;
}
