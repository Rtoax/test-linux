#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include "call.h"


extern int int_1;

static int call_print(const char *fname)
{
	/**
	 * NOTE: __symbol_get() can only get EXPORT_SYMBOL_GPL()
	 * err: failing symbol_get of non-GPLONLY symbol jiffies
	 */
	print1_fn print = (print1_fn)__symbol_get(fname);
	if (!print)
		return -ENXIO;
	print();
	__symbol_put(fname);
	return 0;
}

static int simple_init(void)
{
	printk(KERN_WARNING "int_1=%d\n", int_1);

	call_print("print_1");
	call_print("print_2");

	return -EINVAL;
}

module_init(simple_init);
MODULE_LICENSE("GPL");
