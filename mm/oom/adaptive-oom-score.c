// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <argp.h>
#include <assert.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <search.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <unistd.h>
#include "adaptive-oom-score.skel.h"
#include "adaptive-oom-score.h"
#include "oom_helpers.h"

static pthread_t thread;
static pthread_spinlock_t info_lock;
static volatile bool exiting = false;
static int verbose = 0;
static unsigned long rate_threshold = 100 * MB;

#define likely(x)    __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

#define VERBOSE_LOG(fmt...) do {		\
		if (likely(!verbose))		\
			break;			\
		fprintf(stderr, fmt);		\
       } while (0)

#define INFO_LOCK()	pthread_spin_lock(&info_lock)
#define INFO_UNLOCK()	pthread_spin_unlock(&info_lock)

const char argp_prog_doc[] =
	"USAGE: [-T <200MB>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "rate-threshold", 'T', "RATE_THRESHOLD", 0, "Set Pagefault Rate Threshold, suffix KB, MB, GB" },
	{ "verbose", 'v', NULL, 1, "Display the detail, for debug maybe" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'T':
		rate_threshold = str2size(arg);
		break;
	case 'v':
		verbose = 1;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

struct info {
	pid_t pid;
	unsigned long nr_pagefault;
};

/**
 * All process information is stored in this structure, using the red-black
 * tree interface provided by glibc. The tree structure is used because it
 * has its own sorting function, instead of using sorting algorithms such
 * as qsort().
 */
static void *all_procs = NULL;

static int info_cmp(const void *pa, const void *pb)
{
	const struct info *i1, *i2;
	i1 = pa;
	i2 = pb;
	if (i1->pid > i2->pid)
		return -1;
	else if (i1->pid > i2->pid)
		return 1;
	else
		return 0;
}

struct info *alloc_info(pid_t pid, unsigned long nr_pagefault)
{
	struct info *new;
	new = malloc(sizeof(struct info));
	assert(new && "Malloc failed");
	new->pid = pid;
	new->nr_pagefault = nr_pagefault;
	return new;
}

void free_info(void *inf)
{
	free(inf);
}

/* Userspace process page-fault happen */
void Pagefault(pid_t pid, unsigned long nr_pagefault)
{
	struct info *new = alloc_info(pid, nr_pagefault);

	INFO_LOCK();
	struct info **old = tsearch(new, &all_procs, info_cmp);
	if (unlikely(!old))
		assert(!"tsearch failed");

	/* already have this node */
	if (*old != new) {
		VERBOSE_LOG("old process %d, pagefault %lu\n", new->pid, new->nr_pagefault);
		free_info(new);
		(*old)->nr_pagefault += nr_pagefault;
	} else {
		VERBOSE_LOG("record new process %d, pagefault %lu\n", pid, new->nr_pagefault);
	}

	INFO_UNLOCK();
}

static void walk_action(const void *nodep, VISIT which, int depth)
{
	const struct info *inf = *(struct info **)nodep;
	if (which == preorder || which == leaf) {
		printf("pid %d, nr_pagefault %lu\n", inf->pid, inf->nr_pagefault);
	}
}

void WalkInfo(void)
{
	INFO_LOCK();
	twalk(all_procs, walk_action);
	INFO_UNLOCK();
}

void *thread_fn(void *arg)
{
	while (!exiting) {
		WalkInfo();
		usleep(100000);
	}
	return NULL;
}

static void sig_handler(int sig)
{
	exiting = true;
}

int libbpf_print_fn(enum libbpf_print_level level, const char *format,
		    va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;
	return vfprintf(stderr, format, args);
}

static int handle_event(void *ctx, void *data, size_t data_sz)
{
	struct pf_event_t *pf_ev = data;
#ifdef DEBUG
	VERBOSE_LOG("pid %d, error_code %ld\n", pf_ev->pid, pf_ev->error_code);
#endif
	Pagefault(pf_ev->pid, 1);
	return 0;
}

int main(int argc, char *argv[])
{
	int err;
	struct adaptive_oom_score_bpf *skel;
	struct ring_buffer *rb = NULL;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	skel = adaptive_oom_score_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF object\n");
		return 1;
	}

	VERBOSE_LOG("Load bpf done.\n");

	rb = ring_buffer__new(bpf_map__fd(skel->maps.ring_buf), handle_event, NULL, NULL);
	if (!rb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}

	err = adaptive_oom_score_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Attach bpf failed\n");
		goto cleanup;
	}

	VERBOSE_LOG("Handling event.\n");
	VERBOSE_LOG("Running...\n");

	pthread_spin_init(&info_lock, PTHREAD_PROCESS_SHARED);
	pthread_create(&thread, NULL, thread_fn, NULL);

	while (!exiting) {
		err = ring_buffer__poll(rb, 100 /* timeout, ms */);
		/* Ctrl-C will cause -EINTR */
		if (err == -EINTR) {
			err = 0;
			break;
		}
		if (err < 0) {
			fprintf(stderr, "Error polling perf buffer: %d\n", err);
			break;
		}
	}

cleanup:
	pthread_join(thread, NULL);
	pthread_spin_destroy(&info_lock);
	ring_buffer__free(rb);
	adaptive_oom_score_bpf__detach(skel);
	adaptive_oom_score_bpf__destroy(skel);
	tdestroy(all_procs, free_info);
	return 0;
}
