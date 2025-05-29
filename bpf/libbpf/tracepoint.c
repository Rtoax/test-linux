#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include "tracepoint.h"
#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#if defined(TRACEPOINT) && (!defined(MAP_HASH) && !defined(MAP_PERCPU_HASH))
#include "tracepoint.skel.h"
#define struct_bpf	tracepoint_bpf
#define _bpf__open_opts	tracepoint_bpf__open_opts
#define _bpf__load	tracepoint_bpf__load
#define _bpf__destroy	tracepoint_bpf__destroy
#define _bpf__open_and_load	tracepoint_bpf__open_and_load
#define _bpf__attach	tracepoint_bpf__attach
#elif defined(TRACEPOINT) && defined(MAP_HASH)
#include "map_hash.skel.h"
#define struct_bpf	map_hash_bpf
#define _bpf__open_opts	map_hash_bpf__open_opts
#define _bpf__load	map_hash_bpf__load
#define _bpf__destroy	map_hash_bpf__destroy
#define _bpf__open_and_load	map_hash_bpf__open_and_load
#define _bpf__attach	map_hash_bpf__attach
#elif defined(TRACEPOINT) && defined(MAP_PERCPU_HASH)
#include "map_percpu_hash.skel.h"
#define struct_bpf	map_percpu_hash_bpf
#define _bpf__open_opts	map_percpu_hash_bpf__open_opts
#define _bpf__load	map_percpu_hash_bpf__load
#define _bpf__destroy	map_percpu_hash_bpf__destroy
#define _bpf__open_and_load	map_percpu_hash_bpf__open_and_load
#define _bpf__attach	map_percpu_hash_bpf__attach
#elif defined(TRACEPOINT) && defined(MAP_LRU_HASH)
#include "map_lru_hash.skel.h"
#define struct_bpf	map_lru_hash_bpf
#define _bpf__open_opts	map_lru_hash_bpf__open_opts
#define _bpf__load	map_lru_hash_bpf__load
#define _bpf__destroy	map_lru_hash_bpf__destroy
#define _bpf__open_and_load	map_lru_hash_bpf__open_and_load
#define _bpf__attach	map_lru_hash_bpf__attach
#elif defined(TRACEPOINT) && defined(MAP_LRU_PERCPU_HASH)
#include "map_lru_percpu_hash.skel.h"
#define struct_bpf	map_lru_percpu_hash_bpf
#define _bpf__open_opts	map_lru_percpu_hash_bpf__open_opts
#define _bpf__load	map_lru_percpu_hash_bpf__load
#define _bpf__destroy	map_lru_percpu_hash_bpf__destroy
#define _bpf__open_and_load	map_lru_percpu_hash_bpf__open_and_load
#define _bpf__attach	map_lru_percpu_hash_bpf__attach
#else
#error "Must define TRACEPOINT and one of MAP_HASH MAP_PERCPU_HASH"
#endif


void handle_event(void *ctx, int cpu, void *event, unsigned int event_sz)
{
	struct event_t *m = event;

	printf("%-6d %-6d %-16s(%-16s) %s %s ret = %d\n", m->pid, m->uid, m->comm,
		m->comm2, m->filename, m->cwd, m->ret);
#ifdef PARSE_AUXV
	printf(" auxv.type %ld, auxv.val 0x%lx\n", m->auxv.type, m->auxv.val);
#endif
}

void lost_event(void *ctx, int cpu, long long unsigned int event_sz)
{
	printf("lost event\n");
}

int main(void)
{
	int err, events_map_fd;
	struct struct_bpf *skel;
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

	skel = _bpf__open_opts(&opts);
	err = _bpf__load(skel);
	if (err) {
		printf("Failed to load BPF object\n");
		_bpf__destroy(skel);
		return 1;
	}

	print_bpf_log_buf(log_buf, sizeof(log_buf));
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

	events_map_fd = bpf_map__fd(skel->maps.events);

	pb = tl_perf_buffer__new(events_map_fd, 8, handle_event, lost_event);
	if (!pb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		_bpf__destroy(skel);
		return 1;
	}

	printf("Tracing execve(2) syscall, and kill 'ls' command.\n");

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
	_bpf__destroy(skel);
	return -err;
}
