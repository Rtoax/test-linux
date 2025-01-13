#pragma once

enum operation_t {
	OP_WHITE,
	OP_BLACK,
};

struct ipv4_addr_t {
	__u32 addr;	/* net endian */
	enum operation_t op;
};

