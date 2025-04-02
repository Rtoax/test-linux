#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

static int __init mod_init(void)
{
	printk("vmalloc_base = 0x%lx\n", vmalloc_base);
	printk("vmemmap_base = 0x%lx\n", vmemmap_base);
	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
