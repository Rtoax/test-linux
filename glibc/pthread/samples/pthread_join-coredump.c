#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

pthread_t thread;

void *thread_fn(void *arg)
{
	printf("Thread return.\n");
	return NULL;
}

int main(void)
{
	int r;
	bool join = false;

	r = pthread_create(&thread, NULL, thread_fn, NULL);
	if (r == 0) {
		printf("Create thread success.\n");
		join = true;
	}
	pthread_setname_np(thread, "Thread");

	/**
	 * misoperation
	 */
#if defined(HAVE_MISOPERATION)
	thread = 0;
#else
#pragma message "-DHAVE_MISOPERATION to misoperation pthread_t"
#endif

	if (join) {
		printf("Wait thread exit.\n");
		pthread_join(thread, NULL);
	}

	printf("Main return.\n");

	return 0;
}
