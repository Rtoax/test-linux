#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

static int sz = 4;
module_param(sz, int, 0660);

bool __weak copy_from_kernel_nofault_allowed(const void *unsafe_src,
					     size_t size)
{
	return true;
}

/* see linux/mm/maccess.c */
static long strncpy_from_kernel_nofault_2(char *dst, const void *unsafe_addr,
					  long count)
{
	const void *src = unsafe_addr;

	if (unlikely(count <= 0))
		return 0;
	if (!copy_from_kernel_nofault_allowed(unsafe_addr, count))
		return -ERANGE;

	pagefault_disable();
	do {
		__get_kernel_nofault(dst, src, u8, Efault);
		dst++;
		src++;
	} while (dst[-1] && src - unsafe_addr < count);
	pagefault_enable();

	dst[-1] = '\0';
	return src - unsafe_addr;
Efault:
	pagefault_enable();
	dst[0] = '\0';
	return -EFAULT;
}

static int __init kern_init(void)
{
	int err;
	char dst[32] = { "abc" };

	printk("test strncpy_from_kernel_nofault()\n");

	err = strncpy_from_kernel_nofault_2(dst + 3, "1234567890", sz);
	printk("dst %s, sz %d, err %d\n", dst, sz, err);

	return -EINVAL;
}

module_init(kern_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
