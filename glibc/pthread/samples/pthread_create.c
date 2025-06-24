#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


static int nr_threads = 1;

static sig_atomic_t loop = true;
static int us = 100000;

void sig_handler(int signum)
{
	printf("Catch signal.\n");
	loop = false;
}

void print_ansi(void)
{
	fprintf(stderr, "\033[31mx\033[m");
	usleep(us);
}

void *print_xs(void *unused)
{
	pthread_setname_np(pthread_self(), "pthread-child");

	while (loop)
		print_ansi();
	return NULL;
}

void parse_args(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++) {
		if (!strncmp(argv[i], "nr=", 3)) {
			nr_threads = atoi(argv[i] + 3);
			if (nr_threads <= 1) {
				fprintf(stderr, "ERROR: bad number %s\n", argv[i]);
				exit(1);
			}
		} else if (!strncmp(argv[i], "t=", 2)) {
			us = atoi(argv[i] + 2);
			if (us <= 1000) {
				fprintf(stderr, "ERROR: bad us %s\n", argv[i]);
				exit(1);
			}
		} else {
			fprintf(stderr, "ERROR: unknown %s\n", argv[i]);
			exit(1);
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t *threads;

	fprintf(stderr, "%s [nr=<number of threads>] [t=<us>]\n", argv[0]);

	signal(SIGINT, sig_handler);

	parse_args(argc - 1, argv + 1);

	threads = malloc(sizeof(pthread_t) * nr_threads);
	assert(threads && "malloc failed.");

	for (i = 0; i < nr_threads; i++)
		pthread_create(&threads[i], NULL, &print_xs, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");

	while (loop) {
		fputc('o', stderr);
		usleep(us);
	}

	for (i = 0; i < nr_threads; i++)
		pthread_join(threads[i], NULL);

	free(threads);

	return 0;
}
