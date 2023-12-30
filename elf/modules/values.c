#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <asm/elf.h>


static int __init kernel_init(void)
{
#ifdef ELF_ET_DYN_BASE
	printk("ELF_ET_DYN_BASE = %#016lx\n", ELF_ET_DYN_BASE);
#endif
	/* Insmod failed by default. */
	return -1;
}

static void __exit kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("xxx");
