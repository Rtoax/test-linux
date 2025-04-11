#include <linux/kernel.h>
#include <linux/module.h>

static int __init test_init(void)
{
	unsigned int i = 0x11101;

	printk("__sw_hweight32(%#x) = %u\n", i, __sw_hweight32(i));

	return -EINVAL;
}
module_init(test_init);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("Dual BSD/GPL");

