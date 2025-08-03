#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include "call.h"


int int_1 = 1024;
EXPORT_SYMBOL(int_1);

int print_1(void)
{
	return printk("print %d\n", int_1);
}
EXPORT_SYMBOL(print_1);

int print_2(void)
{
	return printk("print %d\n", int_1);
}
EXPORT_SYMBOL_GPL(print_2);

MODULE_LICENSE("Dual BSD/GPL");
