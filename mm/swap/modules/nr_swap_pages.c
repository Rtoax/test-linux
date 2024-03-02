/**
 *	File	nr_swap_pages.c
 *	Time	2022-03-27
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/swap.h>

static int kernel_init(void)
{
	unsigned long nr_swap_pages = get_nr_swap_pages();
    printk(KERN_INFO "nr_swap_pages = %ld 0x%lx\n",
		   nr_swap_pages, nr_swap_pages);
    return 0;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
