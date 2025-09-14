#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/bug.h>
#include <linux/kernel.h>
#include <linux/atomic.h>
#include <linux/module.h>


static __init int test_atomics_init(void)
{
	u32 val1 = 100;
	u32 val2 = 200;

	u32 ret = xchg_relaxed(&val1, val2);

	/**
	 * ret  = 100
	 * val1 = 200
	 * val2 = 200
	 */
	pr_info("%d %d %d\n", ret, val1, val2);

	/* insmod failed on purpose */
	return -1;
}

static __exit void test_atomics_exit(void) {}

module_init(test_atomics_init);
module_exit(test_atomics_exit);

MODULE_LICENSE("GPL");

