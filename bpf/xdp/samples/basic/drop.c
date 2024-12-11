#include <linux/bpf.h>

#ifndef SEC
# define SEC(NAME) __attribute__((section(NAME), used))
#endif

SEC("prog")
int xdp_drop(struct xdp_md *ctx)
{
	return XDP_DROP;
}

char __license[] SEC("license") = "GPL";
