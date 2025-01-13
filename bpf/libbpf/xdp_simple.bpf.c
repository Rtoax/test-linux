#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>


SEC("xdp")
int xdp_dummy_prog(struct xdp_md *ctx)
{
	bpf_printk("xdp tx ingress %d, len %ld", ctx->ingress_ifindex,
		   (u64)(ctx->data_end - ctx->data));
	return XDP_PASS;
}

