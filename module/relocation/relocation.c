#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

int local_i = 123;

static int kernel_init(void)
{
	local_i++;
	printk(KERN_INFO "i = %d.\n", local_i);
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
