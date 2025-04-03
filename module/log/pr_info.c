#include <linux/kernel.h>
#include <linux/module.h>

static int __init mod_init(void)
{
	pr_info("pr_info");
	pr_warn("pr_warn");
	pr_err("pr_err");
	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test log");
