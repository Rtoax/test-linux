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
#define NAME tracepoint
#include "skel_defs.h"
#elif defined(TRACEPOINT) && defined(MAP_HASH)
#include "map_hash.skel.h"
#define NAME map_hash
#include "skel_defs.h"
#elif defined(TRACEPOINT) && defined(MAP_PERCPU_HASH)
#include "map_percpu_hash.skel.h"
#define NAME map_percpu_hash
#include "skel_defs.h"
#elif defined(TRACEPOINT) && defined(MAP_LRU_HASH)
#include "map_lru_hash.skel.h"
#define NAME map_lru_hash
#include "skel_defs.h"
#elif defined(TRACEPOINT) && defined(MAP_LRU_PERCPU_HASH)
#include "map_lru_percpu_hash.skel.h"
#define NAME map_lru_percpu_hash
#include "skel_defs.h"
#else
#error "Must define TRACEPOINT and one of MAP_HASH MAP_PERCPU_HASH"
#endif


void handle_event(void *ctx, int cpu, void *event, unsigned int event_sz)
{
	struct event_t *m = event;

	printf("%d %d %s(%s) file=%s cwd=%s ret=%d",
		m->pid, m->uid, m->comm, m->comm2, m->filename, m->cwd, m->ret);
#ifdef PARSE_AUXV
	printf(" auxv(type=%ld, val=0x%lx)", m->auxv.type, m->auxv.val);
#endif
	printf("\n");
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

	BPF__OPEN_AND_LOAD(skel, _bpf__open_and_load, _bpf__open_opts,
			_bpf__load, _bpf__destroy);

	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		_bpf__destroy(skel);
		return 1;
	}

	events_map_fd = bpf_map__fd(skel->maps.events);

	pb = libbpf_perf_buffer__new(events_map_fd, 8, handle_event, lost_event);
	if (!pb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		_bpf__destroy(skel);
		return 1;
	}

	printf("Tracing execve(2) syscall, and kill 'top' command.\n");

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
