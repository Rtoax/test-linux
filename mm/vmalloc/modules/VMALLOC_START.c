#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/sizes.h>
#include <linux/io.h>
#include <asm/page.h>
#ifdef CONFIG_MIPS
#include <asm/bootinfo.h>
#endif

struct foo {
	unsigned int bar;
};

static struct foo *foo;

static int __init mod_init(void)
{
	phys_addr_t pa;
	void *va;

	va = (void *)VMALLOC_START;
	pa = virt_to_phys(va);

	pr_info("PA: %pa for VA: 0x%lx(VMALLOC_START)\n", &pa, (unsigned long)va);

	va = (void *)VMALLOC_END;
	pa = virt_to_phys(va);

	pr_info("PA: %pa for VA: 0x%lx(VMALLOC_END)\n", &pa, (unsigned long)va);

	foo = kzalloc(sizeof(*foo), GFP_KERNEL);
	if (!foo)
		return -ENOMEM;

	pa = virt_to_phys(foo);
	va = foo;
	pr_info("PA: %pa for VA: 0x%lx(kzalloc)\n", &pa, (unsigned long)va);

	kfree(foo);

	foo = vmalloc(sizeof(*foo));
	if (!foo)
		return -ENOMEM;

	pa = virt_to_phys(foo);
	va = foo;
	pr_info("PA: %pa for VA: 0x%lx(vmalloc)\n", &pa, (unsigned long)va);

	vfree(foo);

	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test module for CONFIG_DEBUG_VIRTUAL");
