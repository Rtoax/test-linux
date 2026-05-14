#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/kernel.h>
#include <linux/version.h>

static int test_init(void)
{
	printk(KERN_INFO "in_task = %ld\n", in_task());
	printk(KERN_INFO "in_softirq = %ld\n", in_softirq());
/**
 * v6.18-rc2-1-g70e0a80a1f35
 * commit 70e0a80a1f35 ("treewide: Remove in_irq()")
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 18, 0)
	printk(KERN_INFO "in_irq = %ld\n", in_irq());
#endif
	printk(KERN_INFO "in_nmi = %ld\n", in_nmi());
	return -EINVAL;
}

module_init(test_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
