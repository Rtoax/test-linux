#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/bug.h>
#include <linux/kernel.h>
#include <linux/atomic.h>
#include <linux/module.h>


static __init int test_atomics_init(void)
{
	atomic_t a;
	atomic_set(&a, 0xff00);
	u32 u = atomic_fetch_or_acquire(1 << 5, &a);
	pr_info("%x %x\n", u, atomic_read(&a));

	/* insmod failed on purpose */
	return -1;
}

static __exit void test_atomics_exit(void) {}

module_init(test_atomics_init);
module_exit(test_atomics_exit);

MODULE_LICENSE("GPL");

