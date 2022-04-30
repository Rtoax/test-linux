/**
 *	File	global-out-of-bounds.c
 *	Time	2022-04-29
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#include "kasan.h"

char string[32] = {"Rong Tao"};

static int kernel_init(void)
{
	printk(KERN_INFO "init.\n");

	/**
	 * global out of bounds
	 */
	string[32] = 'a';

	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
