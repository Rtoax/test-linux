/**
 * Description: Get Current Exception Level
 *
 * 2023-09-22	Rong Tao	Create this.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include "currentel.h"


static int __init kernel_init(void)
{
	register uint64_t x0 = currentel();
	printk(KERN_INFO "EL = %lld\n", x0);
	/* make insmod failed, so, we don't need to rmmod */
	return -1;
}

static void __exit kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("Get Current Exception Level");
