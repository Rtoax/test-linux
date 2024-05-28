#include <pthread.h>

/**
 * 创建分离（detach）的线程，这个线程不需要pthread_join
 */
void *thread_function(void *arg)
{
	/* Do work here... */
	return NULL;
}

int main(void)
{
	pthread_attr_t attr;
	pthread_t thread;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread, &attr, &thread_function, NULL);
	pthread_attr_destroy(&attr);
	/* Do work here... */
	/* No need to join the second thread. */
	return 0;
}
