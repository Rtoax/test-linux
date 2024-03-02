/**
 *	File	zone.c
 *	Time	2021.11.05
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>

#if 0
static void for_each_node_test(void)
{
	struct pglist_data *pgdat;
	//can't use in module
	for_each_online_pgdat(pgdat) {
		pr_info("nr_zones = %d\n", pgdat->nr_zones);
	}
}
#endif

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    return 0;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
