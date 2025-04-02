#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/slab.h>

static long size = 1024 * 1024;
module_param(size, long, 0660);

static int __init mod_init(void)
{
	char *mem;

	mem = kmalloc(size, GFP_KERNEL);
	if (mem) {
		printk(KERN_INFO "Allocated kmalloc area of size: %zu\n", size);
	} else {
		printk(KERN_ERR "Failed to allocate kmalloc area\n");
		return -ENOMEM;
	}

	if (mem) {
		kfree(mem);
		printk(KERN_INFO "Freed kmalloc area\n");
	}

	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
