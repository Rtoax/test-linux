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
#include <sys/signalfd.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/ip.h>
#include <linux/icmp.h>

#include "libbpf_wrapper.h"
#include "libxdp_helpers.h"
#include "trace_helpers.h"
#include "xdp_xsk.skel.h"
#include "net_helpers.h"
#include "pkt_stream.h"
#include "log.h"


#define BATCH_SIZE	64

static int ifindex = 0;
static const char *ifname;

static int verbose = false;
static int exiting = false;

static pthread_t rx_thread, display_thread;
#if defined(TX_THREAD)
static pthread_t tx_thread;
#endif

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static struct xsk_umem_info *umem_info = NULL;
static struct xsk_socket_info *sock_info = NULL;

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
	pthread_kill(rx_thread, SIGUSR1);
#if defined(TX_THREAD)
	pthread_kill(tx_thread, SIGUSR1);
#endif
	exiting = true;

	if (sig == SIGSEGV)
		exit(EXIT_FAILURE);
}

static void read_sigfd(int sigfd, const char *msg)
{
	struct signalfd_siginfo fdsi;
	read(sigfd, &fdsi, sizeof(fdsi));
	psignal(fdsi.ssi_signo, msg);
}

void *display_info(void *arg)
{
	while (!exiting) {
		printf("info: avail ");
		printf("rx %d,", xsk_cons_nb_avail(&sock_info->rx, BATCH_SIZE));
		printf("\n");
		printf("info: free ");
		printf("fq %d,", xsk_prod_nb_free(&umem_info->fq, BATCH_SIZE));
		printf("\n");
		sleep(2);
	}
	return NULL;
}

void handle_rx_pkt(void *data, size_t len);

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

	xsk->rx_size = xsk_cfg.rx_size;
	xsk->tx_size = xsk_cfg.tx_size;
	xsk->queue_id = queue_id;
	xsk->bind_flags = xsk_cfg.bind_flags;

	printf("xsk rx_size %d\n", xsk->rx_size);
	printf("xsk tx_size %d\n", xsk->tx_size);
	printf("xsk queue_id %d\n", xsk->queue_id);

	display_xsk_ring("rx", &xsk->rx);
	display_xsk_ring("tx", &xsk->tx);
}

