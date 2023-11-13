#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jump_label.h>

static struct static_key key_true = STATIC_KEY_INIT_TRUE;
static struct static_key key_false = STATIC_KEY_INIT_FALSE;

static DEFINE_STATIC_KEY_FALSE(key_false_2);

static void test_key(void)
{
	if(static_key_true(&key_true)) {
		printk("TRUE: do unlikely thing, count = %d\n", static_key_count(&key_true));
	} else {
		printk("TRUE: do likely thing, count = %d\n", static_key_count(&key_true));
	}

	if(static_key_false(&key_false)) {
		printk("FALSE: do unlikely thing, count = %d\n", static_key_count(&key_false));
	} else {
		printk("FALSE: do likely thing, count = %d\n", static_key_count(&key_false));
	}

	if(static_branch_likely(&key_false_2)) {
		printk("FALSE: do likely thing\n");
	} else {
		printk("FALSE: do unlikely thing\n");
	}
}

static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");

	test_key();

	static_key_slow_inc(&key_false);
	static_key_slow_dec(&key_true);
	static_branch_enable(&key_false_2);

	test_key();

	static_key_enable(&key_true);
	static_key_disable(&key_false);
	static_branch_disable(&key_false_2);

	test_key();

	/* insmod failed on purpose */
	return -1;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
