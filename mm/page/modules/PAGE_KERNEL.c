#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <linux/mmdebug.h>
#include <asm/pgtable.h>
#include <linux/pgtable.h>


static int kernel_init(void)
{
	printk("PAGE_KERNEL = 0x%lx\n", PAGE_KERNEL);
#ifdef PROT_DEFAULT
	printk("PROT_DEFAULT = 0x%llx\n", PROT_DEFAULT);
#endif
#ifdef PROT_NORMAL
	printk("PROT_NORMAL = 0x%llx\n", PROT_NORMAL);
#endif
#ifdef __PAGE_KERNEL
	printk("__PAGE_KERNEL = 0x%lx\n", __PAGE_KERNEL);
#endif
	return -1;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
