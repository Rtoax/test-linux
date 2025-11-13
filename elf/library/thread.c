#include <stdio.h>
#include <pthread.h>

static void *hello(void *arg)
{
	printf("Hello world. %p\n", hello);
	return NULL;
}

void thread_hello(void)
{
	pthread_t thread;
	pthread_create(&thread, NULL, hello, NULL);
	pthread_join(thread, NULL);
}
