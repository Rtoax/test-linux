#include <pthread.h>
#include <stdio.h>
#include <ctype.h>

#include "libs/memshow.h"

void *test_task_fn(void *unused)
{
	pthread_attr_t attr = {};

	fhexdump(stdout, "before init > ", &attr, sizeof(pthread_attr_t));

	pthread_attr_init(&attr);

	fhexdump(stdout, "after  init > ", &attr, sizeof(pthread_attr_t));

	pthread_attr_destroy(&attr);

	fhexdump(stdout, "after destroy > ", &attr, sizeof(pthread_attr_t));

	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, NULL);

	return 0;
}
