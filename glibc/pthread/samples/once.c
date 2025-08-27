#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void once_run(void)
{
	printf("once_run in thread %ld.\n", (unsigned long)pthread_self());
}

void *child_routine(void *arg)
{
	pthread_once(&once, once_run);
	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, child_routine, NULL);
	pthread_create(&tid2, NULL, child_routine, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;

}
