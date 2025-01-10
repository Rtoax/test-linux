// SPDX-License-Identifier: GPL-3.0
#pragma once

#include <stdio.h>
#include <stdint.h>


const char *stricmptype(uint8_t type);
void dump_icmp(struct icmphdr *hdr, size_t len);
unsigned short icmp_chksum(struct icmphdr *addr, int len);
int gen_pkt_icmp_reply(void *rx_pkt, struct icmphdr *request, void *tx_pkt_buf);
