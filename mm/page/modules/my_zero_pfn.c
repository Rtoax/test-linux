/**
 *	File	./my_zero_pfn.c
 *	Time	2021.11.05
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/mm.h>

static int kernel_init(void)
{
    printk(KERN_INFO "========== my init =========\n");
	printk(KERN_INFO "zero pfn = %lx\n", my_zero_pfn(0));
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
