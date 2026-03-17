#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

/**
 * libbpf: https://github.com/libbpf/libbpf
 * commit d8454ba8ad83("libbpf: remove most other deprecated high-level APIs")
 * remove struct bpf_map_def {}
 */
struct bpf_map_def {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(long));
	__uint(max_entries, 2);
	__uint(map_flags, 0);
/**
 * https://github.com/libbpf/libbpf/wiki/Libbpf:-the-road-to-v1.0#drop-support-for-legacy-bpf-map-declaration-syntax
 */
} cnt SEC(".maps");

SEC("xdp_count")
int xdp_count_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	__u32 ipv6_key = 0;
	__u32 ipv4_key = 1;
	long *value;
	__u16 h_proto;
	// This check is necessary to pass verification
	struct ethhdr *eth = data;

	if (data + sizeof(struct ethhdr) > data_end)
		return XDP_DROP;

	h_proto = eth->h_proto;
	// Check if IPv6 packet
	if (h_proto == htons(ETH_P_IPV6)) {
		value = bpf_map_lookup_elem(&cnt, &ipv6_key);
		if (value)
			*value += 1;
		return XDP_PASS;
	}
	value = bpf_map_lookup_elem(&cnt, &ipv4_key);
	if (value)
		*value += 1;
	return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
