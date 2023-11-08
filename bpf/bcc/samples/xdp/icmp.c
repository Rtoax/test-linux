#include <bcc/proto.h>
#include <linux/bpf.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/pkt_cls.h>
#include <uapi/linux/bpf.h>

static __always_inline unsigned short
is_icmp_ping_request(void *data, void *data_end)
{
	struct ethhdr *eth = data;
	if (data + sizeof(struct ethhdr) > data_end)
		return 0;

	if (bpf_ntohs(eth->h_proto) != ETH_P_IP)
		return 0;

	struct iphdr *iph = data + sizeof(struct ethhdr);
	if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end)
		return 0;

	if (iph->protocol != 0x01)
		// We're only interested in ICMP packets
		return 0;

	struct icmphdr *icmp = data + sizeof(struct ethhdr) + sizeof(struct iphdr);
	if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) +
					sizeof(struct icmphdr) >
			data_end)
		return 0;

	return (icmp->type == 8);
}

int xdp_icmp(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;

	if (is_icmp_ping_request(data, data_end)) {
		struct iphdr *iph = data + sizeof(struct ethhdr);
		struct icmphdr *icmp = data + sizeof(struct ethhdr) + sizeof(struct iphdr);
		bpf_trace_printk("[xdp] ICMP request for %x type %x\n", iph->daddr, icmp->type);
	}

	return XDP_PASS;
}

int tc(struct __sk_buff *skb)
{
	bpf_trace_printk("[tc] ingress got packet\n");

	void *data = (void *)(long)skb->data;
	void *data_end = (void *)(long)skb->data_end;

	if (is_icmp_ping_request(data, data_end)) {
		struct iphdr *iph = data + sizeof(struct ethhdr);
		struct icmphdr *icmp = data + sizeof(struct ethhdr) + sizeof(struct iphdr);
		bpf_trace_printk("[tc] ICMP request for %x type %x\n", iph->daddr, icmp->type);
		return TC_ACT_SHOT;
	}
	return TC_ACT_OK;
}

int tc_drop(struct __sk_buff *skb)
{
	bpf_trace_printk("[tc] dropping packet\n");
	return TC_ACT_SHOT;
}
