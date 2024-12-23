#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include "tracepoint.h"
#include "tracepoint.skel.h"
#include "trace_helpers.h"


static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;
	return vfprintf(stderr, format, args);
}

void handle_event(void *ctx, int cpu, void *event, unsigned int event_sz)
{
	struct event_t *m = event;

	printf("%-6d %-6d %-16s %s ret = %d\n", m->pid, m->uid, m->comm,
		m->filename, m->ret);
}

void lost_event(void *ctx, int cpu, long long unsigned int event_sz)
{
	printf("lost event\n");
}

int main(void)
{
	int err, events_map_fd;
	struct tracepoint_bpf *skel;
	struct perf_buffer *pb = NULL;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

#if defined(LIBBPF_OPTS)
	char log_buf[64 * 1024];

	LIBBPF_OPTS(bpf_object_open_opts, opts,
		.kernel_log_buf = log_buf,
		.kernel_log_size = sizeof(log_buf),
		.kernel_log_level = LIBBPF_DEBUG,
	);

	skel = tracepoint_bpf__open_opts(&opts);
	err = tracepoint_bpf__load(skel);
	if (err) {
		printf("Failed to load BPF object\n");
		tracepoint_bpf__destroy(skel);
		return 1;
	}

	print_bpf_log_buf(log_buf, sizeof(log_buf));
#else
	skel = tracepoint_bpf__open_and_load();
#endif
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	err = tracepoint_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		tracepoint_bpf__destroy(skel);
		return 1;
	}

	events_map_fd = bpf_map__fd(skel->maps.events);

#if LIBBPF_MAJOR_VERSION >= 1
	pb = perf_buffer__new(events_map_fd, 8, handle_event, lost_event, NULL,
			      NULL);
#else
	struct perf_buffer_opts pb_opts;
	pb_opts.sample_cb = handle_event;
	pb_opts.lost_cb = lost_event;
	pb = perf_buffer__new(events_map_fd, 8, &pb_opts);
#endif
	if (!pb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		tracepoint_bpf__destroy(skel);
		return 1;
	}

	while (true) {
		err = perf_buffer__poll(pb, 100 /* timeout, ms */);
		/* Ctrl-C gives -EINTR */
		if (err == -EINTR) {
			err = 0;
			break;
		}
		if (err < 0) {
			printf("Error polling perf buffer: %d\n", err);
			break;
		}
	}

	perf_buffer__free(pb);
	tracepoint_bpf__destroy(skel);
	return -err;
}
