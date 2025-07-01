// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#include <stdio.h>
#include <stdint.h>


const char *stricmptype(uint8_t type);
void dump_icmp(struct icmphdr *hdr, size_t len);
unsigned short icmp_chksum(struct icmphdr *addr, int len);
int gen_pkt_icmp_reply(void *rx_pkt, struct icmphdr *request, void *tx_pkt_buf);
