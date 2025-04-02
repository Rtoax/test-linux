#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

static long size = 1024 * 1024;
module_param(size, long, 0660);

static int __init mod_init(void)
{
	char *mem;

	mem = vmalloc(size);
	if (mem) {
		printk(KERN_INFO "Allocated vmalloc area of size: %zu\n", size);
	} else {
		printk(KERN_ERR "Failed to allocate vmalloc area\n");
		return -ENOMEM;
	}

	if (mem) {
		vfree(mem);
		printk(KERN_INFO "Freed vmalloc area\n");
	}

	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
