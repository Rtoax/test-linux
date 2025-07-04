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
#include <sys/time.h>
#include <unistd.h>
#include "adaptive-oom-score.skel.h"
#include "adaptive-oom-score.h"
#include "oom_helpers.h"
#include "proc_helpers.h"


static pthread_t thread;
static pthread_spinlock_t info_lock;
static volatile bool exiting = false;
static int verbose = 0;
/* default 1s */
static unsigned long sampling_interval_us = 1000000UL;
/* default 100 MBps */
static unsigned long rate_threshold_Bps = 100 * MB;
static unsigned long PAGESIZE = 0;

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
	"USAGE: [-T <200MB>] [i <US>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "rate-threshold", 'T', "RATE_THRESHOLD", 0, "Set Pagefault Rate Threshold(Bps), suffix KB, MB, GB" },
	{ "sampling-us", 'i', "SAMPLING_US", 0, "Set Sampling interval, default 1s" },
	{ "verbose", 'v', NULL, 1, "Display the detail, for debug maybe" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'T':
		rate_threshold_Bps = str2size(arg);
		break;
	case 'i':
		sampling_interval_us = strtoull(arg, NULL, 10);
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
	char comm[64];
	unsigned long nr_pagefault;
	struct {
		double rate_Bps;
		unsigned long start_us;
	} sample;
};

unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

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
	else if (i1->pid < i2->pid)
		return 1;
	else
		return 0;
}

struct info *alloc_info(pid_t pid, unsigned long nr_pagefault)
{
	struct info *new;
	new = malloc(sizeof(struct info));
	assert(new && "Malloc failed");

	memset(new, 0, sizeof(*new));

	new->pid = pid;
	proc_pid_comm(pid, new->comm, sizeof(new->comm)),
	new->nr_pagefault = nr_pagefault;
	new->sample.start_us = usecs();

	return new;
}

void free_info(void *inf)
{
	free(inf);
}

void display_info(const struct info *inf)
{
	printf("pid %d, comm %s, nr_pagefault %lu, %.2lfB/s, %.2lfMB/s\n",
		inf->pid, inf->comm, inf->nr_pagefault,
		inf->sample.rate_Bps, inf->sample.rate_Bps / 1024 / 1024);
}

static void update_info(struct info *inf, unsigned long nr_pf)
{
	unsigned long end_us, mem_sz, delta_us;

	end_us = usecs();

	inf->nr_pagefault += nr_pf;

	mem_sz = PAGESIZE * inf->nr_pagefault;

	delta_us = end_us - inf->sample.start_us;
	inf->sample.rate_Bps = mem_sz * 1000000.0f / delta_us;

	/**
	 * Reset sampling
	 */
	if (delta_us > sampling_interval_us) {
		inf->nr_pagefault = 0;
		inf->sample.rate_Bps = 0;
		inf->sample.start_us = usecs();
	}
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
		VERBOSE_LOG_DEBUG("old process %d, pagefault %lu\n", new->pid, new->nr_pagefault);
		free_info(new);
		update_info(*old, nr_pagefault);
	} else {
		VERBOSE_LOG_DEBUG("record new process %d, pagefault %lu\n", pid, new->nr_pagefault);
	}

	INFO_UNLOCK();
}

struct walk_arg {
	const struct info **del_nodes;
	size_t del_cnt;
};

static void walk_action(const void *nodep, VISIT which, void *closure)
{
	struct walk_arg *arg = closure;
	const struct info *inf = *(struct info **)nodep;
	if (which == preorder || which == leaf) {
		/**
		 * If process is not exist anymore, mark it as NEED TO DELETE
		 */
		if (!proc_exist(inf->pid)) {
			VERBOSE_LOG("pid %d, comm %s is not exist, %p.\n", inf->pid, inf->comm, inf);
			arg->del_nodes = realloc(arg->del_nodes,
				(arg->del_cnt + 1) * sizeof(struct info *));
			arg->del_nodes[arg->del_cnt++] = inf;
		} else {
			display_info(inf);
			update_info((void *)inf, 0);
		}
	}
}

void WalkInfo(void)
{
	size_t i;

	struct walk_arg arg = {
		.del_nodes = NULL,
		.del_cnt = 0,
	};

	printf("-----------------------\n");
	INFO_LOCK();
	twalk_r(all_procs, walk_action, &arg);
	INFO_UNLOCK();

	fflush(stdout);

	if (arg.del_cnt > 0)
		VERBOSE_LOG("del %ld\n", arg.del_cnt);

	INFO_LOCK();
	for (i = 0; i < arg.del_cnt; i++) {
		const struct info *del = arg.del_nodes[i];
		VERBOSE_LOG("Try del %d, %p\n", del->pid, del);
		if (unlikely(!tdelete(del, &all_procs, info_cmp))) {
			assert(!"Try delete non-exist node.");
		}
		free((void *)del);
	}
	INFO_UNLOCK();

	if (arg.del_cnt > 0)
		free(arg.del_nodes);
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

	PAGESIZE = getpagesize();

	VERBOSE_LOG("Handling event.\n");
	VERBOSE_LOG("Running...\n");
	VERBOSE_LOG("Sampling Interval %ld us\n", sampling_interval_us);
	VERBOSE_LOG("Rate Threshold %ld Bps\n", rate_threshold_Bps);
	VERBOSE_LOG("PAGESIZE %ld B\n", PAGESIZE);

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
