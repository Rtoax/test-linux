#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

enum op {
	OP_PRINT,
};

struct test_routine {
	enum op op;
	void *(*child)(void *arg);
	void (*parent)(void);
};

static int nr_threads = 1;
static int verbose = 0;
static sig_atomic_t loop = true;
/* print interval */
static int print_interval_us = 100000;
/* control threads to exit normally */
static int timeout_s = 9999999;

void *thread_print_xs(void *unused);
void parent_print_xs(void);

struct test_routine default_print = {
	.op = OP_PRINT,
	.child = thread_print_xs,
	.parent = parent_print_xs,
};

void sig_handler(int signum)
{
	printf("Catch signal.\n");
	loop = false;
}

unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1E6 + tv.tv_usec;
}

/**
 * color: 0-red
 */
void print_ansi(char *msg, size_t us, int color)
{
	fprintf(stderr, "\033[%dm%s\033[m", 31 + color, msg);
	usleep(us);
}

void *thread_print_xs(void *unused)
{
	int elapsed_s = 0;
	unsigned long start = usecs();
	pthread_setname_np(pthread_self(), "pthread-child");

	while (elapsed_s < timeout_s && loop) {
		elapsed_s = (usecs() - start) / 1E6;
		print_ansi("x", print_interval_us, 0);
	}
	return NULL;
}

void parent_print_xs(void)
{
	int elapsed_s = 0;
	unsigned long start = usecs();
	while (elapsed_s < timeout_s && loop) {
		elapsed_s = (usecs() - start) / 1E6;
		print_ansi("o", print_interval_us, 1);
	}
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
			print_interval_us = atoi(argv[i] + 2);
			if (print_interval_us <= 1000) {
				fprintf(stderr,
					"ERROR: bad us %s, must bigger than 1000\n",
					argv[i]);
				exit(1);
			}
		} else if (!strncmp(argv[i], "tout=", 5)) {
			timeout_s = atoi(argv[i] + 5);
		} else if (!strcmp(argv[i], "verbose")) {
			verbose = 1;
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
	struct test_routine *routine = &default_print;

	fprintf(stderr,
		"%s [nr=<nthreads>] [t=<interval us)>] [tout=<timeout us>] [verbose]\n",
		argv[0]);

	signal(SIGINT, sig_handler);

	parse_args(argc - 1, argv + 1);

	if (verbose) {
		printf("parent_print_xs %p\n", parent_print_xs);
		printf("thread_print_xs %p\n", thread_print_xs);
	}

	threads = malloc(sizeof(pthread_t) * nr_threads);
	assert(threads && "malloc failed.");

	for (i = 0; i < nr_threads; i++)
		pthread_create(&threads[i], NULL, routine->child, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");
	if (routine->parent)
		routine->parent();

	for (i = 0; i < nr_threads; i++)
		pthread_join(threads[i], NULL);

	free(threads);

	return 0;
}
