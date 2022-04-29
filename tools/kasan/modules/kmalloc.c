/**
 *	File	kmalloc.c
 *	Time	2022-04-29
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

void *addr = NULL;

static int kernel_init(void)
{
	char *s;

	printk(KERN_INFO "init.\n");
	addr = kmalloc(32, GFP_KERNEL);
	s = addr;
	/**
	 * 此处并没有越界提示
	 */
	s[33] = 'a';

	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "exit.\n");
	kvfree(addr);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
