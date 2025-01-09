// SPDX-License-Identifier: GPL-3.0
#pragma once

#include <stdio.h>
#include <stdint.h>

#define pr_pkt(fmt...) do { \
		fprintf(stdout, "\033[1;32m"); \
		fprintf(stdout, fmt); \
		fprintf(stdout, "\033[m"); \
	} while (0)

#define pr_pkt_err(fmt...) do { \
		fprintf(stderr, "\033[1;31m"); \
		fprintf(stderr, fmt); \
		fprintf(stderr, "\033[m"); \
	} while (0)

#define pr_pkt_dbg(fmt...) do { \
		fprintf(stderr, "\033[2m"); \
		fprintf(stderr, fmt); \
		fprintf(stderr, "\033[m"); \
	} while (0)


const char *stricmptype(uint8_t type);
void dump_icmp(struct icmphdr *hdr, size_t len);
unsigned short icmp_chksum(struct icmphdr *addr, int len);
int gen_pkt_icmp_reply(void *rx_pkt, struct icmphdr *request, void *tx_pkt_buf);
