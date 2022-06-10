/**
 *	File	static_key.c
 *	Time	2021.11.10
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jump_label.h>

static struct static_key key_true = STATIC_KEY_INIT_TRUE;
static struct static_key key_false = STATIC_KEY_INIT_FALSE;

static void test_key_true(void)
{
	if(static_key_true(&key_true)) {
		printk("TRUE: do unlikely thing, count = %d\n", static_key_count(&key_true));
	} else {
		printk("TRUE: do likely thing, count = %d\n", static_key_count(&key_true));
	}
}

static void test_key_false(void)
{
	if(static_key_false(&key_false)) {
		printk("FALSE: do unlikely thing, count = %d\n", static_key_count(&key_false));
	} else {
		printk("FALSE: do likely thing, count = %d\n", static_key_count(&key_false));
	}
}

static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");

	test_key_true();
	test_key_false();

	static_key_slow_inc(&key_false);
	static_key_slow_dec(&key_true);

	test_key_true();
	test_key_false();

	static_key_enable(&key_true);
	static_key_disable(&key_false);

	test_key_true();
	test_key_false();

	return 0;
}

static void kernel_exit(void)
{	
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
