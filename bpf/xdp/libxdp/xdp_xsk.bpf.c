#include <vmlinux.h>
#include <bpf/bpf_helpers.h>

struct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entries, 64);
	__type(key, __u32);
	__type(value, __u32);
} xsk_map SEC(".maps");

SEC("xdp")
int xdp_sock_prog(struct xdp_md *ctx)
{
	__u32 key = 0;
	void *sock;

	/* Redirect the packet to the XSK socket */
	sock = bpf_map_lookup_elem(&xsk_map, &key);
	if (sock) {
		return bpf_redirect_map(&xsk_map, key, XDP_PASS);
	}

	return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
