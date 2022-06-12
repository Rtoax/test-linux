/**
 *	File request-irq.c 
 *	Time 2021.11.03
 *	Author Rong Tao <rongtao@cestc.cn>
 */
#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/interrupt.h> // included for request_irq and free_irq macros
#include <linux/preempt.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A Simple request irq module");
MODULE_VERSION("0.1");

static int irqnum = 2;
module_param(irqnum, int, 0644);
MODULE_PARM_DESC(irqnum, "irq number, acpi is OK");

static char *name = "testirq";
module_param( name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "irq name");	

struct myirq {
	int devid;
};
struct myirq mydev = {1119};

irqreturn_t no_action(int cpl, void *dev_id)
{
    printk(KERN_INFO "irq line number is %d!\n", cpl);
	printk(KERN_INFO "in_task       = %d\n", in_task());
	printk(KERN_INFO "in_irq        = %ld\n", in_irq());
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
	printk(KERN_INFO "in_hardirq    = %ld\n", in_hardirq());
#endif
	printk(KERN_INFO "in_softirq    = %ld\n", in_softirq());
	printk(KERN_INFO "in_interrupt  = %ld\n", in_interrupt());
	printk(KERN_INFO "softirq_count = %ld\n", softirq_count());
	printk(KERN_INFO "hardirq_count = %ld\n", hardirq_count());
	printk(KERN_INFO "irq_count     = %ld\n", irq_count());
	//return IRQ_NONE;
	return IRQ_HANDLED;
}


static int __init rtoax_irq_init(void)
{
	printk(KERN_INFO "request irq %s!\n", name);
	/**
	 *	IRQF_SHARED - 共享中断线，在支持共享的中断线上可注册
	 */
    if (request_irq(irqnum, no_action, IRQF_SHARED, name, &mydev) != 0) {
	    printk(KERN_ERR "%s: request_irq() failed\n", name);
		return -1;
	}
	return 0;
}

static void __exit rtoax_irq_cleanup(void)
{
	printk(KERN_INFO "free irq.\n");
    /*
     *  释放中断
     */
    free_irq(irqnum, &mydev);
}

module_init(rtoax_irq_init);
module_exit(rtoax_irq_cleanup);
