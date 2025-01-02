#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <setjmp.h>
#include <net/if.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
/**
 * libbpf commit b78c75fcb347 ("Makefile: remove xsk.c and xsk.h") v1.0 remove
 * xsk.{c,h}, use libxdp instead.
 */
#if LIBBPF_MAJOR_VERSION < 1
#include <bpf/xsk.h>
#else
#include <xdp/xsk.h>
#endif
#include <sys/mman.h>
#include <sys/resource.h>
#include <linux/if_link.h>

#include "libbpf_wrapper.h"
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

static int exiting = false;
static sigjmp_buf jmp;

static void sig_handler(int sig)
{
	printf("Catch signal!!\n");
	exiting = true;
	siglongjmp(jmp, 1);
}

static void setup_xsk_socket(struct xsk_socket_info *xsk, char *ifname,
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

	struct xsk_umem_config umem_cfg = {
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
		.frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM,
		.flags = XSK_UMEM__DEFAULT_FLAGS,
	};

	if (xsk_umem__create(&umem->umem, umem->buffer, buffer_size, &umem->fq,
			     &umem->cq, &umem_cfg)) {
		fprintf(stderr, "Error creating UMEM: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	int err, ifindex, prog_fd, map_fd, map_key, sock_fd;
	struct xdp_xsk_bpf *skel;
	char *ifname;
	struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
	struct xsk_umem_info *umem_info = NULL;
	struct xsk_socket_info *sock_info = NULL;


	if (argc != 2) {
		fprintf(stderr, "Usage: %s <interface>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (setrlimit(RLIMIT_MEMLOCK, &rlim)) {
		fprintf(stderr, "Error setting rlimit: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);
	sigsetjmp(jmp, 1);
	if (exiting)
		goto cleanup;

	ifname = argv[1];
	ifindex = if_nametoindex(ifname);
	if (ifindex == 0) {
		fprintf(stderr, "Error getting ifindex: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	skel = xdp_xsk_bpf__open();
	err = xdp_xsk_bpf__load(skel);
	if (err) {
		fprintf(stderr, "failed to load skel.\n");
		goto cleanup;
	}

	prog_fd = bpf_program__fd(skel->progs.xdp_sock_prog);
	map_fd = bpf_map__fd(skel->maps.xsk_map);

	printf("map fd %d\n", map_fd);

	umem_info = calloc(1, sizeof(*umem_info));
	setup_umem(umem_info);

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

	struct pollfd fds = {};

	fds.fd = sock_fd;
	fds.events = POLLIN;

	while (!exiting) {
		int ret = poll(&fds, 1, -1);
		if (ret <= 0) {
			fprintf(stderr, "Failed poll xsk fd.\n");
			continue;
		}
		printf("Received packet, ret = %d, %m\n", ret);

		// Add your packet processing logic here
	}

cleanup:
	printf("Byebye!!\n");
	if (umem_info)
		xsk_umem__delete(umem_info->umem);
	if (sock_info)
		xsk_socket__delete(sock_info->xsk);
	tl_bpf_xdp_detach(ifindex, 0);
	xdp_xsk_bpf__destroy(skel);
	return 0;
}
