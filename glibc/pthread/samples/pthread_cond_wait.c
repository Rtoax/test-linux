#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int flag = 0;

static void cleanup_handler(void *arg)
{
	printf("Cleanup handler.\n");
	(void)pthread_mutex_unlock(&mutex);
}

static void *thread_func(void *arg)
{
	pthread_cleanup_push(cleanup_handler, NULL);

	pthread_mutex_lock(&mutex);
	printf("Waiting... flag = %d\n", flag);
	pthread_cond_wait(&cond, &mutex);
	printf("Got flag = %d\n", flag);
	pthread_mutex_unlock(&mutex);

	pthread_cleanup_pop(0);
	return 0;
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thread_func, NULL);

	/* wait child thread startup */
	sleep(1);

	pthread_mutex_lock(&mutex);
	flag = 1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);

	pthread_join(tid, NULL);

	printf("All done\n");
	return 0;
}
