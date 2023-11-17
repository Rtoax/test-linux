#include <linux/mm.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>

static int __init ramtest_init(void)
{
	printk("ramtest_init.\n");

	printk("TotalRAM pages = %ld\n", totalram_pages());
	printk("TotalRAM GB    = %ld\n", totalram_pages()*PAGE_SIZE/1024/1024/1024);

	/* insmod failed on purpose */
	return -1;
}

static void __exit ramtest_exit(void)
{
	printk("ramtest_exit.\n");
}

module_init(ramtest_init);
module_exit(ramtest_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
