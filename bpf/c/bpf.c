#include <linux/bpf.h>
#include <bpf/libbpf.h>

#ifndef SEC
# define SEC(x)  __attribute__((section(x), used))
#endif

/**
 * See libbpf commit bb5d7c1be835 ("libbpf: Add opts-based attach/detach/query
 * API for tcx")
 */
#if LIBBPF_MAJOR_VERSION == 1 && LIBBPF_MINOR_VERSION >= 3
SEC("tcx/ingress")
#else
SEC("classifier")
#endif
int cls_main(struct __sk_buff *skb)
{
	return -1;
}

char __license[] SEC("license") = "GPL";
