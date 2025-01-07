// SPDX-License-Identifier: GPL-3.0
#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <net/if.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/ip.h>

#include "libbpf_wrapper.h"
#include "libxdp_helpers.h"
#include "trace_helpers.h"
#include "xdp_xsk.skel.h"

struct xsk_umem_info {
	struct xsk_ring_prod fq;
	struct xsk_ring_cons cq;
	struct xsk_umem *umem;
	void *buffer;
};

struct xsk_socket_info {
	struct xsk_socket *xsk;
	struct xsk_ring_cons rx;
	struct xsk_ring_prod tx;
	struct xsk_umem_info *umem;
};

static int ifindex = 0;
static const char *ifname;

static int verbose = false;
static int exiting = false;

static pthread_t rx_thread, display_thread;

struct xsk_umem_info *umem_info = NULL;
struct xsk_socket_info *sock_info = NULL;

static const char argp_prog_doc[] =
	"USAGE: [-i <interface>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{ "verbose", 'v', "VERBOSE", 1, "Display detail during running" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		ifname = arg;
		ifindex = if_nametoindex(ifname);
		if (!ifindex)
			ifindex = atoi(ifname);
		break;
	case 'v':
		verbose = true;
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
	printf("Catch signal %d!!\n", sig);
	stop_read_trace_pipe();
	exiting = true;
}

void *display_info(void *arg)
{
	while (!exiting) {
		printf("info: avail ");
		printf("rx %d,", xsk_cons_nb_avail(&sock_info->rx, 64));
		printf("\n");
		printf("info: free ");
		printf("fq %d,", xsk_prod_nb_free(&umem_info->fq, 64));
		printf("\n");
		sleep(2);
	}
	return NULL;
}

