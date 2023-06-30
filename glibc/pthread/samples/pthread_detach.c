#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"


void* test_task_fn(void* unused)
{
	log_child("test_task_fn.\n");

	static int status = 12121;
	int a = 10;

	while (a--) {
		log_child("sleep %d\n", a);
		sleep(1);
	}

	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	sleep(1);

    /* I don't want to know child thread exit, detach is different from join. */
	pthread_detach(thread_id);

	return 0;
}


