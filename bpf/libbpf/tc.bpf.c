/**
 * BPF_PROG_TYPE_SCHED_CLS
 *
 * This program type allows for the implementation of a Traffic Control (TC)
 * classifier (aka filter) in eBPF. TC can be used for a number of use cases,
 * all of them having to do with the manipulation of traffic. TC is for example
 * used to implement QoS (Quality of Service) allowing latency sensitive
 * traffic like VoIP (Voice over IP) to be processed ahead of lets say web
 * traffic. It can also drop packets to simulate packet-loss, add latency to
 * simulate distant clients or apply bandwidth limitations for applications
 * or users, to name a few.
 *
 * TC allows an admin to filter traffic using a hierarchical model of qdiscs
 * (Queuing DISCipline). A root qdisc is attached to a network interface with
 * certain actions. This qdisc can also have child qdiscs which will be used
 * over the root if their filter matches the traffic. This program type allows
 * us to implement such a filter in eBPF.
 *
 * Direct action:
 *
 * TC_ACT_UNSPEC (-1) - Signals that the default configured action should be
 *                      taken.
 * TC_ACT_OK (0) - Signals that the packet should proceed.
 * TC_ACT_RECLASSIFY (1) - Signals that the packet has to re-start
 *                         classification from the root qdisc. This is
 *                         typically used after modifying the packet so its
 *                         classification might have different results.
 * TC_ACT_SHOT (2) - Signals that the packet should be dropped, no other TC
 *                   processing should happen.
 * TC_ACT_PIPE (3) - While defined, this action should not be used and holds
 *                   no particular meaning for eBPF classifiers.
 * TC_ACT_STOLEN (4) - While defined, this action should not be used and holds
 *                     no particular meaning for eBPF classifiers.
 * TC_ACT_QUEUED (5) - While defined, this action should not be used and holds
 *                     no particular meaning for eBPF classifiers.
 * TC_ACT_REPEAT (6) - While defined, this action should not be used and holds
 *                     no particular meaning for eBPF classifiers.
 * TC_ACT_REDIRECT (7) - Signals that the packet should be redirected, the
 *                       details of how and where to are set as side effects
 *                       by helpers functions.
 */
#include <vmlinux.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define TC_ACT_OK 0
#define ETH_P_IP  0x0800 /* Internet Protocol packet */

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
