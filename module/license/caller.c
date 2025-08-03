#include <linux/module.h>
#include "call.h"


extern int int_1;
print1_fn print;

static int simple_init(void)
{
	print = (print1_fn)symbol_get("print_1");

	printk(KERN_WARNING "int_1=%d\n", int_1);
	print();

	return -EINVAL;
}

module_init(simple_init);
MODULE_LICENSE("GPL");
