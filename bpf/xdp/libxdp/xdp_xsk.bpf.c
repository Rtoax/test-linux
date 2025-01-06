#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>

#define ETH_P_IP	0x0800

struct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entries, 64);
	__type(key, __u32);
	__type(value, __u32);
} xsk_map SEC(".maps");

SEC("xdp")
int xdp_sock_prog(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	__u32 index = ctx->rx_queue_index;

	struct ethhdr *ethhdr = data;

	if ((void *)(ethhdr + 1) > data_end)
		return XDP_PASS;

	/**
	 * Only handle IP packets.
	 */
	if (bpf_ntohs(ethhdr->h_proto) != ETH_P_IP)
		return XDP_PASS;

	bpf_printk("(ip) xdp ingress %d, rx queue %d, len %ld",
		   ctx->ingress_ifindex, index,
		   (u64)(ctx->data_end - ctx->data));

	/* Redirect the packet to the XSK socket */
	if (bpf_map_lookup_elem(&xsk_map, &index))
		return bpf_redirect_map(&xsk_map, index, XDP_PASS);

	return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
