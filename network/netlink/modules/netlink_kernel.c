#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#include "common.h"

struct sock *nl_sk = NULL;

static void hello_nl_recv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	int pid;
	struct sk_buff *skb_out;
	int res;

	int msg_size;
	char *msg = "hello, this msg is from kernel";

	printk(KERN_INFO "Entering: %s\n", __FUNCTION__);

	msg_size = strlen(msg);

	/* for receiving...
	 * nlh message comes from skb's data, (sk_buff: unsigned char *data) */
	nlh = (struct nlmsghdr*)skb->data;

	/*	nlmsg_data - head of message payload
	 *	   (unsigned char *) nlh + NLMSG_HDRLEN; */
	printk(KERN_INFO "Netlink received msg payload: %s\n", (char*)nlmsg_data(nlh));

	/* for sending...
	 * Sending process port ID, will send new message back to the
	 * 'user space sender' */
	pid = nlh->nlmsg_pid;

	/* nlmsg_new - Allocate a new netlink message: skb_out */
	skb_out = nlmsg_new(msg_size, 0);

	if (!skb_out) {
		printk(KERN_ERR "Failed to allocate new skb\n");
		return;
	}
	/* nlmsg_put - Add a new netlink message to an skb */
	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);

	/* not in mcast group */
	NETLINK_CB(skb_out).dst_group = 0;

	strncpy(nlmsg_data(nlh), msg, msg_size);

	/* nlmsg_unicast - unicast a netlink message
	 * @pid: netlink pid of the destination socket */
	res = nlmsg_unicast(nl_sk, skb_out, pid);
	if (res < 0)
		printk(KERN_INFO "Error while sending bak to user\n");
}

static int __init hello_init(void)
{
	struct netlink_kernel_cfg cfg = {
		.input = hello_nl_recv_msg,
	};

	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
	if (!nl_sk) {
		printk(KERN_ALERT "Error creating socket.\n");
		return -10;
	}

	printk("Init OK!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "exiting hello module\n");
	netlink_kernel_release(nl_sk);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");