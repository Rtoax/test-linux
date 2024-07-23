#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/kernel.h>

static int test_init(void)
{
	printk(KERN_INFO "in_task = %ld\n", in_task());
	printk(KERN_INFO "in_softirq = %ld\n", in_softirq());
	printk(KERN_INFO "in_irq = %ld\n", in_irq());
	printk(KERN_INFO "in_nmi = %ld\n", in_nmi());
	return -EINVAL;
}

module_init(test_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
