#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>


static int kernel_init(void)
{
	printk(KERN_INFO "Testing CLOCK accuracy.\n");
	/* TODO */
	return -1;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
