#include <linux/module.h>

int int_1 = 1024;
EXPORT_SYMBOL(int_1);

int print_1(void)
{
	return printk("print %d\n", int_1);
}
EXPORT_SYMBOL(print_1);

MODULE_LICENSE("Dual BSD/GPL");
