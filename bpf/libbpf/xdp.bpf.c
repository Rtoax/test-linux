/**
 * BPF_PROG_TYPE_XDP
 *
 * XDP (Express Data Path) programs can attach to network devices and are
 * called for every incoming (ingress) packet received by that network device.
 * XDP programs can take quite a large number of actions, most prominent of
 * which are manipulation of the packet, dropping the packet, redirecting it
 * and letting it pass to the network stack.
 *
 * Notable use cases for XDP programs are for DDoS protection, Load Balancing,
 * and high-throughput packet filtering. If loaded with native driver support,
 * XDP programs will be called just after receiving the packet but before
 * allocating memory for a socket buffer. This call site makes XDP programs
 * extremely performant, especially in use cases where traffic is forwarded or
 * dropped a lot in comparison to other eBPF program types or techniques which
 * run after the relatively expensive socket buffer allocation process has
 * taken place, only to discard it.
 */
#include <vmlinux.h>
#include <linux/version.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>

#define ETH_P_IP	0x0800

#if defined(XDP_BASIC) /* Test basic */

#if defined(STRICT_SEC_NAME)
SEC("xdp")
#endif
int xdp_dummy_prog(struct xdp_md *ctx)
{
	return XDP_PASS;
}

#if defined(STRICT_SEC_NAME)
SEC("xdp")
#endif
int xdp_printk(struct xdp_md *ctx)
{
	int proto = 0;
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *ethhdr = data;
	static unsigned long icmp_count = 0;

	if (data + sizeof(struct ethhdr) > data_end) {
		bpf_printk("Not ether header");
		return XDP_PASS;
	}

	if (bpf_ntohs(ethhdr->h_proto) == ETH_P_IP) {
		struct iphdr *iphdr = data + sizeof(struct ethhdr);
		if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) <= data_end)
			proto = iphdr->protocol;
	}

	/**
	 * Only access to ingress_ifindex, egress_ifindex access deny, see
	 * 'xdp/devmap'.
	 */
	bpf_printk("xdp ingress %d", ctx->ingress_ifindex);

	switch (proto) {
	case IPPROTO_ICMP: /* 1 */
		bpf_printk("Hello icmp %ld", icmp_count++);
		if (icmp_count % 2)
			return XDP_DROP;
		break;
	case IPPROTO_TCP: /* 6 */
		bpf_printk("Hello tcp");
		break;
	case IPPROTO_UDP: /* 17 */
		bpf_printk("Hello udp");
		break;
	}
	return XDP_PASS;
}

#elif defined(XDP_DEVMAP) /* Test devmap */

/**
 * see bcc examples/networking/xdp/xdp_redirect_map.py
 */
static inline void swap_src_dst_mac(void *data)
{
	unsigned short *p = data;
	unsigned short dst[3];
	dst[0] = p[0];
	dst[1] = p[1];
	dst[2] = p[2];
	p[0] = p[3];
	p[1] = p[4];
	p[2] = p[5];
	p[3] = dst[0];
	p[4] = dst[1];
	p[5] = dst[2];
}

/**
 * The packet can be redirected to egress on a different interface than where
 * it entered (like XDP_TX but for a different interface). This can be done
 * using the bpf_redirect helper (not recommended) or the bpf_redirect_map
 * helper in combination with a BPF_MAP_TYPE_DEVMAP or BPF_MAP_TYPE_DEVMAP_HASH
 * map.
 */
