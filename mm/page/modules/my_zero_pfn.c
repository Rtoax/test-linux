#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/mm.h>

static int kernel_init(void)
{
	printk(KERN_INFO "========== my init =========\n");
	printk(KERN_INFO "zero pfn = %lx\n", my_zero_pfn(0));
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
