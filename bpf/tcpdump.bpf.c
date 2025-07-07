#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

#define ETH_P_IP        0x0800

/**
 * sudo tcpdump -d ip and tcp port 80
 */
SEC("xdp")
int xdp_tcpdump_prog(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;

	struct ethhdr *ethhdr = data;
	struct iphdr *iphdr;
	struct tcphdr *tcphdr;

	if (ethhdr->h_proto == ETH_P_IP) {
		iphdr = (void *)(ethhdr + 1);

		if ((void *)iphdr > data_end)
			return XDP_PASS;

		if (iphdr->protocol == IPPROTO_TCP) {
			if (iphdr->frag_off & 0x1fff)
				goto exit;

			tcphdr = (void *)(iphdr + 1);

			if ((void *)tcphdr > data_end)
				return XDP_PASS;

			if (tcphdr->source != 80 && tcphdr->dest != 80)
				goto exit;

			/* 0x40000, see libcap,tcpdump source code */
			return XDP_PASS;
		} else {
			goto exit;
		}
	} else {
		goto exit;
	}
exit:
	return XDP_PASS;
}
