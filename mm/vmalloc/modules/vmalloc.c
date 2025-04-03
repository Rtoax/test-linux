#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

static long size = 1024 * 1024;
module_param(size, long, 0660);

static char *mem;

static int __init mod_init(void)
{
	int i;

	mem = vmalloc(size);
	if (!mem) {
		printk(KERN_ERR "Failed to allocate vmalloc area\n");
		return -ENOMEM;
	}

	printk(KERN_INFO "Allocated vmalloc area of size: %zu\n", size);

	/**
	 * Page fault
	 *
	 * Initial Allocation: When memory is initially requested by vmalloc,
	 * it is allocated in a virtually contiguous manner. However, this
	 * memory is not necessarily physically contiguous, and the pages
	 * are mapped on demand.
	 *
	 * Page Faults on Access: When the allocated memory is first accessed,
	 * page faults will occur if the pages have not yet been mapped to
	 * physical memory. These page faults will trigger the operating
	 * system to map the required physical pages to the virtual addresses.
	 *
	 * Subsequent Accesses: After the initial access and mapping,
	 * subsequent accesses to the same memory should not cause page
	 * faults, as the pages would already be mapped to physical memory.
	 *
	 * Swapping: If the system is under memory pressure and the allocated
	 * pages are swapped out to disk, accessing those pages again will
	 * cause page faults, as the pages need to be brought back into
	 * physical memory.
	 */
	for (i = 0; i < size; i += 1UL << PAGE_SHIFT)
		mem[i] = 'a';

	vfree(mem);
	printk(KERN_INFO "Freed vmalloc area\n");

	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
