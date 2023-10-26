#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/bug.h>
#include <linux/kernel.h>
#include <linux/atomic.h>
#include <linux/module.h>


static __init int test_atomics_init(void)
{
	int ret;
	atomic_t a;
	u32 val = 0;

	atomic_set(&a, 0xff00);

	/**
	 * atomic_try_cmpxchg_relaxed() is same
	 */
	ret = atomic_try_cmpxchg_acquire(&a, &val, 1 << 3);
	pr_info("%d %x %x\n", ret, val, atomic_read(&a));

	ret = atomic_try_cmpxchg_acquire(&a, &val, 1 << 3);
	pr_info("%d %x %x\n", ret, val, atomic_read(&a));

	/* insmod failed on purpose */
	return -1;
}

static __exit void test_atomics_exit(void) {}

module_init(test_atomics_init);
module_exit(test_atomics_exit);

MODULE_LICENSE("GPL");

