#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void sig_handler(int sig)
{
	psignal(sig, "Catch");
	exit(1);
}

int overflow(void)
{
	char *s = NULL;
	/* Segvfault here */
	char c = s[1024];
	return c;
}

void *sleep_routine(void *arg)
{
	for (;;) {
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	int i;
#define NR_THREAD 10
	pthread_t child[NR_THREAD];

	fprintf(stderr, "usage: %s [catch=<segv>]\n", argv[0]);

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
		}
	}

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&child[i], NULL, sleep_routine, NULL);

	sleep(2);

	overflow();

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(child[i], NULL);
	return 0;
}
