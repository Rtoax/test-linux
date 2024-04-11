#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/timekeeping.h>


typedef void (*fn_ts64_t)(struct timespec64 *);

static inline unsigned long nsecs64(fn_ts64_t fn)
{
	struct timespec64 ts;
	fn(&ts);
	return (ts.tv_sec * 1E9 + ts.tv_nsec);
}

static void test(char *name, fn_ts64_t fn)
{
	unsigned long start, end, cnt;

	cnt = 0;
	start = end = nsecs64(fn);
	/* 5ms */
	while (end - start < 5000000) {
		cnt++;
		end = nsecs64(fn);
	}
	printk(KERN_INFO "%-48s %-16ld %-16ld\n", name, end - start, cnt);
}

static int kernel_init(void)
{
	printk(KERN_INFO "Testing CLOCK accuracy.\n");
	test("REALTIME", ktime_get_real_ts64);
	test("REALTIME_COARSE", ktime_get_coarse_real_ts64);
	return -1;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
