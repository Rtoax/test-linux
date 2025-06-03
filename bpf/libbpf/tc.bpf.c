/**
 * BPF_PROG_TYPE_SCHED_CLS, BPF_PROG_TYPE_SCHED_ACT
 *
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
 *
 * BPF_PROG_TYPE_SCHED_ACT
 *
 * BPF_PROG_TYPE_SCHED_CLS can be used to classify packets in various ways,
 * such as filtering or marking packets for specific handling.
 * BPF_PROG_TYPE_SCHED_ACT can perform actions on packets, such as modifying
 * packet contents, redirecting packets, or dropping packets altogether.
 */
#include <vmlinux.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define TC_ACT_OK 0
#define ETH_P_IP  0x0800 /* Internet Protocol packet */

#if defined(TEST_SPIN_LOCK)
#include "spin_lock.h"

struct {
	/**
	 * bpf_spin_lock objects are only allowed inside maps of types
	 * BPF_MAP_TYPE_HASH and BPF_MAP_TYPE_ARRAY (this list could be
	 * extended in the future).
	 */
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct spin_lock_hmap_elem);
} spin_lock_hash_map SEC(".maps");

#elif defined(TEST_RBTREE)
#include "spin_lock.h"

#include "btf_helpers.h"
/**
 * see linux:tools/testing/selftests/bpf/progs/rbtree.c
 */
#define private(name) SEC(".data." #name) __hidden __attribute__((aligned(8)))
#define __contains(name, node) __attribute__((btf_decl_tag("contains:" #name ":" #node)))
#define bpf_rbtree_add(head, node, less) bpf_rbtree_add_impl(head, node, less, NULL, 0)
struct node_data {
	long key;
	long data;
	struct bpf_rb_node node;
};

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct spin_lock_hmap_elem);
} spin_lock_hash_map SEC(".maps");

private(A) struct bpf_spin_lock glock;
/**
 * linux commit 9c395c1b99bd ("bpf: Add basic bpf_rb_{root,node} support")
 * v6.2-rc7-1571-g9c395c1b99bd add bpf_rb_root to uapi/linux/bpf.h
 */
private(A) struct bpf_rb_root groot __contains(node_data, node);

long less_callback_ran = -1;

static bool less(struct bpf_rb_node *a, const struct bpf_rb_node *b)
{
	struct node_data *node_a;
	struct node_data *node_b;

	node_a = container_of(a, struct node_data, node);
	node_b = container_of(b, struct node_data, node);
	less_callback_ran = 1;

	return node_a->key < node_b->key;
}
#endif /* TEST_RBTREE */

#ifdef TEST_SCHED_ACT
SEC("action")
#else
# if LIBBPF_MAJOR_VERSION == 1 && LIBBPF_MINOR_VERSION < 3
/**
 * same: SEC("classifier"), SEC("action"), SEC("tc") deprecated
 * see libbpf commit bb5d7c1be835 ("libbpf: Add opts-based attach/detach/query API for tcx")
 * https://github.com/libbpf/libbpf
 */
SEC("tc")
# else
/**
 * SEC("tc/ingress"), SEC("tc/egress") alias
 * SEC("tcx/ingress"), SEC("tcx/egress")
 */
SEC("tcx/ingress")
# endif
#endif
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

#if defined(TEST_SPIN_LOCK)
	struct spin_lock_hmap_elem *val;
	int key = 0;

	val = bpf_map_lookup_elem(&spin_lock_hash_map, &key);
	if (!val)
		return 1;

	bpf_spin_lock(&val->lock);
	bpf_spin_unlock(&val->lock);
	bpf_printk("test spin lock");

#elif defined(TEST_RBTREE)
	struct node_data n1, n2, *o;
	struct bpf_rb_node *res = NULL;
	struct spin_lock_hmap_elem *val;
	int key = 0;

	val = bpf_map_lookup_elem(&spin_lock_hash_map, &key);
	if (!val)
		return 1;

	n1.key = 1;
	n2.key = 2;

	bpf_spin_lock(&val->lock);
	bpf_rbtree_add(&groot, &n1.node, less);
	bpf_rbtree_add(&groot, &n2.node, less);

	res = bpf_rbtree_first(&groot);
	if (!res) {
		bpf_printk("Failed to call bpf_rbtree_first.");
		bpf_spin_unlock(&val->lock);
		return 2;
	}

	o = container_of(res, struct node_data, node);
	bpf_printk("First rbtree key is %d", o->key);

	res = bpf_rbtree_remove(&groot, &o->node);

	bpf_spin_unlock(&val->lock);

#endif /* TEST_RBTREE */

	return TC_ACT_OK;
}

char __license[] SEC("license") = "GPL";
