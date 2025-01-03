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
#include <setjmp.h>
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

#if defined(XDP_BASIC)
#include "xdp.skel.h"
#define struct_bpf	xdp_bpf
#define _bpf__open	xdp_bpf__open
#define _bpf__load	xdp_bpf__load
#define _bpf__destroy	xdp_bpf__destroy
#elif defined(XDP_DEVMAP)
#include "xdp_devmap.skel.h"
#define struct_bpf	xdp_devmap_bpf
#define _bpf__open	xdp_devmap_bpf__open
#define _bpf__load	xdp_devmap_bpf__load
#define _bpf__destroy	xdp_devmap_bpf__destroy
#elif defined(XDP_CPUMAP)
#include "xdp_cpumap.skel.h"
#define struct_bpf	xdp_cpumap_bpf
#define _bpf__open	xdp_cpumap_bpf__open
#define _bpf__load	xdp_cpumap_bpf__load
#define _bpf__destroy	xdp_cpumap_bpf__destroy
#elif defined(XDP_XSKMAP)
#include "xdp_xskmap.skel.h"
#define struct_bpf	xdp_xskmap_bpf
#define _bpf__open	xdp_xskmap_bpf__open
#define _bpf__load	xdp_xskmap_bpf__load
#define _bpf__destroy	xdp_xskmap_bpf__destroy
#endif

static volatile bool exiting = false;
static sigjmp_buf jmp;

int ifindex = -1;
const char *interface;
#if defined(XDP_DEVMAP)
int o_ifindex = -1;
const char *out_interface;
#elif defined(XDP_CPUMAP)
int cpu = -1;
#endif

const char argp_prog_doc[] =
#if defined(XDP_BASIC) || defined(XDP_XSKMAP)
	"USAGE: [-i <interface>]\n";
#elif defined(XDP_DEVMAP)
	"USAGE: [-i <interface>] [-o <interface>]\n";
#elif defined(XDP_CPUMAP)
	"USAGE: [-i <interface>] [-c <cpu>]\n";
#endif

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
#if defined(XDP_DEVMAP)
	{ "outinterface", 'o', "OUT-INTERFACE", 0, "Network interface to redirect" },
#elif defined(XDP_CPUMAP)
	{ "cpu", 'c', "CPU", 0, "Redirect to cpu" },
#endif
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		interface = arg;
		ifindex = if_nametoindex(interface);
		if (!ifindex)
			ifindex = atoi(interface);
		break;
#if defined(XDP_DEVMAP)
	case 'o':
		out_interface = arg;
		o_ifindex = if_nametoindex(out_interface);
		if (!o_ifindex)
			o_ifindex = atoi(out_interface);
		break;
#elif defined(XDP_CPUMAP)
	case 'c':
		cpu = atoi(arg);
		break;
#endif
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
	exiting = true;
	siglongjmp(jmp, 1);
}

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;

	return vfprintf(stderr, format, args);
}

void display_xdp_ring_offset(const char *pfx, struct xdp_ring_offset *off)
{
	printf("%s : producer=%lld, consumer=%lld, desc=%lld, flags=%llx\n",
		pfx ?: "", off->producer, off->consumer, off->desc, off->flags);
};

int main(int argc, char *argv[])
{
	int err, prog_fd;
	struct struct_bpf *skel;
	int xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);
	sigsetjmp(jmp, 1);
	if (exiting)
		goto cleanup;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify interface with -i\n");
		return -EINVAL;
	}
#if defined(XDP_DEVMAP)
	if (o_ifindex == -1) {
		fprintf(stderr, "Need specify out interface with -o\n");
		return -EINVAL;
	}
#elif defined(XDP_CPUMAP)
	if (cpu == -1) {
		fprintf(stderr, "Need specify redirect cpu with -c\n");
		return -EINVAL;
	}
#endif

	skel = _bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

#if defined(XDP_BASIC) || defined(XDP_XSKMAP)
	fprintf(stderr, "Track interface %s, index %d\n", interface, ifindex);
