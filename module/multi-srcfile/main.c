#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include "foo.h"


static __init int main_init(void)
{
	printk(KERN_INFO "Hi from init\n");
	foo();
	return 0;
}

static __exit void main_exit(void)
{
	printk(KERN_INFO "Bye!\n");
}

module_init(main_init)
module_exit(main_exit)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
