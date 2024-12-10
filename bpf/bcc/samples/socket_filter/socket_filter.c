#include <bcc/proto.h>
#include <net/sock.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/pkt_cls.h>

#ifndef ETH_P_IP
#define ETH_P_IP	0x0800
#endif
#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP	0x01
#endif
#ifndef IPPROTO_TCP
#define IPPROTO_TCP	0x06
#endif

/**
 *  0: DROP the packet
 * -1: KEEP the packet and return it to user space (userspace can read it
 *     from the socket_fd)
 */
#define KEEP	(-1)
#define DROP	(0)

int socket_filter(struct __sk_buff *skb)
{
	unsigned char *cursor = NULL;

	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));

	/* look for IP Packets */
	if (ethernet->type != ETH_P_IP)
		return DROP;

	struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));
	if (ip->nextp == IPPROTO_ICMP) {
		bpf_trace_printk("[socket_filter] icmp %s\n", ip->dst);
	} else if (ip->nextp == IPPROTO_TCP) {
		bpf_trace_printk("[socket_filter] tcp %s\n", ip->dst);
		/* -1: Send TCP Packets to userspace */
		return KEEP;
	}

	return DROP;
}
