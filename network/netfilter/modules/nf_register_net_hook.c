/**
 *	File	nf_register_net_hook
 *	Time	2021.11.07
 *	Author	Rong Tao <rongtao@cestc.cn>
 *
 *  Reference: 
 *  http://cs241.cs.illinois.edu/assignments/notorious_netfilter
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/if_ether.h>

static struct nf_hook_ops netfilter_ops;

unsigned int main_hook(void *priv,
		       struct sk_buff *skb,
		       const struct nf_hook_state *state)
{
	struct ethhdr *mh = eth_hdr(skb);
	struct iphdr *iph = ip_hdr(skb);

    printk(KERN_INFO "PF_INET netfilter hook called.\n");
	printk(KERN_INFO "MAC %x:%x:%x:%x:%x:%x -> %x:%x:%x:%x:%x:%x\n",
				mh->h_source[0],mh->h_source[1],
				mh->h_source[2],mh->h_source[3],
				mh->h_source[4],mh->h_source[5],
				mh->h_dest[0],mh->h_dest[1],
				mh->h_dest[2],mh->h_dest[3],
				mh->h_dest[4],mh->h_dest[5]);
	printk(KERN_INFO "id: %d, protocol: %d, ttl: %d",iph->id, iph->protocol,iph->ttl);

    return NF_ACCEPT;
}

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    
    netfilter_ops.hook = main_hook;
    netfilter_ops.pf = PF_INET;
    netfilter_ops.hooknum = 0;
    netfilter_ops.priority = NF_IP_PRI_FIRST;
    
    nf_register_net_hook(&init_net, &netfilter_ops);
    
    return 0;
}

static void kernel_exit(void)
{
    printk(KERN_INFO "my exit.\n");
    nf_unregister_net_hook(&init_net, &netfilter_ops);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
