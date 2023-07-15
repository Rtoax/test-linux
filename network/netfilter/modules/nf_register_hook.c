/**
 *	nf_register_hook is delete from linux-4.13
 *	only <= 4.12 has nf_register_hook
 *	http://heapspray.net/post/writing-a-netfilter-linux-kernel-module-for-3xx-kernels/
 *	can not compile successful
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
 
static struct nf_hook_ops hk; 
 
/* if you get a warning about this function, change the first argument to "const struct nf_hook_ops *ops" - it is basically a copy of the variables fed into 'hk' below */
unsigned int nf_hook_ex(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *)){
 
        if (skb != NULL)
                printk(KERN_INFO "Dropping received packet\n");
 
        return NF_DROP;
}
 
/* Called when module loaded using 'insmod' */
int kmod_init(void){
        /* Just some fancy C to copy an inline struct */
        hk = (struct nf_hook_ops){
                .hook = nf_hook_ex, /* this is important, this variable is of type nf_hookfn - the signature of the function MUST match this type */
                .hooknum = NF_INET_PRE_ROUTING, /* Prerouting is the first netfilter stage */
                .pf = PF_INET, /* Just hook for Internet Packets */
                .priority = NF_IP_PRI_FIRST /* Run this hook before any other hook */
        };
        nf_register_hook(&hk);
 
  return 0;
}
 
/* Called when module unloaded using 'rmmod' */
void kmod_exit(void){
        nf_unregister_hook(&hk);
}
 
/* Some standard macros to pass the kernel compile script some information */
module_init(kmod_init);
module_exit(kmod_exit);
MODULE_LICENSE("GPL");
