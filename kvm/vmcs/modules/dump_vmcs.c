#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

typedef void (*dump_vmcs)(void);

/**
 * FIXME: get, not constant
 * Need kvm_intel.dump_invalid_vmcs=1 like
 * $ sudo modprobe kvm_intel dump_invalid_vmcs=1
 */
dump_vmcs dump = (dump_vmcs)0xffffffffc19c8810;

static int kernel_init(void)
{
	printk(KERN_INFO "call dump_vmcs().\n");
	dump();
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
