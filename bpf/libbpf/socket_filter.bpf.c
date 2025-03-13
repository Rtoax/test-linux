/**
 * BPF_PROG_TYPE_SOCKET_FILTER
 *
 * Socket filter programs can hook into network sockets and are designed to
 * filter or modify packets received by that socket (the program isn't called
 * for egress/outgoing packets).
 *
 * A noticeable use-case for this program type is "tcpdump" which uses a raw
 * sockets in combination with a socket filter generated from the filter
 * query to efficiently filter packets and only pay the kernel-userspace
 * barrier cost for packets of interest.
 *
 * Socket filters pre-date eBPF itself, socket filters were the first ever
 * prototype in the original BPF implementation, now referred to as cBPF
 * (classic BPF). In fact, usage of this program type was the reason for
 * inventing the whole system.
 *
 * Refs:
 * - https://www.tcpdump.org/papers/bpf-usenix93.pdf
 * - https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_SOCKET_FILTER/
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>
#include "socket_filter.h"
#include "bpf_misc.h"


#define ETH_HLEN	14	/* Total octets in header. */
#define ETH_P_IP	0x0800	/* Internet Protocol packet	*/

struct {
	/**
	 * BPF_MAP_TYPE_RINGBUF
	 *
	 * The ring-buffer map can be used to efficiently send large amounts
	 * of data from eBPF programs to userspace. Data is sent in a queue
	 * / first-in-first-out (FIFO) manner.
	 *
	 * Since this map type does not have key-value pairs, and the
	 * communicated samples can be of any size, the key_size and value_size
	 * attributes have to both be set to 0.
	 *
	 * The max_entries attribute is used to specify the size of the
	 * ring-buffer in bytes. It must be a power of 2 and a multiple of the
	 * page size (typically 4096), so 4096, 8192, 16384, 32768, ect.
	 *
	 * v5.7-rc7-2894-g457f44363a88
	 * kernel commit 457f44363a88 ("bpf: Implement BPF ring buffer and
	 * verifier support for it")
	 */
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 256 * 1024);
} ring_buf SEC(".maps");

struct {
#if defined(MAP_PERCPU_ARRAY)
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
#elif defined(MAP_ARRAY)
	/**
	 * BPF_MAP_TYPE_ARRAY
	 *
	 * The array map type is a generic map type with no restrictions on the
	 * structure of the value. Like a normal array, the array map has a
	 * numeric key starting at 0 and incrementing.
	 */
	__uint(type, BPF_MAP_TYPE_ARRAY);
#else
# error "Must define MAP_PERCPU_ARRAY or MAP_ARRAY"
#endif
	__type(key, u32);
	__type(value, long);
	__uint(max_entries, 256);
} proto_cnt SEC(".maps");

/**
 * SEC("socketxxxx") will be parse as BPF_PROG_TYPE_SOCKET_FILTER
 *
 * Set bpf prog type with bpf_program__set_type()
 */
#if defined(STRICT_SEC_NAME)
SEC("socket")
#else
SEC("socket0")
#endif
int bpf_prog1(struct __sk_buff *skb)
{
	struct so_event *e;
	__u8 verlen;
	__u16 proto;
	__u32 nhoff = ETH_HLEN;
	long *value;
	int index;

	bpf_skb_load_bytes(skb, 12, &proto, 2);
	proto = __bpf_ntohs(proto);
	if (proto != ETH_P_IP)
		return 0;

#define RESERVE_SUBMIT 1

#if defined(RESERVE_SUBMIT)
	e = bpf_ringbuf_reserve(&ring_buf, sizeof(*e), 0);
	if (!e)
		return 0;
#else
	static struct so_event event = {};
	e = &event;
#endif

	bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, protocol), &e->ip_proto, 1);
	if (e->ip_proto != IPPROTO_GRE) {
		bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, saddr), &(e->src_addr), 4);
		bpf_skb_load_bytes(skb, nhoff + offsetof(struct iphdr, daddr), &(e->dst_addr), 4);
	}

	index = e->ip_proto;
	value = bpf_map_lookup_elem(&proto_cnt, &index);
	if (value)
		__sync_fetch_and_add(value, 1);

	bpf_skb_load_bytes(skb, nhoff + 0, &verlen, 1);
	bpf_skb_load_bytes(skb, nhoff + ((verlen & 0xF) << 2), &(e->ports), 4);
	e->pkt_type = skb->pkt_type;
	e->ifindex = skb->ifindex;

#if defined(RESERVE_SUBMIT)
	bpf_ringbuf_submit(e, 0);
	/**
	 * void bpf_ringbuf_discard(void *data, __u64 flags);
	 *
	 * Discard reserved ring buffer sample, pointed to by data.
	 *
	 * - If BPF_RB_NO_WAKEUP is specified in flags, no notification of new
	 *   data availability is sent.
	 * - If BPF_RB_FORCE_WAKEUP is specified in flags, notification of new
	 *   data availability is sent unconditionally.
	 * - If 0 is specified in flags, an adaptive notification of new data
	 *   availability is sent.
	 */
#else
	bpf_ringbuf_output(&ring_buf, e, sizeof(*e), 0);
#endif

	return skb->len;
}

char __license[] SEC("license") = "GPL";
