/**
 *	File	super_block.c
 *	Time	2021.11.07
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    // TODO
    return 0;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
