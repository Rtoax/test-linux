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
#include <bpf/bpf_core_read.h>
#include "bpf_experimental.h"

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
/**
 * linux commit 9c395c1b99bd ("bpf: Add basic bpf_rb_{root,node} support")
 * v6.2-rc7-1571-g9c395c1b99bd add bpf_rb_root to uapi/linux/bpf.h
 */
#include "spin_lock.h"
#include "rbtree.h"

#include "btf_helpers.h"

struct node_data {
	long key;
	long data;
	struct bpf_rb_node node;
};

# if defined(TEST_RBTREE_RAW_MAP)
struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct spin_lock_hmap_elem);
} spin_lock_hash_map SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__uint(max_entries, 1);
	__type(key, int);
	__type(value, struct rbtree_root);
} rbtree_root_map SEC(".maps");

# else /* TEST_RBTREE_RAW_MAP */
/**
 * see linux:tools/testing/selftests/bpf/progs/rbtree.c
 */
#define private(name) SEC(".data." #name) __hidden __attribute__((aligned(8)))
private(A) struct bpf_spin_lock glock;
private(A) struct bpf_rb_root groot __contains(node_data, node);
# endif /* TEST_RBTREE_RAW_MAP */

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
	char *str = "";

	val = bpf_map_lookup_elem(&spin_lock_hash_map, &key);
	if (!val)
		return 1;

	bpf_spin_lock(&val->lock);
	str = "HELLO";
	bpf_spin_unlock(&val->lock);
	bpf_printk("test spin lock, %s", str);

#elif defined(TEST_RBTREE)
	struct bpf_rb_node *res = NULL;
	struct bpf_spin_lock *spinlock;
	struct bpf_rb_root *rbroot;

# if defined(TEST_RBTREE_RAW_MAP)
	int key = 0;
	struct spin_lock_hmap_elem *lock;
	struct rbtree_root *root;

	lock = bpf_map_lookup_elem(&spin_lock_hash_map, &key);
	if (!lock)
		return 1;
	spinlock = &lock->lock;

	root = bpf_map_lookup_elem(&rbtree_root_map, &key);
	if (!root)
		return 1;
	rbroot = &root->root;

#else /* TEST_RBTREE_RAW_MAP */

	spinlock = &glock;
	rbroot = &groot;
#endif
	struct node_data *n, *m;

	n = bpf_obj_new(typeof(*n));
	if (!n)
		return 1;
	n->key = 1;

	m = bpf_obj_new(typeof(*m));
	if (!m) {
		bpf_obj_drop(n);
		return 2;
	}
	m->key = 1;

	bpf_spin_lock(spinlock);
	bpf_rbtree_add(rbroot, &n->node, less);
	bpf_rbtree_add(rbroot, &m->node, less);
	bpf_spin_unlock(spinlock);

	n = bpf_obj_new(typeof(*n));
	if (!n)
		return 3;
	n->key = 3;

	bpf_spin_lock(spinlock);
	bpf_rbtree_add(rbroot, &n->node, less);
	bpf_spin_unlock(spinlock);

	bpf_printk("test rbtree");

#endif /* TEST_RBTREE */

	return TC_ACT_OK;
}

char __license[] SEC("license") = "GPL";
