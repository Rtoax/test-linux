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
#include "proc_helpers.h"
#include "rb.h"


static pthread_t thread;
static pthread_spinlock_t info_lock;
static volatile bool exiting = false;
static int verbose = 0;
static unsigned long rate_threshold = 100 * MB;

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)
#define __unused	__attribute__((unused))

#define VERBOSE_LOG(fmt...) do {		\
		if (likely(!verbose))		\
			break;			\
		fprintf(stderr, fmt);		\
       } while (0)

#ifdef DEBUG
#define VERBOSE_LOG_DEBUG(fmt...) VERBOSE_LOG(fmt)
#else
#define VERBOSE_LOG_DEBUG(fmt...)
#endif

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
	rb_node(struct info) rb_link_node;
};

typedef rb_tree(struct info) infos_t;

/**
 * All process information is stored in this structure, using the red-black
 * tree interface provided by glibc. The tree structure is used because it
 * has its own sorting function, instead of using sorting algorithms such
 * as qsort().
 */
static infos_t all_procs;

static int info_cmp(const struct info *i1, const struct info *i2)
{
	if (i1->pid > i2->pid)
		return -1;
	else if (i1->pid > i2->pid)
		return 1;
	else
		return 0;
}

rb_gen(static __unused, infos_, infos_t, struct info, rb_link_node, info_cmp);

struct info *try_get_info(pid_t pid)
{
	struct info i = { .pid = pid, };
	return infos_search(&all_procs, &i);
}

bool has_info(pid_t pid)
{
	return try_get_info(pid);
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

void free_info(struct info *inf)
{
	free(inf);
}

/* Userspace process page-fault happen */
void Pagefault(pid_t pid, unsigned long nr_pagefault)
{
	struct info *new;

	INFO_LOCK();

	new = try_get_info(pid);
	if (new) {
		VERBOSE_LOG_DEBUG("old process %d, pagefault %lu\n", new->pid, new->nr_pagefault);
		new->nr_pagefault += nr_pagefault;
	} else {
		VERBOSE_LOG_DEBUG("record new process %d, pagefault %lu\n", pid, new->nr_pagefault);
		new = alloc_info(pid, nr_pagefault);
		infos_insert(&all_procs, new);
	}

	INFO_UNLOCK();
}


void WalkInfo(void)
{
	struct info *inf;

	printf("-----------------------\n");

	INFO_LOCK();
	for (inf = infos_first(&all_procs); inf; inf = infos_next(&all_procs, inf)) {
		printf("pid %d, nr_pagefault %lu\n", inf->pid, inf->nr_pagefault);
		if (!proc_exist(inf->pid)) {
			VERBOSE_LOG("pid %d is not exist, %p.\n", inf->pid, inf);
			infos_remove(&all_procs, inf);
			free_info((void *)inf);
			inf = infos_first(&all_procs);
		}
	}
	INFO_UNLOCK();

	fflush(stdout);
}

void *thread_fn(void *arg)
{
	while (!exiting) {
		WalkInfo();
		usleep(1000000);
		//system("clear");
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
	VERBOSE_LOG_DEBUG("pid %d, error_code %ld\n", pf_ev->pid, pf_ev->error_code);
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

	infos_new(&all_procs);

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
	return 0;
}
