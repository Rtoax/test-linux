#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/kprobes.h>

typedef void (*dump_vmcs)(void);
typedef unsigned long(*kallsymsFn)(const char *);

static ulong addr = 0xffffffffc1abf810UL;
module_param(addr, ulong, 0660);

static kallsymsFn kallsyms = NULL;

static unsigned long my_kallsyms_lookup_name(const char *name)
{
	return kallsyms(name);
}

static int init_kallsyms(void)
{
	struct kprobe kp = {0};
	int ret = 0;
	kp.symbol_name = "kallsyms_lookup_name";
	ret = register_kprobe(&kp);
	if (ret < 0)
		return ret;
	kallsyms = (kallsymsFn)kp.addr;
	unregister_kprobe(&kp);
	return ret;
}

/**
 * Need kvm_intel.dump_invalid_vmcs=1 like
 * $ sudo modprobe kvm_intel dump_invalid_vmcs=1
 */
dump_vmcs dump = NULL;

static int kernel_init(void)
{
	printk(KERN_INFO "====== dump_vmcs ======\n");

	init_kallsyms();

	addr = my_kallsyms_lookup_name("dump_vmcs");

	printk(KERN_INFO "dump_vmcs = %lx\n", addr);
	printk(KERN_INFO "see also $ sudo grep -w dump_vmcs /proc/kallsyms\n");

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
