#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include "raw_tracepoint.h"

#if defined(SEC_DEF_RAW_TRACEPOINT)
#include "raw_tracepoint.skel.h"
#define struct_bpf	raw_tracepoint_bpf
#define _bpf__open_opts	raw_tracepoint_bpf__open_opts
#define _bpf__load	raw_tracepoint_bpf__load
#define _bpf__destroy	raw_tracepoint_bpf__destroy
#define _bpf__open_and_load	raw_tracepoint_bpf__open_and_load
#define _bpf__attach	raw_tracepoint_bpf__attach
#elif defined(SEC_DEF_TP_BTF)
#include "tp_btf.skel.h"
#define struct_bpf	tp_btf_bpf
#define _bpf__open_opts	tp_btf_bpf__open_opts
#define _bpf__load	tp_btf_bpf__load
#define _bpf__destroy	tp_btf_bpf__destroy
#define _bpf__open_and_load	tp_btf_bpf__open_and_load
#define _bpf__attach	tp_btf_bpf__attach
#endif


static volatile sig_atomic_t stop = 0;

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;
	return vfprintf(stderr, format, args);
}

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	stop = 1;
}

void handle_event(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct data_t *m = data;
	printf("%-6d %-6d %-16s %-16s %-16s\n", m->pid, m->uid, m->comm,
		m->parent_comm, m->child_comm);
}

void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
	printf("lost event\n");
}

int main(void)
{
	int err, event_map_fd;
	struct struct_bpf *skel;
	struct perf_buffer *pb = NULL;

	signal(SIGINT, sig_handler);

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

#if defined(LIBBPF_OPTS)
	int i;
	char log_buf[64 * 1024];

	LIBBPF_OPTS(bpf_object_open_opts, opts,
		.kernel_log_buf = log_buf,
		.kernel_log_size = sizeof(log_buf),
		.kernel_log_level = LIBBPF_DEBUG,
	);

	skel = _bpf__open_opts(&opts);
	err = _bpf__load(skel);
	if (err) {
		printf("Failed to load BPF object\n");
		_bpf__destroy(skel);
		return 1;
	}

	/* Print the verifier log */
	for (i = 0; i < sizeof(log_buf); i++) {
		if (log_buf[i] == 0 && log_buf[i+1] == 0) {
			break;
		}
		printf("%c", log_buf[i]);
	}
#else
	skel = _bpf__open_and_load();
#endif
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		_bpf__destroy(skel);
		return 1;
	}

	event_map_fd = bpf_map__fd(skel->maps.event);

#if LIBBPF_MAJOR_VERSION >= 1
	pb = perf_buffer__new(event_map_fd, 8, handle_event, lost_event, NULL,
				 NULL);
#else
	struct perf_buffer_opts pb_opts;
	pb_opts.sample_cb = handle_event;
	pb_opts.lost_cb = lost_event;
	pb = perf_buffer__new(event_map_fd, 8, &pb_opts);
#endif
	if (!pb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		_bpf__destroy(skel);
		return 1;
	}

	while (!stop) {
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
	_bpf__destroy(skel);
	return -err;
}
