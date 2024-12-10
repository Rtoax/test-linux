#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define TC_ACT_OK 0

/**
 * Same as SEC("classifier")
 */
SEC("tc")
int tc_1(struct __sk_buff *ctx)
{
	bpf_printk("Got sk");
	return TC_ACT_OK;
}

char __license[] SEC("license") = "GPL";
