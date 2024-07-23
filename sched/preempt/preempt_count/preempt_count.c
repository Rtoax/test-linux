#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/kernel.h>

static int print_count(const char *discription)
{
	printk("======== %s ========\n", discription);
#define M(mask) \
	printk(KERN_INFO "%20s = 0x%08lx\n", #mask, mask)

	M(PREEMPT_MASK);
	M(SOFTIRQ_MASK);
	M(HARDIRQ_MASK);
	M(NMI_MASK);

#define COUNT(count) \
	printk(KERN_INFO "%20s = 0x%08lx\n", #count, count)

	COUNT(hardirq_count());
	COUNT(softirq_count());
	COUNT(irq_count());

	return 0;
}

static int test_init(void)
{
	printk(KERN_INFO "Hi.\n");

	print_count("test 1");

	preempt_disable();

	print_count("preempt_disable()");

	preempt_enable();

	return 0;
}

static void test_exit(void)
{
	printk(KERN_INFO "bye.\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
