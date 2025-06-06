#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#include <net/if.h>
#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket_helpers.h"
#include "socket_filter.h"
#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#if defined(SOCKET_FILTER) && !defined(MAP_ARRAY) && !defined(MAP_PERCPU_ARRAY)
#include "socket_filter.skel.h"
#define struct_bpf	socket_filter_bpf
#define _bpf__open	socket_filter_bpf__open
#define _bpf__load	socket_filter_bpf__load
#define _bpf__destroy	socket_filter_bpf__destroy
#elif defined(SOCKET_FILTER) && defined(MAP_ARRAY)
#include "map_array.skel.h"
#define struct_bpf	map_array_bpf
#define _bpf__open	map_array_bpf__open
#define _bpf__load	map_array_bpf__load
#define _bpf__destroy	map_array_bpf__destroy
#elif defined(SOCKET_FILTER) && defined(MAP_PERCPU_ARRAY)
#include "map_percpu_array.skel.h"
#define struct_bpf	map_percpu_array_bpf
#define _bpf__open	map_percpu_array_bpf__open
#define _bpf__load	map_percpu_array_bpf__load
#define _bpf__destroy	map_percpu_array_bpf__destroy
#endif

static volatile bool exiting = false;
static int map_fd = -1;

const char *interface;

const char argp_prog_doc[] =
	"USAGE: [-i <interface>]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		interface = arg;
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


static const char *ipproto_mapping[IPPROTO_MAX] = {
	[IPPROTO_IP] = "IP",	   [IPPROTO_ICMP] = "ICMP",	  [IPPROTO_IGMP] = "IGMP",
	[IPPROTO_IPIP] = "IPIP",   [IPPROTO_TCP] = "TCP",	  [IPPROTO_EGP] = "EGP",
	[IPPROTO_PUP] = "PUP",	   [IPPROTO_UDP] = "UDP",	  [IPPROTO_IDP] = "IDP",
	[IPPROTO_TP] = "TP",	   [IPPROTO_DCCP] = "DCCP",	  [IPPROTO_IPV6] = "IPV6",
	[IPPROTO_RSVP] = "RSVP",   [IPPROTO_GRE] = "GRE",	  [IPPROTO_ESP] = "ESP",
	[IPPROTO_AH] = "AH",	   [IPPROTO_MTP] = "MTP",	  [IPPROTO_BEETPH] = "BEETPH",
	[IPPROTO_ENCAP] = "ENCAP", [IPPROTO_PIM] = "PIM",	  [IPPROTO_COMP] = "COMP",
	[IPPROTO_SCTP] = "SCTP",   [IPPROTO_UDPLITE] = "UDPLITE", [IPPROTO_MPLS] = "MPLS",
	[IPPROTO_RAW] = "RAW"
};

static void sig_handler(int sig)
{
	exiting = true;
}

static inline void ltoa(uint32_t addr, char *dst)
{
	snprintf(dst, 16, "%u.%u.%u.%u", (addr >> 24) & 0xFF, (addr >> 16) & 0xFF,
		 (addr >> 8) & 0xFF, (addr & 0xFF));
}

static int handle_event(void *ctx, void *data, size_t data_sz)
{
	const struct so_event *e = data;
	char ifname[IF_NAMESIZE];
	char sstr[16] = {}, dstr[16] = {};

	if (e->pkt_type != PACKET_HOST)
		return 0;

	if (e->ip_proto < 0 || e->ip_proto >= IPPROTO_MAX)
		return 0;

	if (!if_indextoname(e->ifindex, ifname))
		return 0;

	ltoa(ntohl(e->src_addr), sstr);
	ltoa(ntohl(e->dst_addr), dstr);

	if (map_fd != -1) {
		long long tcp_cnt, udp_cnt, icmp_cnt;
		int key;

		key = IPPROTO_TCP;
		assert(bpf_map_lookup_elem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPROTO_UDP;
		assert(bpf_map_lookup_elem(map_fd, &key, &udp_cnt) == 0);

		key = IPPROTO_ICMP;
		assert(bpf_map_lookup_elem(map_fd, &key, &icmp_cnt) == 0);

		printf("TCP: %lld, UDP: %lld, ICMP: %lld, ", tcp_cnt, udp_cnt, icmp_cnt);
	}

	printf("interface: %s\tprotocol: %s\t%s:%d(src) -> %s:%d(dst)\n", ifname,
	       ipproto_mapping[e->ip_proto], sstr, ntohs(e->port16[0]), dstr, ntohs(e->port16[1]));

	return 0;
}

int main(int argc, char *argv[])
{
	int err, sock, prog_fd;
	struct struct_bpf *skel;
	struct ring_buffer *rb = NULL;

	interface = "lo";

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	/* Cleaner handling of Ctrl-C */
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	skel = _bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	fprintf(stderr, "Track interface %s\n", interface);
	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);

	err = _bpf__load(skel);
	if (err) {
		_bpf__destroy(skel);
		return 1;
	}

	map_fd = bpf_map__fd(skel->maps.proto_cnt);

	rb = ring_buffer__new(bpf_map__fd(skel->maps.ring_buf), handle_event, NULL, NULL);
	if (!rb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}

	/* Create raw socket for localhost interface */
	sock = open_raw_sock(interface);
	if (sock < 0) {
		err = -2;
		fprintf(stderr, "Failed to open raw socket of interface %s\n",
			interface);
		goto cleanup;
	}

	/* Attach BPF program to raw socket */
	prog_fd = bpf_program__fd(skel->progs.bpf_prog1);
	if (setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd, sizeof(prog_fd))) {
		err = -3;
		fprintf(stderr, "Failed to attach to raw socket\n");
		goto cleanup;
	}

	/* Process events */
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
		sleep(1);
	}

cleanup:
	ring_buffer__free(rb);
	_bpf__destroy(skel);
	return 0;
}
