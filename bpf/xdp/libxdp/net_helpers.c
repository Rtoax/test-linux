// SPDX-License-Identifier: GPL-3.0
#include <arpa/inet.h>
#include <stdio.h>
#include <linux/icmp.h>

#include "net_helpers.h"

const char *stricmptype(uint8_t type)
{
	switch (type) {
#define CASE(v) case ICMP_##v: return (#v);
	CASE(ECHOREPLY);
	CASE(DEST_UNREACH);
	CASE(SOURCE_QUENCH);
	CASE(REDIRECT);
	CASE(ECHO);
	CASE(TIME_EXCEEDED);
	CASE(PARAMETERPROB);
	CASE(TIMESTAMP);
	CASE(TIMESTAMPREPLY);
	CASE(INFO_REQUEST);
	CASE(INFO_REPLY);
	CASE(ADDRESS);
	CASE(ADDRESSREPLY);
	}
	return "Unknown";
}

void dump_icmp(struct icmphdr *hdr, size_t len)
{
	pr_pkt("type %s, code %d, cksum 0x%04x",
		stricmptype(hdr->type), hdr->code, hdr->checksum);
	if (hdr->type == ICMP_ECHO)
		pr_pkt(", id %d, seq %d", htons(hdr->un.echo.id),
			htons(hdr->un.echo.sequence));
	/* Payload, test with 'ping -s [size]' */
	if (len > sizeof(struct icmphdr))
		pr_pkt(", payload(len %ld)", len - sizeof(struct icmphdr));
	pr_pkt("\n");
}

