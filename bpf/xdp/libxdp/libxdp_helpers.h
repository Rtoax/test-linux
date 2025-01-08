#pragma once
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

#define MIN_ETH_PKT_SIZE 64
#define ETH_FCS_SIZE 4
#define MIN_PKT_SIZE (MIN_ETH_PKT_SIZE - ETH_FCS_SIZE)

#define DEFAULT_PKT_CNT (4 * 1024)
#define DEFAULT_UMEM_BUFFERS (DEFAULT_PKT_CNT / 4)
#define UMEM_SIZE (DEFAULT_UMEM_BUFFERS * XSK_UMEM__DEFAULT_FRAME_SIZE)

struct xsk_umem_info {
	struct xsk_ring_prod fq;
	struct xsk_ring_cons cq;
	struct xsk_umem *umem;
	void *buffer;
	__u32 num_frames;
	__u32 frame_size;
	__u32 frame_headroom;
	__u32 base_addr;
};

struct xsk_socket_info {
	struct xsk_socket *xsk;
	struct xsk_ring_cons rx;
	struct xsk_ring_prod tx;
	struct xsk_umem_info *umem;
};

int kick_rx(int xdp_fd);
void kick_tx(int xdp_fd);
