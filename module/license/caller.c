#include <linux/module.h>

extern int int_1;
extern int print_1(void);

static int simple_init(void)
{
	printk(KERN_WARNING "int_1=%d\n", int_1);
	print_1();
	return -EINVAL;
}

module_init(simple_init);
MODULE_LICENSE("Dual BSD/GPL");
