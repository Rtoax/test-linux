#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include "config-map.h"
#include "config-map.skel.h"
#include "trace_helpers.h"
#include "libbpf_wrapper.h"


void handle_event(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct data_t *m = data;

	printf("%-6d %-6d %-4d %-16s %s\n", m->pid, m->uid, m->counter, m->command, m->message);
}

void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
	printf("lost event\n");
}

int main(void)
{
	int err, event_map_fd;
	struct config_map_bpf *skel;
	struct perf_buffer *pb = NULL;
	char log_buf[64 * 1024];

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

#if defined(LIBBPF_OPTS)
	LIBBPF_OPTS(bpf_object_open_opts, opts,
		.kernel_log_buf = log_buf,
		.kernel_log_size = sizeof(log_buf),
		.kernel_log_level = 1,
	);

	skel = config_map_bpf__open_opts(&opts);
	err = config_map_bpf__load(skel);
	if (err) {
		printf("Failed to load BPF object\n");
		config_map_bpf__destroy(skel);
		return 1;
	}
#else
	skel = config_map_bpf__open_and_load();
#endif
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	print_bpf_log_buf(log_buf, sizeof(log_buf));

	/**
	 * Configure a message to use only if the UID for the event is current
	 * user.
	 */
	uint32_t key = getuid();
	struct msg_t msg;
	const char *m = "Hello RT";
	strncpy((char *)&msg.message, m, strlen(m));

	printf("Config message for uid = %d\n", key);
	printf("event max entries %d\n", bpf_map__max_entries(skel->maps.event));
	printf("config_hash max entries %d\n", bpf_map__max_entries(skel->maps.config_hash));
/**
 * libbpf commit 650adc5118f1 ("libbpf: Add safer high-level wrappers for map
 * operations") support bpf_map__update_elem()
 */
#if LIBBPF_MAJOR_VERSION >= 1 || (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 8)
	bpf_map__update_elem(skel->maps.config_hash, &key, sizeof(key), &msg,
				sizeof(msg), 0);
#else
	int msg_map_fd = bpf_map__fd(skel->maps.config_hash);
	err = bpf_map_update_elem(msg_map_fd, &key, &msg, 0);
	if (err < 0) {
		printf("failed to update elem.\n");
		config_map_bpf__destroy(skel);
		return 1;
	}
#endif

	/* Attach the progam to the event */
	err = config_map_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		config_map_bpf__destroy(skel);
		return 1;
	}

	event_map_fd = bpf_map__fd(skel->maps.event);

	pb = tl_perf_buffer__new(event_map_fd, 8, handle_event, lost_event);
	if (!pb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		config_map_bpf__destroy(skel);
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
	config_map_bpf__destroy(skel);
	return -err;
}
