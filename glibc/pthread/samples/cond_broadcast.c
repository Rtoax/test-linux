#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_THREAD_NUM 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_fun(void *arg)
{
	int index = *(int *)arg;
	printf("[%d]thread start up!\n", index);
	pthread_mutex_lock(&mutex);
	printf("[%d]thread wait...\n", index);
	pthread_cond_wait(&cond, &mutex);
	printf("[%d]thread wake up\n", index);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

int main(void)
{
	int i;
	pthread_t tid[MAX_THREAD_NUM];

#if defined(COND_ATTR)
	pthread_condattr_t condattr;
	clockid_t clockid = -1;

	pthread_condattr_init(&condattr);
	pthread_condattr_getclock(&condattr, &clockid);
	pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC);
	pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);

	pthread_cond_init(&cond, &condattr);
#endif

	for (i = 0; i < MAX_THREAD_NUM; i++) {
		pthread_create(&tid[i], NULL, thread_fun, &i);
	}

	/* wakeup one by one for two thread */
	sleep(1);
	pthread_cond_signal(&cond);
	sleep(1);
	pthread_cond_signal(&cond);
	sleep(1);

	/* wakeup the left all */
	pthread_cond_broadcast(&cond);

	for (i = 0; i < MAX_THREAD_NUM; ++i)
		pthread_join(tid[i], NULL);

#if defined(COND_ATTR)
	pthread_cond_destroy(&cond);
#endif

	return 0;
}

