#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>

/* Example 0 */
static int num0 = 0;
module_param(num0, int, 0660);

/* Example 1 */
static int set_num1(const char *val, const struct kernel_param *kp)
{
	int n = 0, ret;
	ret = kstrtoint(val, 10, &n);
	if (ret != 0 || n < 1 || n > 32)
		return -EINVAL;
	return param_set_int(val, kp);
}

static const struct kernel_param_ops param_ops = {
	.set = set_num1,
	.get = param_get_int,
};

static int num1 = 100;
module_param_cb(num1, &param_ops, &num1, 0664);

static long num3 = 0;
module_param(num3, long, 0660);

static int simple_init(void)
{
	printk(KERN_WARNING "num0=%d num1=%d, num3=%ld\n", num0, num1, num3);
	return -EINVAL;
}

module_init(simple_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
