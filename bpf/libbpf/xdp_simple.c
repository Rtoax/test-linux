#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <linux/if_xdp.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <malloc.h>
#include <net/if.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>

#include "trace_helpers.h"
#include "libbpf_wrapper.h"
#include "libxdp_helpers.h"

#include "xdp_simple.skel.h"
#include "xdp_simple.h"

#define struct_bpf	xdp_simple_bpf
#define _bpf__open	xdp_simple_bpf__open
#define _bpf__load	xdp_simple_bpf__load
#define _bpf__destroy	xdp_simple_bpf__destroy


static int ifindex = -1;
static const char *ifname;

static int ipv4_black_count = 0;
static struct ipv4_addr_t *ipv4_black_list = NULL;

static int verbose = 0;

static const char argp_prog_doc[] =
	"USAGE: [-i <ifname>] [-b <address>] [-v]\n"
	"\n"
	"Examples:\n"
	"\n";

static const struct argp_option opts[] = {
	{ "ifname", 'i', "INTERFACE", 0, "Network ifname to attach" },
	{ "black", 'b', "BLACK", 0, "Add address to black list" },
	{ "verbose", 'v', NULL, 1, "Display the detail, for debug maybe" },
	{},
};

static void add_black(const char *p)
{
	int err;
	struct sockaddr_in addr;

	err = inet_pton(AF_INET, p, &addr.sin_addr);
	if (err < 0) {
		fprintf(stderr, "Bad address %s\n", p);
		abort();
	}

	if (verbose)
		fprintf(stderr, "Add address %s(0x%x) to blacklist.\n", p,
			addr.sin_addr.s_addr);

	ipv4_black_list = realloc(ipv4_black_list, ++ipv4_black_count);

	ipv4_black_list[ipv4_black_count - 1].addr = addr.sin_addr.s_addr;
	ipv4_black_list[ipv4_black_count - 1].op = OP_BLACK;
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		ifname = arg;
		ifindex = if_nametoindex(ifname);
		if (!ifindex)
			ifindex = atoi(ifname);
		break;
	case 'b':
		add_black(arg);
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

static void sig_handler(int sig)
{
	read_trace_pipe_stop();
}

void handle_event(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct event_t *e = data;
	char buf[128], *ifname;

	ifname = if_indextoname(e->rx_ifindex, buf);

	printf("%-10s %-16s\n", ifname, strxdpaction(e->xdp_action));
}

void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
	printf("lost event\n");
}

int main(int argc, char *argv[])
{
	int err, i, prog_fd, map_fd, events_fd;
	struct struct_bpf *skel;
	struct perf_buffer *perf_buf = NULL;
	int xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify ifname with -i\n");
		return -EINVAL;
	}

	skel = _bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	bpf_program__set_type(skel->progs.xdp_dummy_prog, BPF_PROG_TYPE_XDP);

	err = _bpf__load(skel);
	if (err) {
		_bpf__destroy(skel);
		return 1;
	}

	prog_fd = bpf_program__fd(skel->progs.xdp_dummy_prog);
	map_fd = bpf_map__fd(skel->maps.map_blacklist);

	for (i = 0; i < ipv4_black_count; i++) {
		int key = ipv4_black_list[i].addr;
		err = bpf_map_update_elem(map_fd, &key, &ipv4_black_list[i], 0);
		if (err < 0) {
			printf("failed to update elem.\n");
			goto cleanup;
		}
	}

	events_fd = bpf_map__fd(skel->maps.events);

	perf_buf = tl_perf_buffer__new(events_fd, 8, handle_event, lost_event);
	if (!perf_buf) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}

	err = tl_bpf_xdp_attach(ifindex, prog_fd, xdp_flags);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

	read_trace_pipe_start();

	while (true) {
		err = perf_buffer__poll(perf_buf, 100 /* timeout, ms */);
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

cleanup:
	read_trace_pipe_wait();
	printf("Detach xdp from ifname %s\n", ifname);
	tl_bpf_xdp_detach(ifindex, xdp_flags);
	_bpf__destroy(skel);
	return 0;
}
