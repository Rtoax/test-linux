#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* rename all threads */
bool renaming = true;
/* parent process coredump by default */
bool childcore = false;

void sig_handler(int sig)
{
	psignal(sig, "Catch");
	exit(1);
}

void set_thread_name(const char *name)
{
	if (pthread_setname_np(pthread_self(), name)) {
		perror("pthread_setname_np");
		exit(EXIT_FAILURE);
	}
}

int overflow(void)
{
	char *s = NULL;
	/* Segvfault here */
	char c = s[1024];
	return c;
}

void *child_work(void *arg)
{
	if (renaming)
		set_thread_name("child-thread");

	for (;;) {
		if (childcore)
			overflow();
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	int i;
#define NR_THREAD 10
	pthread_t child[NR_THREAD];

	fprintf(stderr, "usage: %s [catch=<segv>] [childcore] [norename]\n",
		argv[0]);

	for (i = 1; i < argc; i++) {
		if (!strncmp("catch=", argv[i], strlen("catch="))) {
			if (!strcmp(argv[i] + strlen("catch="), "segv")) {
				/**
				 * If catching segv, the core will not be
				 * generated, except restore the signal handler
				 * in sig_handler().
				 */
				signal(SIGSEGV, sig_handler);
			}
		} else if (!strcmp("childcore", argv[i])) {
			childcore = true;
		} else if (!strcmp("norename", argv[i])) {
			renaming = false;
		} else {
			fprintf(stderr, "ERROR: Unknown arg %s\n", argv[i]);
			exit(EXIT_FAILURE);
		}
	}

	if (renaming)
		set_thread_name("parent-thread");

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&child[i], NULL, child_work, NULL);

	if (!childcore)
		overflow();

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(child[i], NULL);
	return 0;
}
