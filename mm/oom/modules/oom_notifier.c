/**
 * oom_notifier.c - register OOM notifier
 *
 * 2023-09-08	Rong Tao	Create this
 */
#include <linux/module.h>
#include <linux/oom.h>

static int notifier_fn(struct notifier_block *nb, unsigned long action,
		       void *data)
{
	/* TODO */
	return 0;
}

struct notifier_block nb = {
	.notifier_call = notifier_fn,
	.priority = 0,
};

static int __init kernel_init(void)
{
	int ret = register_oom_notifier(&nb);
	return ret;
}

static void __exit kernel_exit(void)
{
	unregister_oom_notifier(&nb);
}

module_init(kernel_init);
module_exit(kernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("Register OOM notifier chain");
