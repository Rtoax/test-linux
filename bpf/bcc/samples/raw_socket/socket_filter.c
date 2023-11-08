#include <bcc/proto.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/pkt_cls.h>


int socket_filter(struct __sk_buff *skb)
{
	unsigned char *cursor = NULL;

	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));

	/* look for IP Packets */
	if (ethernet->type != 0x0800)
		return 0;

	struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));
	if (ip->nextp == 0x01)
		bpf_trace_printk("[socket_filter] ICMP request for %s\n", ip->dst);
	else if (ip->nextp == 0x06) {
		bpf_trace_printk("[socket_filter] ICMP request for %s\n", ip->dst);
		/* Send TCP Packets to userspace */
		return -1;
	}

	return 0;
}
