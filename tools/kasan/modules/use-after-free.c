/**
 *	File	free.c
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
	printk(KERN_INFO "init.\n");
	addr = kmalloc(32, GFP_KERNEL);
	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "exit.\n");
	kfree(addr);

	/* use after free */
	*(char *)addr = 'a';
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