static void setup_umem(struct xsk_umem_info *umem)
{
	umem->buffer_size = UMEM_SIZE;

	umem->buffer = mmap(NULL, umem->buffer_size, PROT_READ | PROT_WRITE,
			    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (umem->buffer == MAP_FAILED) {
		fprintf(stderr, "Error allocating UMEM buffer: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct xsk_umem_config umem_cfg = {
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
		.frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM,
		.flags = XSK_UMEM__DEFAULT_FLAGS,
	};

	if (xsk_umem__create(&umem->umem, umem->buffer, umem->buffer_size,
			     &umem->fq, &umem->cq, &umem_cfg)) {
		fprintf(stderr, "Error creating UMEM: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	umem->fill_size = umem_cfg.fill_size;
	umem->comp_size = umem_cfg.comp_size;
	umem->num_frames = DEFAULT_UMEM_BUFFERS;
	umem->frame_size = umem_cfg.frame_size;
	umem->frame_headroom = umem_cfg.frame_headroom;
	umem->base_addr = DEFAULT_UMEM_BUFFERS * XSK_UMEM__DEFAULT_FRAME_SIZE;

	printf("umem buffer size 0x%lx, vaddr %p\n", umem->buffer_size, umem->buffer);
	printf("umem num_frames %d(0x%x)\n", umem->num_frames, umem->num_frames);
	printf("umem frame_size %d(0x%x)\n", umem->frame_size, umem->frame_size);
	printf("umem frame_headroom %d(0x%x)\n", umem->frame_headroom, umem->frame_headroom);
	printf("umem base_addr %d(0x%x)\n", umem->base_addr, umem->base_addr);

	display_xsk_umem("umem", umem->umem);
}

/**
 * Fill ring, see linux:xsk_populate_fill_ring()
 */
int xsk_populate_fill_ring(struct xsk_umem_info *umem_info)
{
	int i, ret;
	__u32 idx;

	ret = xsk_ring_prod__reserve(&umem_info->fq, umem_info->fill_size, &idx);
	if (ret != umem_info->fill_size) {
		fprintf(stderr, "reserve fill ring failed.\n");
		return -1;
	}
	for (i = 0; i < umem_info->fill_size; i++) {
		__u64 addr = i * umem_info->frame_size;
		*xsk_ring_prod__fill_addr(&umem_info->fq, idx++) = addr;
		if (verbose && i % 100 == 0)
			pr_dbg("fill_addr: 0x%llx\n", addr);
	}
	xsk_ring_prod__submit(&umem_info->fq, umem_info->fill_size);
	return 0;
}

int receive_pkts(struct pollfd *pfds, size_t nr_pfds)
{
	int ret;
	__u32 i, rcvd;
	__u32 idx_rx = 0, idx_fq = 0;

	rcvd = xsk_ring_cons__peek(&sock_info->rx, BATCH_SIZE, &idx_rx);
	if (!rcvd)
		return -ENOENT;

	ret = xsk_ring_prod__reserve(&umem_info->fq, rcvd, &idx_fq);
	while (ret != rcvd) {
		if (ret < 0) {
			fprintf(stderr, "fill ring reserve failed.\n");
			goto exit;
		}
		if (xsk_ring_prod__needs_wakeup(&umem_info->fq)) {
			ret = poll(pfds, nr_pfds, 1000);
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
			pr_dbg("Handle rx desc: addr: 0x%llx(orig: 0x%llx), "
			       "len: %d(0x%x), idx: %d, rcvd: %d\n",
			       desc->addr, orig, desc->len, desc->len, idx_rx, rcvd);

		handle_rx_pkt(xsk_umem__get_data(umem_info->buffer, addr), desc->len);
	}

	xsk_ring_prod__submit(&umem_info->fq, rcvd);
	xsk_ring_cons__release(&sock_info->rx, rcvd);

exit:
	return 0;
}

#if defined(TX_THREAD)
int send_pkts(struct pollfd *pfds, size_t nr_pfds, int sigfd)
{
/* Handle SIGINT */
#define TX_EXIT_WITH_SIG	0xf1f1
	int ret, sock_fd;
	__u32 i, idx = 0;
	int re_poll;

	sock_fd = xsk_socket__fd(sock_info->xsk);

	while (xsk_ring_prod__reserve(&sock_info->tx, BATCH_SIZE, &idx) < BATCH_SIZE) {
poll_1:
		re_poll = true;
		ret = poll(pfds, nr_pfds, -1);
		if (ret <= 0) {
			fprintf(stderr, "Poll error %d\n", ret);
			pthread_exit(NULL);
		}
		for (i = 0; i < nr_pfds; i++) {
			if (pfds[i].revents == 0)
				continue;
			if (pfds[i].fd == sock_fd) {
				re_poll = false;
			} else if (pfds[i].fd == sigfd) {
				read_sigfd(sigfd, "send_pkts interrupt");
				return TX_EXIT_WITH_SIG;
			}
		}
		/* above poll() not return for sock_fd, re-poll */
		if (re_poll)
			goto poll_1;

		if (xsk_ring_prod__needs_wakeup(&sock_info->tx))
			kick_tx(sock_fd);

		unsigned int rcvd;

		rcvd = xsk_ring_cons__peek(&umem_info->cq, BATCH_SIZE, &idx);
		if (rcvd)
			xsk_ring_cons__release(&umem_info->cq, rcvd);
	}

	for (i = 0; i < BATCH_SIZE; i++) {
		struct xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&sock_info->tx, idx + i);

		/* TODO: set tx_desc addr and len */
		(void)tx_desc;
	}

	/* TODO: Waiting for rx_thread */

	xsk_ring_prod__submit(&sock_info->tx, i);

poll_2:
	re_poll = true;
	ret = poll(pfds, nr_pfds, -1);
	if (ret <= 0) {
		fprintf(stderr, "poll tx failed, %m\n");
		return -errno;
	}
	for (i = 0; i < nr_pfds; i++) {
		if (pfds[i].revents == 0)
			continue;
		if (pfds[i].fd == sock_fd) {
			re_poll = false;
		} else if (pfds[i].fd == sigfd) {
			read_sigfd(sigfd, "send_pkts interrupt");
			return TX_EXIT_WITH_SIG;
		}
	}

	/* above poll() not return for sock_fd, re-poll */
	if (re_poll)
		goto poll_2;

	return 0;
}
#endif

/**
 * see linux: tools/testing/selftests/bpf/xskxceiver.c:complete_pkts()
 */
void complete_tx_pkts(int batch_size)
{
	__u32 idx = 0;
	unsigned int rcvd;

	if (xsk_ring_prod__needs_wakeup(&sock_info->tx))
		kick_tx(xsk_socket__fd(sock_info->xsk));

	rcvd = xsk_ring_cons__peek(&umem_info->cq, batch_size, &idx);
	if (rcvd) {
#if 1 // SIGSEGV here
		__u64 addr = *xsk_ring_cons__comp_addr(&umem_info->cq, idx + rcvd - 1);
		pr_dbg("complete addr 0x%llx(%p)\n", addr, xsk_umem__get_data(umem_info->buffer, addr));
#endif
		xsk_ring_cons__release(&umem_info->cq, rcvd);
	}
}

void icmp_reply(void *rx_pkt, struct icmphdr *request)
{
	int ret, sock_fd;
	__u32 idx = 0;
	struct pollfd fd;

	sock_fd = xsk_socket__fd(sock_info->xsk);

	fd.fd = sock_fd;
	fd.events = POLLOUT;

	while (xsk_ring_prod__reserve(&sock_info->tx, 1, &idx)) {
		ret = poll(&fd, 1, -1);
		if (ret <= 0) {
			fprintf(stderr, "Poll error %d\n", ret);
			pthread_exit(NULL);
		}

		complete_tx_pkts(1);
	}

	pr_dbg("tx queue: cached_prod %d, cached_cons %d\n",
		   sock_info->tx.cached_prod, sock_info->tx.cached_cons);

	struct xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&sock_info->tx, idx);

	__u64 addr = idx * umem_info->frame_size;
	addr = xsk_umem__add_offset_to_addr(addr);
	void *tx_pkt_buf = xsk_umem__get_data(umem_info->buffer, addr);

	tx_desc->addr = addr;
	tx_desc->len = gen_pkt_icmp_reply(rx_pkt, request, tx_pkt_buf)
				+ sizeof(struct ethhdr) + sizeof(struct iphdr);

	pr_dbg("tx icmp echo reply, idx = %d, addr 0x%llx(rx: %p, tx: %p), len %d.\n",
		   idx, addr, rx_pkt, tx_pkt_buf, tx_desc->len);

	xsk_ring_prod__submit(&sock_info->tx, 1);

	if (verbose) {
		display_xsk_ring("fq", &umem_info->fq);
		display_xsk_ring("cq", &umem_info->cq);
		display_xsk_ring("rx", &sock_info->rx);
		display_xsk_ring("tx", &sock_info->tx);
	}

	ret = poll(&fd, 1, -1);
	if (ret <= 0) {
		fprintf(stderr, "Poll error %d\n", ret);
		pthread_exit(NULL);
	}

	complete_tx_pkts(1);

	return;
}

void handle_rx_pkt(void *data, size_t len)
{
	void *data_end = data + len;
	struct ethhdr *eth = data;
	struct iphdr *iph;
	struct icmphdr *icmph;
	static __u64 pkt_cnt = 0;

	if ((void *)(eth + 1) > data_end) {
		pr_err("Bad pkt.\n");
		return;
	}

	if (eth->h_proto != htons(ETH_P_IP)) {
		pr_dbg("Not ip pkt, ether proto 0x%x.\n", eth->h_proto);
		return;
	}

	iph = data + sizeof(struct ethhdr);
	if ((void *)(iph + 1) > data_end) {
		pr_err("Bad ip pkt.\n");
		return;
	}

	pkt_cnt++;

	switch (iph->protocol) {
	case IPPROTO_ICMP: /* 1 */
		pr_inf("Get ICMP(%8lld): ", pkt_cnt);
		icmph = (void *)(iph + 1);
		dump_icmp(icmph, len - sizeof(struct ethhdr) - sizeof(struct iphdr));
		icmp_reply(data, icmph);
		break;
	case IPPROTO_TCP: /* 6 */
		pr_inf("Get TCP. %lld\n", pkt_cnt);
		break;
	case IPPROTO_UDP: /* 17 */
		pr_inf("Get UDP. %lld\n", pkt_cnt);
		break;
	default:
		pr_err("Unknown pkt %d.\n", iph->protocol);
		break;
	}
	return;
}

static void *rx_thread_callback(void *arg)
{
	int ret, sock_fd, sigfd;
	struct pollfd pfds[2] = {};
	sigset_t sigmask;

	sock_fd = xsk_socket__fd(sock_info->xsk);

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
	sigfd = signalfd(-1, &sigmask, 0);

	pfds[0].fd = sock_fd;
	pfds[0].events = POLLIN;
	pfds[1].fd = sigfd;
	pfds[1].events = POLLIN;

	while (!exiting) {
		__u32 i;

		kick_rx(sock_fd);

		ret = poll(pfds, 2, -1);
		if (ret <= 0) {
			fprintf(stderr, "Failed poll xsk fd.\n");
			continue;
		}

		for (i = 0; i < 2; i++) {
			if (pfds[i].revents == 0)
				continue;
			if (pfds[i].fd == sock_fd) {
				if (receive_pkts(pfds, 2))
					continue;
			} else if (pfds[i].fd == sigfd) {
				read_sigfd(sigfd, "rx_thread terminate");
				goto exit;
			}
		}
	}

exit:
	close(sigfd);
	return NULL;
}

#if defined(TX_THREAD)
static void *tx_thread_callback(void *arg)
{
	int ret, sock_fd, sigfd;
	struct pollfd pfds[2] = {};
	sigset_t sigmask;

	sock_fd = xsk_socket__fd(sock_info->xsk);

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
	sigfd = signalfd(-1, &sigmask, 0);

	pfds[0].fd = sock_fd;
	pfds[0].events = POLLOUT;
	pfds[1].fd = sigfd;
	pfds[1].events = POLLIN;

	while (!exiting) {
		__u32 i;

		ret = poll(pfds, 2, -1);
		if (ret <= 0) {
			fprintf(stderr, "Failed poll xsk fd.\n");
			continue;
		}

		for (i = 0; i < 2; i++) {
			if (pfds[i].revents == 0)
				continue;

			if (pfds[i].fd == sock_fd) {
				/* Only poll socket fd, skip signal fd */
				ret = send_pkts(pfds, 2, sigfd);
				if (ret) {
					if (ret == TX_EXIT_WITH_SIG)
						goto exit;
					else
						continue;
				}
			} else if (pfds[i].fd == sigfd) {
				read_sigfd(sigfd, "tx_thread terminate");
				goto exit;
			}
		}
	}

exit:
	close(sigfd);
	return NULL;
}
#endif

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
#if defined(TX_THREAD)
	pthread_create(&tx_thread, NULL, tx_thread_callback, NULL);
#endif

	/* Main thread waiting in here */
	read_trace_pipe();
	pthread_join(rx_thread, NULL);
#if defined(TX_THREAD)
	pthread_join(tx_thread, NULL);
#endif

cleanup:
	printf("Byebye!!\n");

	if (verbose)
		pthread_join(display_thread, NULL);

	if (sock_info)
		xsk_socket__delete(sock_info->xsk);
	if (umem_info) {
		xsk_umem__delete(umem_info->umem);
		munmap(umem_info->buffer, umem_info->buffer_size);
	}
	tl_bpf_xdp_detach(ifindex, 0);
	xdp_xsk_bpf__destroy(skel);
	return 0;
}
