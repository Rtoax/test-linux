#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

typedef void (*dump_vmcs)(void);

static ulong addr = 0xffffffffc1abf810UL;
module_param(addr, ulong, 0660);

/**
 * Need kvm_intel.dump_invalid_vmcs=1 like
 * $ sudo modprobe kvm_intel dump_invalid_vmcs=1
 */
dump_vmcs dump = NULL;

static int kernel_init(void)
{
	printk(KERN_INFO "call dump_vmcs().\n");
	dump = (dump_vmcs)addr;
	if (dump)
		dump();
	else
		printk(KERN_ERR "Need param addr=[ADDR]");
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
