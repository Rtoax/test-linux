#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/interrupt.h> // included for request_irq and free_irq macros
#include <linux/preempt.h>
#include <linux/workqueue.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A Simple workqueue bottom half module");
MODULE_VERSION("0.1");

static int irqnum = 2;
module_param(irqnum, int, 0644);
MODULE_PARM_DESC(irqnum, "irq number, acpi is OK");

static char *name = "workqueue-template";
module_param( name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "irq name");	

struct myirq {
	int devid;
};

struct myirq mydev = {
	.devid = 1119,
};

struct work_struct myworkqueue;

void my_do_work(struct work_struct *work);

static void print_irq_status(char *prefix)
{
	printk(KERN_INFO "%20s in_task       = %d\n", prefix, in_task());
	printk(KERN_INFO "%20s in_irq        = %ld\n", prefix, in_irq());
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
	printk(KERN_INFO "%20s in_hardirq    = %ld\n", prefix, in_hardirq());
#endif
	printk(KERN_INFO "%20s in_softirq    = %ld\n", prefix, in_softirq());
	printk(KERN_INFO "%20s in_interrupt  = %ld\n", prefix, in_interrupt());
	printk(KERN_INFO "%20s softirq_count = %ld\n", prefix, softirq_count());
	printk(KERN_INFO "%20s hardirq_count = %ld\n", prefix, hardirq_count());
	printk(KERN_INFO "%20s irq_count     = %ld\n", prefix, irq_count());
}

void my_do_work(struct work_struct *work)
{
	print_irq_status("irq bottom workqueue half: ");
}

irqreturn_t no_action(int cpl, void *dev_id)
{
	printk(KERN_INFO "irq line number is %d!\n", cpl);
	print_irq_status("irq top half: ");

	schedule_work(&myworkqueue);

	return IRQ_HANDLED;
}

static int __init rtoax_irq_init(void)
{
	printk(KERN_INFO "request irq %s!\n", name);
	if (request_irq(irqnum, no_action, IRQF_SHARED, name, &mydev) != 0) {
		printk(KERN_ERR "%s: request_irq() failed\n", name);
		return -1;
	}
	INIT_WORK(&myworkqueue, my_do_work);
	return 0;
}

static void __exit rtoax_irq_cleanup(void)
{
	printk(KERN_INFO "free irq.\n");
	free_irq(irqnum, &mydev);
}

module_init(rtoax_irq_init);
module_exit(rtoax_irq_cleanup);
