/**
 *	File	sections.c
 *	Time	2021.11.20
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/version.h>

#include <asm-generic/sections.h>

static void print_sections(void)
{
	/**
	 * _text is undefined
	 */
	extern char __attribute__((unused)) _text[];
	//printk("_text = %p\n", _text);	
}

static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");

	print_sections();

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
