#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

#define PRINT_ADDR(addr)	printk(KERN_INFO "%-32s %#016x\n", #addr, addr)

static int __init print_init(void)
{
	PRINT_ADDR(CONFIG_PHYSICAL_START);
	PRINT_ADDR(CONFIG_PHYSICAL_ALIGN);

	/* insmod failed in purpose */
	return -1;
}

static void __exit print_exit(void)
{}

MODULE_LICENSE("GPL");
module_init(print_init);
module_exit(print_exit);
