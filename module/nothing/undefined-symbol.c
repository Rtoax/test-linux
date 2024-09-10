#include <linux/module.h>

extern void undefined_func(void);

static int kernel_init(void)
{
	undefined_func();
	return 0;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("Dual BSD/GPL");
