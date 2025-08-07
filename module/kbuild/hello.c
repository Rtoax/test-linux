#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int ok = 0;
module_param(ok, int, 0660);

static int hello_init(void)
{
	printk("Hi, hello\n");
#ifndef CURRENT_PATH
#error Not define CURRENT_PATH
#endif
#ifdef CCFLAGS_Y
#pragma message("CCFLAGS_Y")
#endif
#ifdef HELLO1
#pragma message("hello1")
#endif
#ifdef HELLO2
#pragma message("hello2")
#endif
	printk("CURRENT_PATH = %s\n", CURRENT_PATH);
	if (ok)
		return 0;
	return -EINVAL;
}

static void hello_exit(void)
{}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("My kernel hello module");
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
