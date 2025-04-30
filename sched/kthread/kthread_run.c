#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>


static struct task_struct *task;

static char *g_message = "Hello from MyThread!";

static int thread_function(void *data)
{
	u64 count = 0;
	printk(KERN_INFO "KThread entry %s\n", (char *)data);

	while (!kthread_should_stop()) {
		msleep_interruptible(1000);
		printk(KERN_INFO "%s count %lld\n", current->comm, count++);
		schedule();
	}

	printk(KERN_INFO "MyThread says goodbye\n");
	return 0;
}

static int kernel_init(void)
{
	printk(KERN_INFO "mykthread init.\n");
	task = kthread_run(&thread_function, (void *)g_message, "rong%s", "tao");
	return task ? 0 : -EINVAL;
}

static void kernel_exit(void)
{
	kthread_stop(task);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
