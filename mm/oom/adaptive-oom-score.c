// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * This tool can dynamically decide or adjust which process OOM-Killer kills
 * based on the actual memory application of the process, instead of selecting
 * the process with the highest oom_score and the most memory usage.
 *
 * This tool currently only considers the rate at which a process allocates
 * memory. For example, when a service, such as redis or memcached, steadily
 * occupies most of the system's memory, and another process suddenly applies
 * for and uses RAM memory, redis or memcached will be killed, which is not
 * what we expect. Therefore, we dynamically determine which process should
 * be killed based on the sudden increase in memory allocation.
 */
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

#define ANSI_RED	"\033[31m"
#define ANSI_GRE	"\033[32m"
#define ANSI_YEL	"\033[33m"
#define ANSI_BLU	"\033[34m"
#define ANSI_PUR	"\033[35m"
#define ANSI_RST	"\033[m"

static pthread_t thread;
static pthread_spinlock_t info_lock;
static volatile bool exiting = false;
static int verbose = 0;
/* default 1s */
static unsigned long sampling_interval_us = 1000000UL;
/* default 50 MBps */
static unsigned long rate_threshold_Bps = 50 * MB;
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

#define WARNING(fmt...) do {	\
		fprintf(stderr, ANSI_PUR);	\
		fprintf(stderr, fmt);	\
		fprintf(stderr, ANSI_RST);	\
	} while (0)

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
	char comm_bpf[TASK_COMM_LEN];

	size_t nr_sampling;

#define NR_SAMPLING_0BPS	10
	/**
	 * The number of consecutive sampling rates of 0, can be used to
	 * remove invalid data from statistical data.
	 */
	size_t nr_sampling_0Bps;

#define NR_SAMPLING_EXCEEDING_LIMITS	3
	/**
	 * The number of samples that exceeded the rate threshold.
	 */
	size_t nr_sampling_exceeding_limits;

	struct __date_to_record__ {
		double rate_Bps;
		unsigned long nr_pf;	/* number of pagefault */
		unsigned long start_us;
	}
	/* number of pagefault in one sampling cycle */
	sample,
	/* total pagefault */
	total;
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

struct info *alloc_info(pid_t pid, unsigned long nr_pf, char *comm)
{
	struct info *new;
	new = malloc(sizeof(struct info));
	assert(new && "Malloc failed");

	memset(new, 0, sizeof(*new));

	new->pid = pid;
	proc_pid_comm(pid, new->comm, sizeof(new->comm)),
	strcpy(new->comm_bpf, comm);
	new->total.nr_pf = new->sample.nr_pf = nr_pf;
	new->total.start_us = new->sample.start_us = usecs();

	return new;
}

void free_info(void *inf)
{
	free(inf);
}

void display_info(const struct info *inf)
{
#define _FMT "pf %lu, %.2lfB/s, %.2lfMB/s"
#define _DATA(d) d.nr_pf, d.rate_Bps, d.rate_Bps / 1024 / 1024
	printf("pid %d, comm %s(%s) (total: %s"_FMT""ANSI_RST")(sample: %s"_FMT""ANSI_RST")\n",
		inf->pid, inf->comm, inf->comm_bpf,
		inf->total.rate_Bps > 10 * MB ? ANSI_RED : ANSI_RST,
		_DATA(inf->total),
		inf->sample.rate_Bps > 10 * MB ? ANSI_RED : ANSI_RST,
		_DATA(inf->sample));
#undef _FMT
#undef _DATA
}

static void update_info(struct info *inf, unsigned long nr_pf)
{
	unsigned long end_us, mem_sz, delta_us;

	end_us = usecs();

	inf->total.nr_pf += nr_pf;
	inf->sample.nr_pf += nr_pf;

	/**
	 * Update sampling
	 */
	mem_sz = PAGESIZE * inf->sample.nr_pf;
	delta_us = end_us - inf->sample.start_us;
	inf->sample.rate_Bps = mem_sz * 1000000.0f / delta_us;


	/* Pagefault() will update too */
	if (nr_pf == 0) {
		inf->nr_sampling++;
		if (inf->sample.rate_Bps != 0)
			inf->nr_sampling_0Bps = 0;
		else {
			inf->nr_sampling_0Bps++;
		}

		if (inf->sample.rate_Bps >= rate_threshold_Bps)
			inf->nr_sampling_exceeding_limits++;
	}

	if (delta_us > sampling_interval_us) {
		inf->sample.nr_pf = 0;
		inf->sample.rate_Bps = 0;
		inf->sample.start_us = usecs();
	}

	/**
	 * Update total
	 */
	mem_sz = PAGESIZE * inf->total.nr_pf;
	delta_us = end_us - inf->total.start_us;
	inf->total.rate_Bps = mem_sz * 1000000.0f / delta_us;
}

/* Userspace process page-fault happen */
void Pagefault(unsigned long nr_pf, struct pf_event_t *pf_ev)
{
	pid_t pid = pf_ev->pid;
	struct info *new = alloc_info(pid, nr_pf, pf_ev->comm);

	INFO_LOCK();
	struct info **old = tsearch(new, &all_procs, info_cmp);
	if (unlikely(!old))
		assert(!"tsearch failed");

	/* already have this node */
	if (*old != new) {
		VERBOSE_LOG_DEBUG("old process %d, pagefault %lu\n", pid, nr_pf);
		free_info(new);
		update_info(*old, nr_pf);
	} else {
		VERBOSE_LOG_DEBUG("record new process %d, pagefault %lu\n", pid, nr_pf);
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
		bool should_del;

		/**
		 * If process is not exist anymore, mark it as NEED TO DELETE
		 */
		should_del = !proc_exist(inf->pid);

		/**
		 * If the sampling rate is 0 for several consecutive times,
		 * the process will be deleted from the statistics.
		 */
		if (inf->nr_sampling_0Bps >= NR_SAMPLING_0BPS)
			should_del |= 1;

		if (should_del) {
			VERBOSE_LOG("pid %d, comm %s(%s) is not exist, %p.\n",
				inf->pid, inf->comm, inf->comm_bpf, inf);
			arg->del_nodes = realloc(arg->del_nodes,
				(arg->del_cnt + 1) * sizeof(struct info *));
			arg->del_nodes[arg->del_cnt++] = inf;
		} else {
			display_info(inf);
			update_info((void *)inf, 0);
			/**
			 * This process has been allocating memory at a rate
			 * that is too high for a long time, so the score at
			 * which this process is killed by the oom-killer is
			 * increased.
			 */
			if (inf->nr_sampling_exceeding_limits > NR_SAMPLING_EXCEEDING_LIMITS) {
				WARNING("Set %s(%s)[%d] oom_score_adj to max.\n",
					inf->comm, inf->comm_bpf, inf->pid);
				/**
				 * TODO: Here, we can introduce a more complex
				 * algorithm instead of simply adjusting
				 * oom_score_adj to the maximum.
				 */
				set_oom_score_adj(inf->pid, OOM_SCORE_ADJ_MAX);
			}
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
		usleep(sampling_interval_us);
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
	Pagefault(1, pf_ev);
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

	/* Trust me, i'll never use too much memory */
	disable_oom_by_score_adj(getpid());

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
