/**
 *	File	slab_def.c
 *	Time	2023-01-17
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/gfp.h>


static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");
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
