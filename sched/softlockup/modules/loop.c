#include <linux/module.h>
#include <linux/kthread.h>


struct task_struct *kt;

/**
 * If CONFIG_PREEMPT=y, this infinite loop will not cause soft lockup,
 * otherwise, it'll cause soft lockup.
 */
static int loop_func(void *arg)
{
	int i = 0;
	while (!kthread_should_stop()) {
		i++;
	}
	return 0;
}

static int __init init_loop(void)
{
	kt = kthread_run(loop_func, NULL, "loop_thread");
	if (IS_ERR(kt)) {
		return -1;
	}

	return 0;
}

static void __exit exit_loop(void)
{
	kthread_stop(kt);
}

module_init(init_loop);
module_exit(exit_loop);
MODULE_LICENSE("GPL");
