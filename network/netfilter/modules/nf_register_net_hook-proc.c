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
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

DEFINE_MUTEX(range_count_mutex);

static struct nf_hook_ops netfilter_ops;

unsigned int main_hook(void *priv,
		       struct sk_buff *skb,
		       const struct nf_hook_state *state)
{
    printk(KERN_INFO "PF_INET netfilter hook called.\n");
    return NF_ACCEPT;
}

static char message[1024];

ssize_t filter_read(struct file *f, char __user *u, size_t req, loff_t *off)
{
    int message_offset;
    int i;

    message_offset = 0;
    mutex_lock(&range_count_mutex);
    for (i = 0; i < google_range_count; i++) {
        message_offset +=
            snprintf(message + message_offset, sizeof(message) - message_offset,
                     "range %d (%pI4 - %pI4): %zu\n", i, google_ranges[i].start,
                     google_ranges[i].end, range_count[i]);
        if(message_offset >= 1024)
          break;
    }
    mutex_unlock(&range_count_mutex);

    if (*off > message_offset)
        return 0;
    if(req > message_offset - *off)
        req = message_offset - *off;

    copy_to_user(u, message+*off, req);
    *off += req;
    
    return req;
}
struct file_operations fops = {
    .read = filter_read,
};
struct proc_dir_entry *filterdir;

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    
    // Creates  /proc/filter/
    filterdir = proc_mkdir("filter", NULL); 
    // creates /proc/filter/status
    proc_create("status", 0666, filterdir, &fops); 
    
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
    remove_proc_entry("status", filterdir);
    remove_proc_entry("filter", NULL);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
