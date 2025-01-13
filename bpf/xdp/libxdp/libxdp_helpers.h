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

#ifndef MAX
#define MAX(a, b) ((a > b) ? a : b)
#endif

#define DEFAULT_PKT_CNT MAX(XSK_RING_CONS__DEFAULT_NUM_DESCS, XSK_RING_PROD__DEFAULT_NUM_DESCS)
/**
 * rx+fill and tx+complete have buffer_size buffer.
 */
#define DEFAULT_UMEM_BUFFERS (DEFAULT_PKT_CNT * 2)
#define UMEM_SIZE (DEFAULT_UMEM_BUFFERS * XSK_UMEM__DEFAULT_FRAME_SIZE)

struct xsk_umem_info {
	struct xsk_ring_prod fq;
	struct xsk_ring_cons cq;
	struct xsk_umem *umem;
	__u32 fill_size;
	__u32 comp_size;
	void *buffer;
	size_t buffer_size;
	__u32 num_frames;
	__u32 frame_size;
	__u32 frame_headroom;
	__u32 base_addr;
};

struct xsk_socket_info {
	struct xsk_socket *xsk;
	struct xsk_ring_cons rx;
	struct xsk_ring_prod tx;
	__u32 rx_size;
	__u32 tx_size;
	int queue_id;
	int bind_flags;
	struct xsk_umem_info *umem;
};

const char *strxdpaction(int action);

int kick_rx(int xdp_fd);
void kick_tx(int xdp_fd);
void display_xsk_ring(const char *pfx, void *ring);
void display_xsk_umem_config(const char *pfx, struct xsk_umem_config *uc);
void display_xsk_umem(const char *pfx, struct xsk_umem *umem);
void display_xdp_ring_offset(const char *pfx, struct xdp_ring_offset *off);
void display_xdp_mmap_offsets(const char *pfx, struct xdp_mmap_offsets *offs);
int xsk_get_mmap_offsets(int fd, struct xdp_mmap_offsets *off);
