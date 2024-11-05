#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
{
	printk("Hi, hello\n");
#ifndef CURRENT_PATH
#error Not define CURRENT_PATH
#endif
	printk("CURRENT_PATH = %s\n", CURRENT_PATH);
	return -EINVAL;
}

module_init(hello_init);

MODULE_DESCRIPTION("My kernel hello module");
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
