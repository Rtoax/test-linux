#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>

static int kernel_init(void)
{
	printk(KERN_INFO "numa_node_id %d\n", numa_node_id());
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
