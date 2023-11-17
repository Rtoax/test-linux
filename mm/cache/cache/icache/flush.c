#include <linux/mm.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>


static void __exit flush_exit(void);

static int __init flush_init(void)
{
	printk("flush_init.\n");

	unsigned long start = (unsigned long)flush_init;
	unsigned long end = (unsigned long)flush_exit;

	/* TODO: Flush icache */
	//__flush_icache_range(start, end);

	return 0;
}

static void __exit flush_exit(void)
{
	printk("flush_exit.\n");
}

module_init(flush_init);
module_exit(flush_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
