#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "xdp_dos.h"
#include "bpf_misc.h"
#include "bpf_debug.h"

#define ETH_P_IP	0x0800

typedef struct {
	uint8_t type; // Type of message (e.g. echo request)
	uint8_t code; // Code of message (e.g. echo reply)
	uint16_t checksum; // Checksum of the packet
	uint8_t id; // Identifier of the packet
	uint8_t seq; // Sequence number of the packet
	uint8_t ak_prio; // Custom AK-Prio field (0 for high priority, 1 for low priority)
	char data[28]; // Data payload (optional)
} icmp_packet_t;

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, u32);
	__type(value, struct user_config);
} map_config SEC(".maps");

/**
 * Use to record all packets from network
 */
struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 4096);
	__type(key, struct ipv4_key_t);
	__type(value, struct ipv4_stat_t);
} map_stat SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 128);
	__type(key, u32);	/* key is saddr */
	__type(value, struct ipv4_addr_t);
} map_whitelist SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 128);
	__type(key, u32);	/* key is saddr */
	__type(value, struct ipv4_addr_t);
} map_iprandom SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} events SEC(".maps");


SEC("xdp")
int xdp_dummy_prog(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	__u64 data_len = (__u64)((long)data_end - (long)data);
	struct ethhdr *ethhdr = data;
	struct iphdr *iphdr;
	//struct icmphdr *icmphdr;
	icmp_packet_t *icmphdr;
	__u32 ip_proto = 0;

	struct ipv4_key_t ipv4_key = {};
	struct ipv4_stat_t *ipv4_stat = NULL;
	struct ipv4_addr_t *white;
	struct ipv4_addr_t *rand;
	struct event_t event = {};
	struct user_config *user_config;
	const int key_user_config = MAP_KEY_USER_CONFIG;
	u64 delta, sec = bpf_ktime_get_ns() / 1000000000UL;


	event.rx_ifindex = ctx->ingress_ifindex;
	event.xdp_action = XDP_PASS;
	event.action = AC_NONE;

	if ((void *)(ethhdr + 1) > data_end)
		return XDP_PASS;

	/* Only handle ipv4 packet */
	if (bpf_ntohs(ethhdr->h_proto) != ETH_P_IP)
		return XDP_PASS;

	iphdr = data + sizeof(struct ethhdr);
	if ((void *)(iphdr + 1) > data_end)
		return XDP_PASS;

	/* Get use config first */
	user_config = bpf_map_lookup_elem(&map_config, &key_user_config);
	if (!user_config) {
		bpf_printk("xdp_dos: not found any user config.");
		return XDP_PASS;
	}

	ip_proto = iphdr->protocol;

	event.saddr = iphdr->saddr;
	event.protocol = ip_proto;

	/**
	 * Only handle ICMP
	 */
	if (ip_proto != IPPROTO_ICMP)
		return XDP_PASS;

	icmphdr = (void *)(iphdr + 1);

	/* Invalid ICMP packet, FIXME: add AK-prio */
	if ((void *)(icmphdr + 1) > data_end)
		return XDP_PASS;

	white = bpf_map_lookup_elem(&map_whitelist, &iphdr->saddr);
	if (white)
		bpf_printk("xdp address 0x%lx packet in whitelist.", iphdr->saddr);

	rand = bpf_map_lookup_elem(&map_iprandom, &iphdr->saddr);
	if (rand)
		bpf_printk("xdp address 0x%lx packet in IPrandom list.", iphdr->saddr);

	ipv4_key.saddr = iphdr->saddr;
	ipv4_key.protocol = ip_proto;

	ipv4_stat = bpf_map_lookup_elem(&map_stat, &ipv4_key);

	/* Brand new ipv4+protocol */
	if (!ipv4_stat) {
		struct ipv4_stat_t newstat = {};

		newstat.saddr = iphdr->saddr;
		newstat.protocol = ip_proto;
		newstat.npkts = 1;
		newstat.sample_start = sec;
		newstat.sample_npkts = 0;
		newstat.flags = 0;

		if (white) {
			newstat.flags &= ~F_IN_BLACKLIST;
			newstat.flags |= F_IN_WHITELIST;
		}

		if (rand)
			newstat.flags |= F_IN_IPRANDOM;

		/**
		 * Add ipv4+protocol to map_stat, statistic packet.
		 */
		if (bpf_map_update_elem(&map_stat, &ipv4_key, &newstat, BPF_NOEXIST))
			/* actually, never failed here. */
			bpf_printk("xdp_dos: add elem to map_stat failed.");
		event.action = AC_NEW_IP_ADDR;
		goto commit_event;
	}

	/* Sampling */
	ipv4_stat->npkts++;
	ipv4_stat->sample_npkts++;

	delta = sec - ipv4_stat->sample_start;

	/* Address in white list, set by user */
	if (white) {
		BPF_DEBUG("in white list.");
		ipv4_stat->flags |= F_IN_WHITELIST;
		event.xdp_action = XDP_PASS;
		event.action = AC_STAT_IN_WHITELIST;
		goto commit_event;
	}

	/**
	 * Address is already in black list, not in whitelist
	 */
	if (ipv4_stat->flags & F_IN_BLACKLIST) {
		BPF_DEBUG("in blacklist: npkts %ld, sec %ld, delta %ld\n",
			  ipv4_stat->sample_npkts, ipv4_stat->sample_start, delta);

		/**
		 * IPRandom
		 *
		 * If IP address is in IPrandom list, generate a saddr,
		 */
		if (rand) {
			__u32 random_saddr = bpf_get_prandom_u32();
			/**
			 * Ignore increment of npkts of this address above.
			 */
			ipv4_stat->npkts--;
			iphdr->saddr = random_saddr;	/* Modify saddr */
			event.random_saddr = random_saddr;
		}

		/**
		 * If it is greater than the threshold, the time and number of
		 * packets should be updated in real time. so that, we could
		 * re-record from current packet.
		 */
		if (ipv4_stat->sample_npkts >= user_config->blacklist_sample_threshold) {
			ipv4_stat->sample_npkts = 0;
			ipv4_stat->sample_start = sec;
		}

		/**
		 * If time delta greater than blacklist-sample-secs, and number
		 * of rx packets lesser than blacklist-threshold, remove address
		 * from blacklist.
		 */
		if (sec - ipv4_stat->sample_start >= user_config->blacklist_sample_secs &&
		    ipv4_stat->sample_npkts < user_config->blacklist_sample_threshold) {

			/* Remove address from blacklist */
			BPF_DEBUG("remove from blacklist: npkts %ld, sec %ld, delta %ld\n",
				  ipv4_stat->sample_npkts, ipv4_stat->sample_start, delta);

			ipv4_stat->flags &= ~F_IN_BLACKLIST;
			ipv4_stat->sample_npkts = 0;
			ipv4_stat->sample_start = sec;

			event.xdp_action = XDP_PASS;
			event.action = AC_REMOVE_FROM_BLACKLIST;

			goto commit_event;
		}

		/**
		 * High priority, pass 2 drop 1 for each 3 pkts
		 */
		if (icmphdr->ak_prio == 0) {
			if (++ipv4_stat->cnt_icmp_prio[0] <= 2) {
				event.xdp_action = XDP_PASS;
				event.black_action = AC_BLACK_PASS;
				BPF_DEBUG("icmp prio 0 pass.");
			} else {
				ipv4_stat->cnt_icmp_prio[0] = 0;
				event.xdp_action = XDP_DROP;
				event.black_action = AC_BLACK_DROP;
				BPF_DEBUG("icmp prio 0 drop.");
			}
		/**
		 * Low priority, pass 1 drop 2 for each 3 pkts
		 */
		} else if (icmphdr->ak_prio == 1) {
			if (++ipv4_stat->cnt_icmp_prio[1] <= 2) {
				event.xdp_action = XDP_DROP;
				event.black_action = AC_BLACK_DROP;
				BPF_DEBUG("icmp prio 1 drop.");
			} else {
				ipv4_stat->cnt_icmp_prio[1] = 0;
				event.xdp_action = XDP_PASS;
				event.black_action = AC_BLACK_PASS;
				BPF_DEBUG("icmp prio 1 pass.");
			}
		} else {
			event.xdp_action = XDP_DROP;
		}

		event.icmp_prio = icmphdr->ak_prio;
		event.action = AC_STAT_IN_BLACKLIST;

		/* Copy packet data to event buffer. */
		if (event.xdp_action == XDP_DROP) {
			int i;
			bpf_printk("dump pkt len %ld", data_len);
			#pragma unroll
			for (i = 0; i < sizeof(*ethhdr) + sizeof(*iphdr) + sizeof(*icmphdr); i++) {
				event.pkt_data[i] = *(char *)(data + i);
			}
			event.pkt_len = data_len;
		}

		BPF_DEBUG("move to blacklist: npkts %ld, sec %ld, delta %ld\n",
			  ipv4_stat->sample_npkts, ipv4_stat->sample_start, delta);
		goto commit_event;
	}

	/**
	 * Ok, we are not in blacklist here.
	 */

	/**
	 * 1. delta <= sampling-interval, number of packets >= MAX threshold
	 * 2. delta >  sampling-interval, number of packets >= MAX threshold
	 */
	if ((delta <= user_config->sample_secs && ipv4_stat->sample_npkts >= user_config->sample_threshold) ||
	    (delta > user_config->sample_secs && ipv4_stat->sample_npkts >= user_config->sample_threshold)) {

		if (ipv4_stat->flags & F_IN_BLACKLIST) {
			event.action = AC_STAT_IN_BLACKLIST;
		} else {
			ipv4_stat->flags |= F_IN_BLACKLIST;
			event.action = AC_MOVE_TO_BLACKLIST;
		}

		/**
		 * Just XDP_PASS this packet, of course, we could XDP_DROP,
		 * because this packet is in white-black boundary.
		 */
		event.xdp_action = XDP_PASS;
		goto commit_event;

	/* 3. Reset sampling */
	} else if (delta > user_config->sample_secs && ipv4_stat->sample_npkts < user_config->sample_threshold) {
		ipv4_stat->sample_npkts = 0;
		ipv4_stat->sample_start = sec;

		event.xdp_action = XDP_PASS;
		event.action = AC_NONE;

		BPF_DEBUG("reset sampling: delta %ld\n", delta);

		goto commit_event;
	}

	BPF_DEBUG("xdp rx pkt from ifindex %d, saddr 0x%x, len %ld",
		  ctx->ingress_ifindex, iphdr->saddr,
		  (u64)(ctx->data_end - ctx->data));
	BPF_DEBUG("event action %d, saddr %d", event.action, iphdr->saddr);

commit_event:

	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, &event, sizeof(event));
	return event.xdp_action;
}

char __license[] SEC("license") = "GPL";
