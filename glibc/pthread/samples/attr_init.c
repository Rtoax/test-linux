#include <pthread.h>
#include <stdio.h>
#include <ctype.h>

#include <libs/memshow.h>

void *test_task_fn(void *unused)
{
	pthread_attr_t attr;

	memshow("before init > ", &attr, sizeof(pthread_attr_t));

	pthread_attr_init(&attr);

	memshow("after  init > ", &attr, sizeof(pthread_attr_t));

	pthread_attr_destroy(&attr);

	memshow("after destroy > ", &attr, sizeof(pthread_attr_t));

	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, NULL);

	return 0;
}
