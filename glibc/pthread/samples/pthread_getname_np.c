#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#define NAMELEN 16

#define err_exit(en, msg) do { \
		errno = en; perror(msg); exit(EXIT_FAILURE); \
	} while (0)

static void *threadfunc(void *parm)
{
	sleep(2);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	int rc;
	char name[NAMELEN];

	rc = pthread_create(&thread, NULL, threadfunc, NULL);
	if (rc != 0)
		err_exit(rc, "pthread_create");

	rc = pthread_getname_np(thread, name, NAMELEN);
	if (rc != 0)
		err_exit(rc, "pthread_getname_np");

	printf("Created a thread. Default name is: %s\n", name);
	rc = pthread_setname_np(thread, "THREADFOO");
	if (rc != 0)
		err_exit(rc, "pthread_setname_np");

	sleep(1);

	rc = pthread_getname_np(thread, name, NAMELEN);
	if (rc != 0)
		err_exit(rc, "pthread_getname_np");

	printf("The thread name after setting it is %s.\n", name);

	rc = pthread_join(thread, NULL);
	if (rc != 0)
		err_exit(rc, "pthread_join");

	printf("Done\n");
	exit(EXIT_SUCCESS);
}
