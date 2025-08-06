#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

#define SIZE 8

/**
 * Format: array_int=1,2,3,4,5,6,7,8
 */
static int array_int[SIZE];
static int count;
module_param_array(array_int, int, &count, 0660);

static int ok = 0;
module_param(ok, int, 0660);

static int simple_init(void)
{
	int i;
	for (i = 0; i < count; i++)
		printk(KERN_WARNING "array_int[%d]=%d\n", i, array_int[i]);

	if (ok)
		return 0;

	return -EINVAL;
}

module_init(simple_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
