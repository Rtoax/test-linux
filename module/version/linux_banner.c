#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");
	/**
	 * linux_banner undefined
	 */
	//printk(KERN_INFO "linux_banner = %s\n", linux_banner);
	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
