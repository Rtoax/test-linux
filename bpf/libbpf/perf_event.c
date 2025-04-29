#include <argp.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <linux/bpf.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include "perf_event.h"
#include "perf_event.skel.h"
#include "trace_helpers.h"

#define DEFAULT_FREQ	99

static volatile sig_atomic_t stop = 0;
static int cpu = 0;
static int pid = -1;
static int verbose = 0;

static const char argp_prog_doc[] =
	"USAGE: [-c <cpu>] [-p <pid>] [-v]\n"
	"\n";

static const struct argp_option opts[] = {
	{ "cpu", 'c', "CPU", 0, "CPU to sample" },
	{ "pid", 'p', "PID", 0, "PID to sample" },
	{ "verbose", 'v', NULL, 1, "Display the detail, for debug maybe" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'c':
		cpu = atoi(arg);
		break;
	case 'p':
		pid = atoi(arg);
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

static inline int sys_perf_event_open(struct perf_event_attr *attr, pid_t pid,
				      int cpu, int group_fd,
				      unsigned long flags)
{
	return syscall(__NR_perf_event_open, attr, pid, cpu, group_fd, flags);
}

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	read_trace_pipe_stop();
	stop = 1;
}

static void print_ip_map(int fd)
{
	unsigned long key, next_key;
	unsigned int value;
	int max;

	printf("%-19s %-16s\n", "ADDR", "COUNT");

	key = 0;
	max = 0;
	while (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		bpf_map_lookup_elem(fd, &next_key, &value);
		printf("%-19lx %-16d\n", next_key, value);
		key = next_key;
	}

	if (max == MAX_IPS) {
		printf("WARNING: IP hash was full (max %d entries); ", max);
		printf("may have dropped samples\n");
	}
}

int main(int argc, char *argv[])
{
	int err, event_map_fd, pmu_fd;
	struct perf_event_bpf *skel;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);

#if defined(LIBBPF_OPTS)
	LIBBPF_OPTS(bpf_object_open_opts, opts,
		.kernel_log_level = LIBBPF_DEBUG,
	);

	skel = perf_event_bpf__open_opts(&opts);
	err = perf_event_bpf__load(skel);
	if (err) {
		printf("Failed to load BPF object\n");
		perf_event_bpf__destroy(skel);
		return 1;
	}
#else
	skel = perf_event_bpf__open_and_load();
#endif
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	err = perf_event_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		perf_event_bpf__destroy(skel);
		return 1;
	}

	struct perf_event_attr pe_sample_attr = {
		.type = PERF_TYPE_SOFTWARE,
		.freq = 1,
		.sample_period = DEFAULT_FREQ,
		.config = PERF_COUNT_SW_CPU_CLOCK,
		.inherit = 1,
	};

	pmu_fd = sys_perf_event_open(&pe_sample_attr, pid, cpu,
				     -1 /* group_fd */, 0 /* flags */);
	if (pmu_fd < 0) {
		fprintf(stderr, "ERROR: Initializing perf sampling\n");
		err = -1;
		goto cleanup;
	}

	fprintf(stderr, "CPU %d, PID %d, PMU fd %d\n", cpu, pid, pmu_fd);

	skel->links.do_sample = bpf_program__attach_perf_event(skel->progs.do_sample, pmu_fd);
	if (libbpf_get_error(skel->links.do_sample)) {
		fprintf(stderr, "ERROR: Attach perf event\n");
		err = -1;
		goto cleanup;
	}

	printf("Start sampling...\n");

	read_trace_pipe();

cleanup:
	printf("Exiting...\n");
	if (!err) {
		event_map_fd = bpf_map__fd(skel->maps.vaddr_map);
		print_ip_map(event_map_fd);
	}
	close(pmu_fd);
	perf_event_bpf__destroy(skel);
	return -err;
}
