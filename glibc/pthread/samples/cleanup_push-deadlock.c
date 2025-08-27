/**
 * https://www.cnblogs.com/mydomain/archive/2011/08/15/2139830.html
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

#if defined(DEADLOCK)
void cleanup(void *arg)
{
}
#else
void cleanup(void *arg)
{
	printf("thread0 cleanup unlock mutex...\n");
	pthread_mutex_unlock(&mutex);
}
#endif

void *thread0(void *arg)
{
	/* thread cleanup handler */
	pthread_cleanup_push(cleanup, NULL);

	printf("thread0 locking mutex...\n");
	pthread_mutex_lock(&mutex);
	printf("thread0 locked mutex.\n");

	printf("thread0 waiting cond...\n");
	pthread_cond_wait(&cond, &mutex);
	printf("thread0 unlocking mutex...\n");
	pthread_mutex_unlock(&mutex);

	pthread_cleanup_pop(0);

	printf("thread0 exiting...\n");
	pthread_exit(NULL);

	return NULL;
}

void *thread1(void *arg)
{
	/* Make sure thread0 lock mutex first. */
	sleep(1);
	printf("thread1 locking mutex...\n");
	pthread_mutex_lock(&mutex);
	printf("thread1 locked mutex.\n");

	printf("thread1 broadcast cond...\n");
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);

	printf("thread1 exiting...\n");

	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid[2];

	pthread_create(&tid[0], NULL, thread0, NULL);
	pthread_create(&tid[1], NULL, thread1, NULL);

	sleep(2);

	printf("main cancel thread0\n");
	pthread_cancel(tid[0]);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
