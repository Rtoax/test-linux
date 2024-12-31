#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <net/if.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bpf/xsk.h>
#include <xdp/xsk.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <linux/if_link.h>

#define MAX_SOCKS 1

struct xsk_umem_info {
	struct xsk_umem *umem;
	void *buffer;
};

struct xsk_socket_info {
	struct xsk_socket *xsk;
	struct xsk_ring_cons rx;
	struct xsk_ring_prod tx;
	struct xsk_umem_info *umem;
};

static void setup_xdp_program(int ifindex, const char *filename)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type = BPF_PROG_TYPE_XDP,
		.file = filename,
	};
	struct bpf_object *obj;
	int prog_fd;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd)) {
		fprintf(stderr, "Error loading XDP program: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (bpf_set_link_xdp_fd(ifindex, prog_fd, 0) < 0) {
		fprintf(stderr, "Error attaching XDP program: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void setup_xsk_socket(struct xsk_socket_info *xsk, char *ifname,
			     int queue_id)
{
	struct xsk_socket_config xsk_cfg = {
		.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.libbpf_flags = 0,
		.xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST,
		.bind_flags = XDP_USE_NEED_WAKEUP,
	};

	if (xsk_socket__create(&xsk->xsk, ifname, queue_id, xsk->umem->umem, &xsk->rx, &xsk->tx, &xsk_cfg)) {
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
		.flags = 0,
	};

	if (xsk_umem__create(&umem->umem, umem->buffer, buffer_size, NULL, NULL, &umem_cfg)) {
		fprintf(stderr, "Error creating UMEM: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
	if (setrlimit(RLIMIT_MEMLOCK, &rlim)) {
		fprintf(stderr, "Error setting rlimit: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <interface> <xdp_prog.o>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *ifname = argv[1];
	int ifindex = if_nametoindex(ifname);
	if (ifindex == 0) {
		fprintf(stderr, "Error getting ifindex: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	setup_xdp_program(ifindex, argv[2]);

	struct xsk_umem_info *umem_info = calloc(1, sizeof(*umem_info));
	setup_umem(umem_info);

	struct xsk_socket_info *sock_info = calloc(1, sizeof(*sock_info));
	sock_info->umem = umem_info;
	setup_xsk_socket(sock_info, ifname, 0);

	int map_fd = bpf_obj_get("/sys/fs/bpf/xsk_map");
	if (map_fd < 0) {
		fprintf(stderr, "Error getting XSKMAP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int key = 0;
	int fd = xsk_socket__fd(sock_info->xsk);
	if (bpf_map_update_elem(map_fd, &key, &fd, 0) < 0) {
		fprintf(stderr, "Error updating XSKMAP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("XDP and XSK setup complete.\n");

	// Add your packet processing logic here

	return 0;
}
