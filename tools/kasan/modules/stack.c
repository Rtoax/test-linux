/**
 *	File	stack.c
 *	Time	2022-04-29
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int call_count = 1000;
module_param(call_count, int, 0660);

int __attribute__((optimize("-O0")))
stack_overflow(int i)
{
	printk(KERN_INFO "stack_overflow %-16d.\n", i);
	return i?stack_overflow(i-1):-1;
}

static int kernel_init(void)
{
	printk(KERN_INFO "init.\n");

	stack_overflow(call_count);

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