#elif defined(XDP_DEVMAP)
	fprintf(stderr, "Redirect %s(%d) to %s(%d)\n", interface, ifindex,
		out_interface, o_ifindex);
#elif defined(XDP_CPUMAP)
	fprintf(stderr, "Redirect %s(%d) to cpu %d\n", interface, ifindex,
		cpu);
#endif
	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);

#if !defined(STRICT_SEC_NAME)
# if defined(XDP_BASIC)
	bpf_program__set_type(skel->progs.xdp_printk, BPF_PROG_TYPE_XDP);
# elif defined(XDP_DEVMAP)
	bpf_program__set_type(skel->progs.xdp_redir_prog, BPF_PROG_TYPE_XDP);
	bpf_program__set_type(skel->progs.xdp_devmap_printk, BPF_PROG_TYPE_XDP);
# endif
#endif

	err = _bpf__load(skel);
	if (err) {
		_bpf__destroy(skel);
		return 1;
	}

#if defined(XDP_BASIC)
	/* Attach BPF program to raw socket */
	prog_fd = bpf_program__fd(skel->progs.xdp_printk);

	err = tl_bpf_xdp_attach(ifindex, prog_fd, xdp_flags);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

#elif defined(XDP_DEVMAP) /* Test devmap */
	int map_fd, o_prog_fd;
	__u32 idx = 0;
	struct bpf_devmap_val val;

	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	o_prog_fd = bpf_program__fd(skel->progs.xdp_devmap_printk);
	map_fd = bpf_map__fd(skel->maps.devmap_ports);

	val.ifindex = o_ifindex;
	val.bpf_prog.fd = o_prog_fd;

	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	if (err < 0) {
		printf("failed to update elem, err = %d, mapfd %d, progfd %d.\n",
			err, map_fd, o_prog_fd);
		goto cleanup;
	}

	err = tl_bpf_xdp_attach(ifindex, prog_fd, XDP_FLAGS_SKB_MODE);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

#elif defined(XDP_CPUMAP) /* Test cpumap */

	int map_fd, run_map_fd, dummy_prog_fd;
	__u32 idx = 0;
	struct bpf_cpumap_val val;

	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	dummy_prog_fd = bpf_program__fd(skel->progs.xdp_dummy_cpumap);

	map_fd = bpf_map__fd(skel->maps.cpu_map);
	run_map_fd = bpf_map__fd(skel->maps.run_on_cpu);

	err = bpf_map_update_elem(run_map_fd, &idx, &cpu, 0);
	if (err < 0) {
		printf("failed to update run elem, err = %d, mapfd %d.\n",
			err, run_map_fd);
		goto cleanup;
	}

	val.qsize = 192;
	val.bpf_prog.fd = dummy_prog_fd;

	err = bpf_map_update_elem(map_fd, &cpu, &val, 0);
	if (err < 0) {
		printf("failed to update cpu elem, err = %d, mapfd %d.\n",
			err, map_fd);
		goto cleanup;
	}

	err = tl_bpf_xdp_attach(ifindex, prog_fd, XDP_FLAGS_SKB_MODE);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

#elif defined(XDP_XSKMAP)

	int sock_fd;
	static const int chunk_size = 4096;
	static const int chunk_count = 4096;
	static const int umem_len = chunk_size * chunk_count;
	unsigned char *umem;
	int xsk_map_fd;

	prog_fd = bpf_program__fd(skel->progs.xsk_redir_prog);
	xsk_map_fd = bpf_map__fd(skel->maps.xsks_map);

	sock_fd = socket(AF_XDP, SOCK_RAW | SOCK_CLOEXEC, 0);
	if (sock_fd < 0) {
		perror("socket");
		goto cleanup;
	}

#ifdef UMEM_WITHOUT_MMAP
	/**
	 * Never use memalign()/malloc(), use mmap(2) instead, otherwise, cause
	 *
	 * setsockopt XDP_UMEM_REG: Invalid argument
	 */
	umem = memalign(4096, umem_len);
