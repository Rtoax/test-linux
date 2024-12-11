#include <vmlinux.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define TC_ACT_OK 0
#define ETH_P_IP  0x0800 /* Internet Protocol packet	*/

/**
 * Same as SEC("classifier")
 */
SEC("tc")
int tc_ingress(struct __sk_buff *ctx)
{
	void *data_end = (void *)(__u64)ctx->data_end;
	void *data = (void *)(__u64)ctx->data;
	struct ethhdr *ethhdr;
	struct iphdr *iphdr;

	if (ctx->protocol != bpf_htons(ETH_P_IP))
		return TC_ACT_OK;

	ethhdr = data;
	if ((void *)(ethhdr + 1) > data_end)
		return TC_ACT_OK;

	iphdr = (struct iphdr *)(ethhdr + 1);
	if ((void *)(iphdr + 1) > data_end)
		return TC_ACT_OK;

	bpf_printk("Got IP packet: tot_len: %d, ttl: %d", bpf_ntohs(iphdr->tot_len), iphdr->ttl);
	return TC_ACT_OK;
}

char __license[] SEC("license") = "GPL";
