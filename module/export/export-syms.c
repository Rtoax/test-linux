#include <linux/module.h>
#include <linux/printk.h>

#include "common.h"

void my_print_hello(struct module *mod)
{
	printk(KERN_INFO "Hello World from module %s\n", module_name(mod));
}
EXPORT_SYMBOL(my_print_hello);

static int kernel_init(void)
{
	struct module *mod = THIS_MODULE;
	my_print_hello(mod);
	return 0;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("Dual BSD/GPL");
