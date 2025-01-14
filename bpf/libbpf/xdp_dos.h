#pragma once

#if defined(DEBUG)
#define DIR_FILTER_DUMP		"./filter_dump/"
#define LOG_PACKET_FILTER	"./packet_filter.log"
#define LOG_PACKET_MUTATE	"./packet_mutate.log"
#else
#define DIR_FILTER_DUMP		"/tmp/filter_dump/"
#define LOG_PACKET_FILTER	"/var/log/packet_filter.log"
#define LOG_PACKET_MUTATE	"/var/log/packet_mutate.log"
#endif
#define MAP_KEY_USER_CONFIG	0

struct user_config {
	int sample_secs;
	int sample_threshold;
	int blacklist_sample_secs;
	int blacklist_sample_threshold;
};

struct ipv4_addr_t {
	__u32 addr;	/* net endian */
};

struct ipv4_key_t {
	__u32 saddr;		/* srouce address (net endian) */
	__u32 protocol;		/* ipv4 protocol */
};

struct ipv4_stat_t {
	__u32 saddr;		/* srouce address (net endian) */
	__u32 protocol;		/* ipv4 protocol */
	__u64 npkts;		/* total packets of one source address */
	__u64 sample_start;	/* each sample interval start, both used in
				 * whitelist and blacklist */
	__u64 sample_npkts;	/* each sample period packets count, both used
				 * in whitelist and blacklist */
#define F_IN_BLACKLIST	(1 << 0)	/* address in blacklist */
#define F_IN_WHITELIST	(1 << 1)	/* address in whitelist */
#define F_IN_IPRANDOM	(1 << 2)	/* address in IPrandom list */
	__u32 flags;

	/**
	 * action = AC_STAT_IN_BLACKLIST
	 */
	__u32 cnt_icmp_prio[2];
};

struct event_t {
	int rx_ifindex;
	__u32 saddr;
	__u32 protocol;

	int xdp_action; /* XDP actions, XDP_ABORTED, XDP_DROP, XDP_PASS,
			 * XDP_TX, XDP_REDIRECT, */
#define AC_NONE				0	/* None */
#define AC_NEW_IP_ADDR			1	/* Get new address */
#define AC_MOVE_TO_BLACKLIST		2	/* Move ip to blacklist */
#define AC_STAT_IN_BLACKLIST		3	/* Already in blacklist */
#define AC_REMOVE_FROM_BLACKLIST	4	/* Remove from blacklist */
#define AC_STAT_IN_WHITELIST		5	/* Add to whitelist by user */
	int action;

	/**
	 * action = AC_STAT_IN_BLACKLIST
	 */
#define AC_BLACK_DROP		1	/* drop pkt in black list */
#define AC_BLACK_PASS		2	/* pass pkt in black list */
	int black_action;

	__u8 icmp_prio;	/* 0 or 1 */

	/**
	 * if packet is droped(black_action = AC_BLACK_DROP), send packet to
	 * user space, dump it.
	 *
	 * 256 is enough
	 */
	__u32 pkt_len;
	char pkt_data[128];

	__u32 random_saddr;

};