static void setup_xsk_socket(struct xsk_socket_info *xsk, const char *ifname,
			     int queue_id)
{
	struct xsk_socket_config xsk_cfg = {
		.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.libbpf_flags = XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD,
		.xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST,
		.bind_flags = XDP_USE_NEED_WAKEUP,
	};

	if (xsk_socket__create(&xsk->xsk, ifname, queue_id, xsk->umem->umem,
			       &xsk->rx, &xsk->tx, &xsk_cfg)) {
		fprintf(stderr, "Error creating XSK socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void setup_umem(struct xsk_umem_info *umem)
{
	const int buffer_size = 2 * 1024 * 4096;

	umem->buffer = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE,
			    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (umem->buffer == MAP_FAILED) {
		fprintf(stderr, "Error allocating UMEM buffer: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("umem buffer %p\n", umem->buffer);

	struct xsk_umem_config umem_cfg = {
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
		.frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM,
		.flags = XSK_UMEM__DEFAULT_FLAGS,
	};

	if (xsk_umem__create(&umem->umem, umem->buffer, buffer_size,
			     &umem->fq, &umem->cq, &umem_cfg)) {
		fprintf(stderr, "Error creating UMEM: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("umem frame_size %d\n", XSK_UMEM__DEFAULT_FRAME_SIZE);
}

int xsk_populate_fill_ring(struct xsk_umem_info *umem_info)
{
	int i, ret;
	__u32 idx;
	/**
	 * Fill ring, see linux:xsk_populate_fill_ring()
	 */
	ret = xsk_ring_prod__reserve(&umem_info->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS, &idx);
	if (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS) {
		fprintf(stderr, "reserve fill ring failed.\n");
		return -1;
	}
	for (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS; i++) {
		__u64 addr = i * XSK_UMEM__DEFAULT_FRAME_SIZE;
		*xsk_ring_prod__fill_addr(&umem_info->fq, idx++) = addr;
	}
	xsk_ring_prod__submit(&umem_info->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS);
	return 0;
}

#define pr_pkt(fmt...) do { \
		fprintf(stdout, "\033[1;32m"); \
		fprintf(stdout, fmt); \
		fprintf(stdout, "\033[m"); \
	} while (0)

#define pr_pkt_err(fmt...) do { \
		fprintf(stderr, "\033[1;31m"); \
		fprintf(stderr, fmt); \
		fprintf(stderr, "\033[m"); \
	} while (0)

#define pr_pkt_dbg(fmt...) do { \
		fprintf(stderr, "\033[2m"); \
		fprintf(stderr, fmt); \
		fprintf(stderr, "\033[m"); \
	} while (0)

void handle_desc(void *data, size_t len)
{
	void *data_end = data + len;
	struct ethhdr *eth = data;
	struct iphdr *iph;
	static __u64 pkt_cnt = 0;

	if ((void *)(eth + 1) > data_end) {
		pr_pkt_err("Bad pkt.\n");
		return;
	}

	if (eth->h_proto != htons(ETH_P_IP)) {
		pr_pkt_dbg("Not ip pkt, ether proto 0x%x.\n", eth->h_proto);
		return;
	}

	iph = data + sizeof(struct ethhdr);
	if ((void *)(iph + 1) > data_end) {
		pr_pkt_err("Bad ip pkt.\n");
		return;
	}

	pkt_cnt++;

	switch (iph->protocol) {
	case IPPROTO_ICMP: /* 1 */
		pr_pkt("Get ICMP. %lld\n", pkt_cnt);
		break;
	case IPPROTO_TCP: /* 6 */
		pr_pkt("Get TCP. %lld\n", pkt_cnt);
		break;
	case IPPROTO_UDP: /* 17 */
		pr_pkt("Get UDP. %lld\n", pkt_cnt);
		break;
	default:
		pr_pkt_err("Unknown pkt %d.\n", iph->protocol);
		break;
	}
	return;
}

static void *rx_thread_callback(void *arg)
{
	int ret, sock_fd;
	struct pollfd fds = {};
	__u32 idx_rx = 0, idx_fq = 0;

	sock_fd = xsk_socket__fd(sock_info->xsk);

	fds.fd = sock_fd;
	fds.events = POLLIN;

	while (!exiting) {
		__u32 i, rcvd;

		kick_rx(sock_fd);
		ret = poll(&fds, 1, -1);
		if (ret <= 0) {
			fprintf(stderr, "Failed poll xsk fd.\n");
			continue;
		}

		rcvd = xsk_ring_cons__peek(&sock_info->rx, 64, &idx_rx);
		if (!rcvd)
			continue;

		ret = xsk_ring_prod__reserve(&umem_info->fq, rcvd, &idx_fq);
		while (ret != rcvd) {
			if (ret < 0) {
				fprintf(stderr, "fill ring reserve failed.\n");
				goto exit;
			}
			if (xsk_ring_prod__needs_wakeup(&umem_info->fq)) {
				ret = poll(&fds, 1, 1000);
				if (ret < 0) {
					fprintf(stderr, "poll failed.\n");
					goto exit;
				}
			}
			ret = xsk_ring_prod__reserve(&umem_info->fq, rcvd, &idx_fq);
		}

		for (i = 0; i < rcvd; i++) {
			const struct xdp_desc *desc = xsk_ring_cons__rx_desc(&sock_info->rx, idx_rx++);
			__u64 addr = desc->addr, orig;

			orig = xsk_umem__extract_addr(addr);
			addr = xsk_umem__add_offset_to_addr(addr);

			*xsk_ring_prod__fill_addr(&umem_info->fq, idx_fq++) = orig;

			if (verbose)
				printf("Handle desc: addr: 0x%llx, len: %d(0x%x), idx: %d, rcvd: %d\n",
					desc->addr, desc->len, desc->len, idx_rx, rcvd);
			handle_desc(xsk_umem__get_data(umem_info->buffer, addr), desc->len);
		}

		xsk_ring_prod__submit(&umem_info->fq, rcvd);
		xsk_ring_cons__release(&sock_info->rx, rcvd);
	}

exit:
	return NULL;
}

int main(int argc, char **argv)
{
	int err, prog_fd, map_fd, map_key, sock_fd;
	struct xdp_xsk_bpf *skel;
	struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == 0) {
		fprintf(stderr, "Error getting ifindex: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (setrlimit(RLIMIT_MEMLOCK, &rlim)) {
		fprintf(stderr, "Error setting rlimit: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);

	skel = xdp_xsk_bpf__open();
	err = xdp_xsk_bpf__load(skel);
	if (err) {
		fprintf(stderr, "failed to load skel.\n");
		goto cleanup;
	}

#if !defined(STRICT_SEC_NAME)
	bpf_program__set_type(skel->progs.xdp_sock_prog, BPF_PROG_TYPE_XDP);
#endif

	prog_fd = bpf_program__fd(skel->progs.xdp_sock_prog);
	map_fd = bpf_map__fd(skel->maps.xsk_map);

	printf("map fd %d\n", map_fd);

	umem_info = calloc(1, sizeof(*umem_info));
	setup_umem(umem_info);

	err = xsk_populate_fill_ring(umem_info);
	if (err)
		goto cleanup;

	sock_info = calloc(1, sizeof(*sock_info));
	sock_info->umem = umem_info;
	setup_xsk_socket(sock_info, ifname, 0);

	map_key = 0;
	sock_fd = xsk_socket__fd(sock_info->xsk);
	err = bpf_map_update_elem(map_fd, &map_key, &sock_fd, 0);
	if (err < 0) {
		fprintf(stderr, "Error updating XSKMAP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	err = tl_bpf_xdp_attach(ifindex, prog_fd, 0);
	if (err)
		goto cleanup;

	printf("XDP and XSK setup complete.\n");

	if (verbose)
		pthread_create(&display_thread, NULL, display_info, NULL);

	pthread_create(&rx_thread, NULL, rx_thread_callback, NULL);

	/* Main thread waiting in here */
	read_trace_pipe();
	pthread_join(rx_thread, NULL);

cleanup:
	printf("Byebye!!\n");

	if (verbose)
		pthread_join(display_thread, NULL);

	if (umem_info)
		xsk_umem__delete(umem_info->umem);
	if (sock_info)
		xsk_socket__delete(sock_info->xsk);
	tl_bpf_xdp_detach(ifindex, 0);
	xdp_xsk_bpf__destroy(skel);
	return 0;
}
