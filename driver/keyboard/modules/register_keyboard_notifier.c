#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/keyboard.h>

static int callback(struct notifier_block *nb, unsigned long action, void *data)
{
	struct keyboard_notifier_param *param = data;
	printk(KERN_INFO "value %d, down %d, shift %d\n",
		param->value, param->down, param->shift);
	return 0;
}

static struct notifier_block nb = {
	.notifier_call = callback,
};

static int __init s_module_init(void)
{
	register_keyboard_notifier(&nb);
	return 0;
}

static void __exit s_module_exit(void)
{
	unregister_keyboard_notifier(&nb);
}

module_init(s_module_init);
module_exit(s_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("Keyboard notifier");
