#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("My kernel hello module");
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk("Hi, hello\n");
	printk("CURRENT_PATH = %s\n", CURRENT_PATH);
	return 0;
}

static void hello_exit(void)
{
	printk("Bye, hello\n");
}

module_init(hello_init);
module_exit(hello_exit);
