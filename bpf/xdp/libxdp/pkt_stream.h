// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. */
#pragma once
#include <stdbool.h>
#include "libxdp_helpers.h"

struct pkt {
	__u64 addr;
	__u32 len;
	__u32 payload;
	bool valid;
};

struct pkt_stream {
	__u32 nb_pkts;
	__u32 rx_pkt_nb;
	struct pkt *pkts;
	bool use_addr_for_fill;
};

void pkt_stream_reset(struct pkt_stream *pkt_stream);
struct pkt *pkt_stream_get_pkt(struct pkt_stream *pkt_stream, __u32 pkt_nb);
struct pkt *pkt_stream_get_next_rx_pkt(struct pkt_stream *pkt_stream,
				       __u32 *pkts_sent);
void pkt_stream_delete(struct pkt_stream *pkt_stream);
struct pkt_stream *__pkt_stream_alloc(__u32 nb_pkts);
void pkt_set(struct xsk_umem_info *umem, struct pkt *pkt, __u64 addr, __u32 len);
struct pkt_stream *pkt_stream_generate(struct xsk_umem_info *umem,
				       __u32 nb_pkts, __u32 pkt_len);
struct pkt_stream *pkt_stream_clone(struct xsk_umem_info *umem,
				    struct pkt_stream *pkt_stream);
