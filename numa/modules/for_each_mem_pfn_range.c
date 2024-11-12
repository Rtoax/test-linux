#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>
#include <linux/memblock.h>

static int kernel_init(void)
{
	unsigned long start_pfn, end_pfn;
	int i, nid;

#if 0
	pr_info("Early memory node ranges\n");
	for_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, &nid) {
		pr_info("  node %3d: [mem %#018Lx-%#018Lx]\n", nid,
				(u64)start_pfn << PAGE_SHIFT,
				((u64)end_pfn << PAGE_SHIFT) - 1);
	}
#endif

	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
