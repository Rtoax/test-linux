#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void *thread(void *arg)
{
	signal(SIGHUP, SIG_IGN);

	for (;;) {
		printf("Thread\n");
		sleep(2);
	}
	return NULL;
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&tid, &attr, thread, NULL);
	pthread_attr_destroy(&attr);

	/**
	 * TODO: howto make parent thread exit and child thread reparent to
	 * init process?
	 */
	sleep(1);
	printf("Parent exiting...\n");
	exit(0);

	return 0;
}
