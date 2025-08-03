#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>

/**
 * time/jiffies.c: EXPORT_SYMBOL(jiffies)
 */
static char ksym_name[KSYM_NAME_LEN] = "jiffies";

static int __init s_module_init(void)
{
	/**
	 * NOTE: __symbol_get() can only get EXPORT_SYMBOL_GPL()
	 * err: failing symbol_get of non-GPLONLY symbol jiffies
	 */
	void *addr = __symbol_get(ksym_name);
	if (!addr)
		return -ENXIO;
	printk(KERN_INFO "__symbol_get(%s) success\n", ksym_name);
	return 0;
}

static void __exit s_module_exit(void)
{
	__symbol_put(ksym_name);
	printk(KERN_INFO "__symbol_put(%s) success\n", ksym_name);
}

module_init(s_module_init);
module_exit(s_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("test symbol get/put");
