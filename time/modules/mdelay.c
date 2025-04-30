#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

static struct task_struct *task;

static int test_thread(void *data)
{
	/* Busy wait 20 seconds */
	mdelay(20000);
	return 0;
}

static int __init test_init(void)
{
	task = kthread_run(test_thread, NULL, "test_mdelay");
	return 0;
}

static void __exit test_exit(void)
{
	kthread_stop(task);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
