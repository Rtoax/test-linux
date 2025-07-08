// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <argp.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/in.h>
#include <net/if.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @ifname could be NULL, if NULL, skip bind(2).
 */
int open_raw_sock(const char *ifname, bool nonblk)
{
	int sock, flags;
	struct sockaddr_ll sll;

	flags = SOCK_CLOEXEC;
	if (nonblk)
		flags |= SOCK_NONBLOCK;

	/* Data Link Layer */
	sock = socket(PF_PACKET, SOCK_RAW | flags, htons(ETH_P_ALL));
	if (sock < 0) {
		fprintf(stderr, "Failed to create raw socket\n");
		return -1;
	}

	if (ifname) {
		memset(&sll, 0, sizeof(sll));
		sll.sll_family = AF_PACKET;
		sll.sll_ifindex = if_nametoindex(ifname);
		sll.sll_protocol = htons(ETH_P_ALL);
		if (bind(sock, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
			fprintf(stderr, "Failed to bind to %s: %s\n", ifname, strerror(errno));
			close(sock);
			return -1;
		}
	}

	return sock;
}