#else
	umem = mmap(NULL, umem_len, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
	printf("umem = %p\n", umem);

	struct xdp_umem_reg umem_reg = {};

	umem_reg.addr = (__u64)(void *)umem;
	umem_reg.len = umem_len;
	umem_reg.chunk_size = chunk_size;
	/**
	 * headroom, if set, the packet data will not be stored from the start
	 * address of each chunk, but the memory of the headroom size will be
	 * reserved before the packet data is stored. Headroom is very common
	 * in tunnel networks to facilitate the encapsulation of the outer
	 * header;
	 */
	umem_reg.headroom = 0;
	umem_reg.flags = 0;

	err = setsockopt(sock_fd, SOL_XDP, XDP_UMEM_REG, &umem_reg, sizeof(umem_reg));
	if (err < 0) {
		perror("setsockopt XDP_UMEM_REG");
		goto cleanup;
	}

	static const int ring_size = 512;

	err = 0;
	/**
	 * FILL RING and COMPLETION RING are required for UMEM, while RX and TX
	 * are optional for AF_XDP socket. For example, if AF_XDP socket only
	 * receives packets, you only need to set the size of RX RING.
	 */
	err += setsockopt(sock_fd, SOL_XDP, XDP_RX_RING, &ring_size, sizeof(ring_size));
	err += setsockopt(sock_fd, SOL_XDP, XDP_TX_RING, &ring_size, sizeof(ring_size));
	err += setsockopt(sock_fd, SOL_XDP, XDP_UMEM_FILL_RING, &ring_size, sizeof(ring_size));
	err += setsockopt(sock_fd, SOL_XDP, XDP_UMEM_COMPLETION_RING, &ring_size, sizeof(ring_size));
	if (err < 0) {
		perror("setsockopt RINGs");
		goto cleanup;
	}

	struct xdp_mmap_offsets offs = {0};
	socklen_t optlen = sizeof(offs);

	if (getsockopt(sock_fd, SOL_XDP, XDP_MMAP_OFFSETS, &offs, &optlen) < 0) {
		perror("getsockopt XDP_MMAP_OFFSETS");
		goto cleanup;
	}

	display_xdp_ring_offset("RX", &offs.rx);
	display_xdp_ring_offset("TX", &offs.tx);
	display_xdp_ring_offset("FR", &offs.fr);
	display_xdp_ring_offset("CR", &offs.cr);

	void *rx_mem, *tx_mem, *fi_mem, *co_mem;

	rx_mem = mmap(NULL, offs.rx.desc + ring_size * sizeof(struct xdp_desc),
		      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
		      sock_fd, XDP_PGOFF_RX_RING);
	if (rx_mem == MAP_FAILED) {
		perror("mmap rx_mem");
		goto cleanup;
	}

	tx_mem = mmap(NULL, offs.tx.desc + ring_size * sizeof(struct xdp_desc),
		      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
		      sock_fd, XDP_PGOFF_TX_RING);
	if (tx_mem == MAP_FAILED) {
		perror("mmap tx_mem");
		goto cleanup;
	}

	fi_mem = mmap(NULL, offs.fr.desc + ring_size * sizeof(__u64),
		      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
		      sock_fd, XDP_UMEM_PGOFF_FILL_RING);
	if (fi_mem == MAP_FAILED) {
		perror("mmap fi_mem");
		goto cleanup;
	}

	co_mem = mmap(NULL, offs.cr.desc + ring_size * sizeof(__u64),
		      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
		      sock_fd, XDP_UMEM_PGOFF_COMPLETION_RING);
	if (co_mem == MAP_FAILED) {
		perror("mmap co_mem");
		goto cleanup;
	}

#if 0
	__u32 *rx_ring_consumer = rx_mem + offs.rx.consumer;
	__u32 *tx_ring_consumer = tx_mem + offs.tx.consumer;
	__u32 *fr_ring_consumer = fi_mem + offs.fr.consumer;
	__u32 *cr_ring_consumer = co_mem + offs.cr.consumer;
	__u32 *rx_ring_producer = rx_mem + offs.rx.producer;
	__u32 *tx_ring_producer = tx_mem + offs.tx.producer;
	__u32 *fr_ring_producer = fi_mem + offs.fr.producer;
	__u32 *cr_ring_producer = co_mem + offs.cr.producer;

	struct xdp_desc *rx_ring = rx_mem + offs.rx.desc;
	struct xdp_desc *tx_ring = tx_mem + offs.tx.desc;
	struct xdp_desc *fr_ring = fi_mem + offs.fr.desc;
	struct xdp_desc *cr_ring = co_mem + offs.cr.desc;
#endif
#if 1
	struct sockaddr_xdp sxdp;
	__u32 queue_id = 0;

	memset(&sxdp, 0, sizeof(sxdp));

	sxdp.sxdp_family = AF_XDP;
	sxdp.sxdp_ifindex = ifindex;
	sxdp.sxdp_queue_id = queue_id;
	sxdp.sxdp_shared_umem_fd = sock_fd;
	/**
	 * XDP_USE_NEED_WAKEUP
	 *
	 * When this flag is set, the application using the AF_XDP socket will
	 * only be woken up by the kernel when there are new packets to process
	 * or when there are empty slots available in the transmit (TX) ring.
	 */
	sxdp.sxdp_flags = XDP_USE_NEED_WAKEUP;

	if (bind(sock_fd, (struct sockaddr *)&sxdp, sizeof(sxdp)) < 0) {
		perror("bind");
		goto cleanup;
	}

	err = bpf_map_update_elem(xsk_map_fd, &queue_id, &sock_fd, 0);
	if (err < 0) {
		printf("failed to update run elem, err = %d, xsk map fd %d.\n",
			err, xsk_map_fd);
		goto cleanup;
	}
#endif

	err = tl_bpf_xdp_attach(ifindex, prog_fd, XDP_FLAGS_SKB_MODE);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

#else
# error "Must define XDP_BASIC, XDP_DEVMAP, XDP_CPUMAP, XDP_XSKMAP"
#endif

#if defined(XDP_XSKMAP) && 1
# if 1
	struct pollfd fds[1] = {};

	fds[0].fd = sock_fd;
	fds[0].events = POLLIN; /* POLLOUT ? */

	while (1) {
		kick_rx(sock_fd);
		err = poll(fds, 1, -1);
		if (err <= 0) {
			fprintf(stderr, "Failed poll xsk fd.\n");
			continue;
		}
		printf("Received packet, ret = %d, %m\n", err);
		/**
		 * TODO: Drop/l2fwd
		 */
	}
/* xsk could not use recvmsg(2) */
# elif 0
	struct iovec iov;
	struct xdp_desc desc;
	struct msghdr msg = {};

	iov.iov_base = ((char *)umem) + offs.rx.desc;
	iov.iov_len = sizeof(desc);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	while (1) {
		/**
		 * Operation not supported
		 * see xsk_proto_ops.sendmsg = xsk_sendmsg()
		 */
		int ret = recvmsg(sock_fd, &msg, 0);
		if (ret < 0) {
			fprintf(stderr, "recvmsg: %s\n", strerror(errno));
			continue;
		}

		struct ethhdr *eth = (struct ethhdr *)((char *)umem + desc.addr);
		struct iphdr *ip = (struct iphdr *)(eth + 1);
		struct udphdr *udp = (struct udphdr *)(ip + 1);

		printf("Received packet: src_ip=%d, dst_ip=%d\n", ip->saddr, ip->daddr);
	}
# endif
#else
	/* Process events */
	read_trace_pipe();
#endif

cleanup:
	printf("Detach xdp from interface %s\n", interface);
	tl_bpf_xdp_detach(ifindex, xdp_flags);
#if defined(XDP_DEVMAP)
	printf("Detach xdp from out interface %s\n", out_interface);
	tl_bpf_xdp_detach(o_ifindex, xdp_flags);
#elif defined(XDP_XSKMAP)
	printf("Close AF_XDP %d\n", sock_fd);
	// TODO: munmap
	close(sock_fd);
#endif
	_bpf__destroy(skel);
	return 0;
}
