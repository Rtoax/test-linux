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
	register uint64_t x0 = read_sysreg(CurrentEL);
	register int el = currentel();

	char *run = "Unknown";
	switch (el) {
	case 0:
		run = "userspace";
		break;
	case 1:
		run = "kernel";
		break;
	case 2:
		run = "hypervisor";
		break;
	case 3:
		run = "secure monitor";
		break;
	}

	printk(KERN_INFO "EL = %lld, el = %d, may run %s\n", x0 >> 2, el, run);
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
