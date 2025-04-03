#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>

static long size = 1024 * 1024;
module_param(size, long, 0660);

static char *mem;

static int __init mod_init(void)
{
	int i;

#ifdef TEST_KMALLOC
#pragma message("test kmalloc()")
	mem = kmalloc(size, GFP_KERNEL);
#else
	mem = vmalloc(size);
#endif
	if (!mem) {
		printk(KERN_ERR "Failed to allocate malloc area\n");
		return -ENOMEM;
	}

	printk(KERN_INFO "Allocated malloc area of size: %zu\n", size);

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

#ifdef TEST_KMALLOC
	kfree(mem);
#else
	vfree(mem);
#endif
	printk(KERN_INFO "Freed malloc area\n");

	return -EINVAL;
}

module_init(mod_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
