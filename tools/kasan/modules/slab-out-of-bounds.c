/**
 *	File	slab-out-of-bounds.c
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
	 * slab out of bounds
	 */
	s[33] = 'a';

	return 0;
}

static void kernel_exit(void)
{
	char *s;

	printk(KERN_INFO "exit.\n");
	kvfree(addr);

	s = addr;
	/**
	 * use after free
	 */
	s[0] = 'a';
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
