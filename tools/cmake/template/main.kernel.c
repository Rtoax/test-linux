// SPDX-License-Identifier: GPL-3.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
#else
#endif

static int __init kernel_init(void)
{
	return 0;
}

static void __exit kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("Test kernel module");
