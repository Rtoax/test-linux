#pragma once

enum operation_t {
	OP_WHITE,
	OP_BLACK,
};

struct ipv4_addr_t {
	__u32 addr;	/* net endian */
	enum operation_t op;
};

struct event_t {
	int rx_ifindex;
	int xdp_action;	/* XDP actions, XDP_ABORTED, XDP_DROP, XDP_PASS,
			 * XDP_TX, XDP_REDIRECT, */
};
