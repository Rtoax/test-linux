// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. */
/**
 * see Linux tools/testing/selftests/bpf/xskxceiver.c
 */
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include "pkt_stream.h"

void pkt_stream_reset(struct pkt_stream *pkt_stream)
{
	if (pkt_stream)
		pkt_stream->rx_pkt_nb = 0;
}

struct pkt *pkt_stream_get_pkt(struct pkt_stream *pkt_stream, __u32 pkt_nb)
{
	if (pkt_nb >= pkt_stream->nb_pkts)
		return NULL;

	return &pkt_stream->pkts[pkt_nb];
}

struct pkt *pkt_stream_get_next_rx_pkt(struct pkt_stream *pkt_stream,
				       __u32 *pkts_sent)
{
	while (pkt_stream->rx_pkt_nb < pkt_stream->nb_pkts) {
		(*pkts_sent)++;
		if (pkt_stream->pkts[pkt_stream->rx_pkt_nb].valid)
			return &pkt_stream->pkts[pkt_stream->rx_pkt_nb++];
		pkt_stream->rx_pkt_nb++;
	}
	return NULL;
}

void pkt_stream_delete(struct pkt_stream *pkt_stream)
{
	free(pkt_stream->pkts);
	free(pkt_stream);
}

struct pkt_stream *__pkt_stream_alloc(__u32 nb_pkts)
{
	struct pkt_stream *pkt_stream;

	pkt_stream = calloc(1, sizeof(*pkt_stream));
	if (!pkt_stream)
		return NULL;

	pkt_stream->pkts = calloc(nb_pkts, sizeof(*pkt_stream->pkts));
	if (!pkt_stream->pkts) {
		free(pkt_stream);
		return NULL;
	}

	pkt_stream->nb_pkts = nb_pkts;
	return pkt_stream;
}

void pkt_set(struct xsk_umem_info *umem, struct pkt *pkt, __u64 addr, __u32 len)
{
	pkt->addr = addr + umem->base_addr;
	pkt->len = len;
	if (len > umem->frame_size - XDP_PACKET_HEADROOM - MIN_PKT_SIZE * 2 - umem->frame_headroom)
		pkt->valid = false;
	else
		pkt->valid = true;
}

struct pkt_stream *pkt_stream_generate(struct xsk_umem_info *umem,
				       __u32 nb_pkts, __u32 pkt_len)
{
	struct pkt_stream *pkt_stream;
	__u32 i;

	pkt_stream = __pkt_stream_alloc(nb_pkts);
	if (!pkt_stream) {
		errno = ENOMEM;
		fprintf(stderr, "alloc pkt_stream failed, %m\n");
		return NULL;
	}

	pkt_stream->nb_pkts = nb_pkts;
	for (i = 0; i < nb_pkts; i++) {
		pkt_set(umem, &pkt_stream->pkts[i], (i % umem->num_frames) * umem->frame_size,
			pkt_len);
		pkt_stream->pkts[i].payload = i;
	}

	return pkt_stream;
}

struct pkt_stream *pkt_stream_clone(struct xsk_umem_info *umem,
				    struct pkt_stream *pkt_stream)
{
	return pkt_stream_generate(umem, pkt_stream->nb_pkts, pkt_stream->pkts[0].len);
}

/**
 * TODO: More APIs
 */
