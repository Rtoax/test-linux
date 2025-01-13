// SPDX-License-Identifier: GPL-3.0
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/ip.h>

#include "net_helpers.h"
#include "log.h"


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
	pr_inf("type %s, code %d, cksum 0x%04x",
		stricmptype(hdr->type), hdr->code, hdr->checksum);
	if (hdr->type == ICMP_ECHO)
		pr_inf(", id %d, seq %d", htons(hdr->un.echo.id),
			htons(hdr->un.echo.sequence));
	/* Payload, test with 'ping -s [size]' */
	if (len > sizeof(struct icmphdr))
		pr_inf(", payload(len %ld)", len - sizeof(struct icmphdr));
	pr_inf("\n");
}

unsigned short icmp_chksum(struct icmphdr *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = (void *)addr;
	unsigned short answer = 0;

	/**
	 * Accumulate the ICMP header binary data in units of 2 bytes
	 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}

/**
 * Return icmp packetsize, see 'ping -s'
 */
int gen_pkt_icmp_reply(void *rx_pkt, struct icmphdr *request, void *tx_pkt_buf)
{
	int packetsize;
	off_t ipoff = sizeof(struct ethhdr);
	off_t icmpoff = sizeof(struct ethhdr) + sizeof(struct iphdr);

	struct ethhdr *rx_ethhdr = rx_pkt;
	struct iphdr *rx_iphdr = rx_pkt + ipoff;
	struct icmphdr *rx_icmphdr = rx_pkt + icmpoff;

	struct ethhdr *tx_ethhdr = tx_pkt_buf;
	struct iphdr *tx_iphdr = tx_pkt_buf + ipoff;
	struct icmphdr *tx_icmphdr = tx_pkt_buf + icmpoff;

	memcpy(tx_ethhdr->h_dest, rx_ethhdr->h_source, ETH_ALEN);
	memcpy(tx_ethhdr->h_source, tx_ethhdr->h_dest, ETH_ALEN);
	tx_ethhdr->h_proto = htons(ETH_P_IP);

#if 0
	tx_iphdr->version = 0x4;
	tx_iphdr->ihl = 0x5;
	tx_iphdr->tos = 0x9;
	tx_iphdr->tot_len = htons(60);
	tx_iphdr->id = 0;
	tx_iphdr->frag_off = 0;
	tx_iphdr->ttl = 64;
	tx_iphdr->protocol = IPPROTO_ICMP;
	tx_iphdr->saddr = rx_iphdr->daddr;
	tx_iphdr->daddr = rx_iphdr->saddr;
	tx_iphdr->check = 0;
#else
	memcpy(tx_iphdr, rx_iphdr, sizeof(struct iphdr));
	tx_iphdr->saddr = rx_iphdr->daddr;
	tx_iphdr->daddr = rx_iphdr->saddr;
#endif

	packetsize = sizeof(struct icmphdr) + 1;
	memset(tx_icmphdr, 0x00, packetsize);

	tx_icmphdr->type = ICMP_ECHOREPLY;
	tx_icmphdr->code = rx_icmphdr->code;
	tx_icmphdr->checksum = 0;
	tx_icmphdr->un.echo.id = rx_icmphdr->un.echo.id;
	tx_icmphdr->un.echo.sequence = ntohs(htons(rx_icmphdr->un.echo.sequence) + 1);

	tx_icmphdr->checksum = icmp_chksum(tx_icmphdr, packetsize);

	return packetsize;
}
