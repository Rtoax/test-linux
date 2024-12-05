#include <bcc/proto.h>
#include <linux/bpf.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/pkt_cls.h>
#include <uapi/linux/bpf.h>

#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP 1
#endif

static __always_inline unsigned short
is_icmp_request(void *data, void *data_end)
{
	struct ethhdr *eth = data;
	struct iphdr *iph;
	struct icmphdr *icmp;

	if (data + sizeof(struct ethhdr) > data_end)
		return 0;

	if (bpf_ntohs(eth->h_proto) != ETH_P_IP)
		return 0;

	iph = data + sizeof(struct ethhdr);
	if ((void *)iph + sizeof(struct iphdr) > data_end)
		return 0;

	/* We're only interested in ICMP packets */
	if (iph->protocol != IPPROTO_ICMP)
		return 0;

	icmp = data + sizeof(struct ethhdr) + sizeof(struct iphdr);
	if ((void *)icmp + sizeof(struct icmphdr) > data_end)
		return 0;

	return (icmp->type == ICMP_ECHO);
}

int xdp_icmp(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;

	if (is_icmp_request(data, data_end)) {
		struct iphdr *iph = data + sizeof(struct ethhdr);
		struct icmphdr *icmp = (void *)iph + sizeof(struct iphdr);
		bpf_trace_printk("[xdp] ICMP request for %x type %x", iph->daddr, icmp->type);
	}

	return XDP_PASS;
}

int tc(struct __sk_buff *skb)
{
	void *data = (void *)(long)skb->data;
	void *data_end = (void *)(long)skb->data_end;

	if (is_icmp_request(data, data_end)) {
		struct iphdr *iph = data + sizeof(struct ethhdr);
		struct icmphdr *icmp = (void *)iph + sizeof(struct iphdr);
		bpf_trace_printk("[tc] ICMP request for %x type %x", iph->daddr, icmp->type);
		return TC_ACT_SHOT;
	}
	return TC_ACT_OK;
}

int tc_drop(struct __sk_buff *skb)
{
	bpf_trace_printk("[tc] dropping packet");
	return TC_ACT_SHOT;
}

static __always_inline void swap_mac_addresses(struct __sk_buff *skb)
{
	unsigned char src_mac[6];
	unsigned char dst_mac[6];
	bpf_skb_load_bytes(skb, offsetof(struct ethhdr, h_source), src_mac, 6);
	bpf_skb_load_bytes(skb, offsetof(struct ethhdr, h_dest), dst_mac, 6);
	bpf_skb_store_bytes(skb, offsetof(struct ethhdr, h_source), dst_mac, 6, 0);
	bpf_skb_store_bytes(skb, offsetof(struct ethhdr, h_dest), src_mac, 6, 0);
}

#define IP_SRC_OFF (ETH_HLEN + offsetof(struct iphdr, saddr))
#define IP_DST_OFF (ETH_HLEN + offsetof(struct iphdr, daddr))

static __always_inline void swap_ip_addresses(struct __sk_buff *skb)
{
	unsigned char src_ip[4];
	unsigned char dst_ip[4];
	bpf_skb_load_bytes(skb, IP_SRC_OFF, src_ip, 4);
	bpf_skb_load_bytes(skb, IP_DST_OFF, dst_ip, 4);
	bpf_skb_store_bytes(skb, IP_SRC_OFF, dst_ip, 4, 0);
	bpf_skb_store_bytes(skb, IP_DST_OFF, src_ip, 4, 0);
}

#define ICMP_CSUM_OFF \
	(ETH_HLEN + sizeof(struct iphdr) + offsetof(struct icmphdr, checksum))
#define ICMP_TYPE_OFF \
	(ETH_HLEN + sizeof(struct iphdr) + offsetof(struct icmphdr, type))

static __always_inline void
update_icmp_type(struct __sk_buff *skb, unsigned char old_type, unsigned char new_type)
{
	bpf_l4_csum_replace(skb, ICMP_CSUM_OFF, old_type, new_type, 2);
	bpf_skb_store_bytes(skb, ICMP_TYPE_OFF, &new_type, sizeof(new_type), 0);
}

int tc_pingpong(struct __sk_buff *skb)
{
	bpf_trace_printk("[tc] ingress got packet");

	void *data = (void *)(long)skb->data;
	void *data_end = (void *)(long)skb->data_end;

	if (!is_icmp_request(data, data_end)) {
		return TC_ACT_OK;
	}

	struct iphdr *iph = data + sizeof(struct ethhdr);
	struct icmphdr *icmp = data + sizeof(struct ethhdr) + sizeof(struct iphdr);
	bpf_trace_printk("[tc] ICMP request for %x type %x", iph->daddr, icmp->type);

	swap_mac_addresses(skb);
	swap_ip_addresses(skb);

	/**
	 * Change the type of the ICMP packet to 0 (ICMP Echo Reply) (was 8
	 * for ICMP Echo request)
	 */
	update_icmp_type(skb, 8, 0);

	/**
	 * Redirecting the modified skb on the same interface to be transmitted
	 * again
	 */
	bpf_clone_redirect(skb, skb->ifindex, 0);

	/**
	 * We modified the packet and redirected a clone of it, so drop this one
	 */
	return TC_ACT_SHOT;
}
