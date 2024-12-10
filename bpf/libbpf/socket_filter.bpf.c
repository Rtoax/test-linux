#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>
#include "socket_filter.h"

#define ETH_HLEN	14	/* Total octets in header. */
#define ETH_P_IP	0x0800	/* Internet Protocol packet	*/

struct {
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 256 * 1024);
} ring_buf SEC(".maps");

/* SEC("socketxxxx") will be parse as BPF_PROG_TYPE_SOCKET_FILTER */
SEC("socket")
int bpf_prog1(struct __sk_buff *skb)
{
	struct so_event *e;
	__u8 verlen;
	__u16 proto;
	__u32 nhoff = ETH_HLEN;

	bpf_skb_load_bytes(skb, 12, &proto, 2);
	proto = __bpf_ntohs(proto);
	if (proto != ETH_P_IP)
		return 0;

	e = bpf_ringbuf_reserve(&ring_buf, sizeof(*e), 0);
	if (!e)
		return 0;

	bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, protocol), &e->ip_proto, 1);
	if (e->ip_proto != IPPROTO_GRE) {
		bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, saddr), &(e->src_addr), 4);
		bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, daddr), &(e->dst_addr), 4);
	}

	bpf_skb_load_bytes(skb, nhoff + 0, &verlen, 1);
	bpf_skb_load_bytes(skb, nhoff + ((verlen & 0xF) << 2), &(e->ports), 4);
	e->pkt_type = skb->pkt_type;
	e->ifindex = skb->ifindex;
	bpf_ringbuf_submit(e, 0);

	return skb->len;
}

char __license[] SEC("license") = "GPL";
