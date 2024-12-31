#include <vmlinux.h>
#include <bpf/bpf_helpers.h>

SEC("xdp_dummy_prog")
int xdp_dummy_prog(struct xdp_md *ctx)
{
	return XDP_PASS;
}
