/**
 * Usage:
 * $ sudo ip link set dev lo xdp obj tcpdump.bpf.o
 * $ sudo ip link set dev lo xdp off
 * $ sudo cat /sys/kernel/tracing/trace_pipe
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

#define ETH_P_IP        0x0800

/**
 * sudo tcpdump -d ip and tcp port 80
 */
SEC("prog")
int xdp_tcpdump_prog(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;

	struct ethhdr *ethhdr = data;
	struct iphdr *iphdr;
	struct tcphdr *tcphdr;

	if ((void *)(ethhdr + 1) > data_end)
		return XDP_PASS;

	if (bpf_ntohs(ethhdr->h_proto) == ETH_P_IP) {
		iphdr = (void *)(ethhdr + 1);

		if ((void *)(iphdr + 1) > data_end)
			return XDP_PASS;

		if (iphdr->protocol == IPPROTO_TCP) {
			if (bpf_ntohs(iphdr->frag_off) & 0x1fff)
				goto exit;

			tcphdr = (void *)(iphdr + 1);

			if ((void *)(tcphdr + 1) > data_end)
				return XDP_PASS;

			if (bpf_ntohs(tcphdr->source) != 80 && bpf_ntohs(tcphdr->dest) != 80)
				goto exit;

			bpf_printk("Get IP->TCP->Port80");

			/* tcpdump return 0x40000, see libcap,tcpdump source code */
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

char __license[] SEC("license") = "GPL";
