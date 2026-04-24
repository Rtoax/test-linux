// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2023-2026 Rong Tao */
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

struct test_routine;

struct task_arg {
	int id;
	/* child thread create thread depth */
	int recursive_depth;
	struct test_routine *routine;
};

struct task {
	pthread_t thread;
	struct task_arg arg;
};

static int nr_threads = 1;
static int verbose = 0;
static sig_atomic_t loop = true;
/* print interval */
static int print_interval_us = 100000;
/* control threads to exit normally */
static int timeout_s = 9999999;

void *thread_print_xs(void *);
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

void *thread_print_xs(void *arg)
{
	int elapsed_s = 0;
	unsigned long start = usecs();
	struct task_arg *targ = arg;

	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf), "child/%d/%d", targ->id,
		 targ->recursive_depth);
	pthread_setname_np(pthread_self(), buf);

	if (verbose)
		fprintf(stderr, "create thread %s, id %ld, arg %d/%d\n", buf,
			pthread_self(), targ->id, targ->recursive_depth);

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
	struct task *tasks;
	struct test_routine *routine = &default_print;

	fprintf(stderr,
		"%s [nr=<nthreads>] [t=<interval us)>] [tout=<timeout us>] [verbose]\n",
		argv[0]);

	signal(SIGINT, sig_handler);

	parse_args(argc - 1, argv + 1);

	if (verbose) {
		fprintf(stderr, "parent_print_xs %p\n", parent_print_xs);
		fprintf(stderr, "thread_print_xs %p\n", thread_print_xs);
	}

	tasks = malloc(sizeof(struct task) * nr_threads);
	assert(tasks && "malloc failed.");

	for (i = 0; i < nr_threads; i++) {
		tasks[i].arg.id = i + 1;
		tasks[i].arg.recursive_depth = 0;
		tasks[i].arg.routine = routine;
		pthread_create(&tasks[i].thread, NULL, routine->child,
			       &tasks[i].arg);
	}

	pthread_setname_np(pthread_self(), "pthread-parent");
	if (routine->parent)
		routine->parent();

	for (i = 0; i < nr_threads; i++)
		pthread_join(tasks[i].thread, NULL);

	free(tasks);
	return 0;
}