struct {
	/**
	 * BPF_MAP_TYPE_DEVMAP
	 *
	 * The device map is a specialized map type which holds references to
	 * network devices.
	 *
	 * This map type is used in combination with the bpf_redirect_map
	 * helper to redirect traffic to egress out of a different device. It
	 * is an array style map, where the indices go from 0 to max_entries-1.
	 * In a later kernel version a hash version of this map was added:
	 * BPF_MAP_TYPE_DEVMAP_HASH.
	 *
	 * see linux commit 6f9d451ab1a3 ("xdp: Add devmap_hash map type for
	 * looking up devices by hashed index") v5.3-rc1-119-g6f9d451ab1a3
	 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 3, 0)
	__uint(type, BPF_MAP_TYPE_DEVMAP_HASH);
#else
	__uint(type, BPF_MAP_TYPE_DEVMAP);
#endif
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(struct bpf_devmap_val));
	__uint(max_entries, 1);
} devmap_ports SEC(".maps");

SEC("xdp")
int xdp_redir_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;

	if (data + sizeof(struct ethhdr) > data_end)
		return XDP_DROP;

	swap_src_dst_mac(data);

	return bpf_redirect_map(&devmap_ports, 0, 0);
}

/**
 * valid program on DEVMAP entry via SEC name;
 * has access to egress and ingress ifindex
 */
#if defined(STRICT_SEC_NAME)
#if (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 7) || (LIBBPF_MAJOR_VERSION >= 1)
/**
 * libbpf commit c245b0eeafcf ("libbpf: Deprecate xdp_cpumap, xdp_devmap and
 * classifier sec definitions") libbpf-0.7 introduce "xdp/devmap".
 */
SEC("xdp/devmap")
#else
/**
 * libbpf commit fcd1b668c6d2 ("libbpf: clean up SEC() handling") libbpf-1.0
 * remove "xdp_devmap" support.
 */
SEC("xdp_devmap/printk")
#endif
#endif
int xdp_devmap_printk(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	unsigned int len = data_end - data;

	bpf_printk("devmap redirect: dev %u -> dev %u len %u",
		   ctx->ingress_ifindex, ctx->egress_ifindex, len);

	return XDP_PASS;
}

#elif defined(XDP_CPUMAP) /* Test cpumap */
/**
 * BPF_MAP_TYPE_CPUMAP
 *
 * The packet can be redirected to another CPU for further processing using the
 * bpf_redirect_map helper in combination with a BPF_MAP_TYPE_CPUMAP map.
 *
 * This feature can for example be used to implement a form of Receive Side
 * Scaling (RSS).
 *
 * The value_size can be 4 or 8 depending on kernel version and optional
 * secondary program support. The key_size must always be 4. The max_entries
 * must be smaller or equal to the amount of logical CPUs on the host.
 */
struct {
	__uint(type, BPF_MAP_TYPE_CPUMAP);
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(struct bpf_cpumap_val));
	__uint(max_entries, 256);
} cpu_map SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uint(max_entries, 1);
} run_on_cpu SEC(".maps");

SEC("xdp")
int xdp_redir_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	unsigned int len = data_end - data;
	u32 key = 0;
	u32 *cpu;

	if (data + sizeof(struct ethhdr) > data_end)
		return XDP_DROP;

	cpu = bpf_map_lookup_elem(&run_on_cpu, &key);
	if (!cpu)
		return XDP_PASS;

	bpf_printk("cpumap redirect: dev %u -> cpu %u len %u",
		   ctx->ingress_ifindex, *cpu, len);

	return bpf_redirect_map(&cpu_map, *cpu, 0);
}

#if defined(STRICT_SEC_NAME)
#if (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 7) || (LIBBPF_MAJOR_VERSION >= 1)
SEC("xdp/cpumap")
#else
SEC("xdp_cpumap/prog1")
#endif
#endif
int xdp_dummy_cpumap(struct xdp_md *ctx)
{
	return XDP_PASS;
}

#elif defined(XDP_XSKMAP) /* Test XSKMAP */

/**
 * BPF_MAP_TYPE_XSKMAP
 *
 * This XDP Socket map is a specialized map which references XDP Sockets.
 *
 * This map type is used in combination with the bpf_redirect_map helper to
 * redirect traffic to userspace, bypassing the kernel network stack. It is
 * an array style map, where the indices go from 0 to max_entries-1. The
 * values of this map are the file descriptor of specially prepared network
 * sockets.
 */
struct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__type(key, __u32);
	__type(value, __u32);
	__uint(max_entries, 4);
} xsks_map SEC(".maps");

SEC("xdp")
int xsk_redir_prog(struct xdp_md *ctx)
{
	__u32 index = ctx->rx_queue_index;

	bpf_printk("rx queue idx = %d", index);

	/**
	 * A set entry here means that the corresponding queue_id has an
	 * active AF_XDP socket bound to it.
	 */
	if (bpf_map_lookup_elem(&xsks_map, &index))
		return bpf_redirect_map(&xsks_map, index, 0);
	return XDP_PASS;
}

#else
# error "Must define XDP_BASIC, XDP_DEVMAP or XDP_CPUMAP"
#endif

char __license[] SEC("license") = "GPL";
