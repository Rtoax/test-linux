/**
 *	File	kthread.c
 *	Time	2021.11.03
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

struct task_struct *task;
char *THREAD_MESSAGE = "Hello from MyThread!";

void print_count(u64 count)
{
	printk(KERN_INFO "MyKthread count %lld\n", count++);
}

int thread_function(void *data)
{
	u64 count = 0;

	printk(KERN_INFO "KThread entry %s\n", (char*) data);

	while (!kthread_should_stop()) {
		msleep_interruptible(1000);
		print_count(count++);
		schedule();
	}

	printk(KERN_INFO "MyThread says goodbye\n");
	return 0;
}

static int kernel_init(void)
{
	printk(KERN_INFO "mykthread init.\n");
	task = kthread_run(&thread_function, (void *)THREAD_MESSAGE, "MyThread");
	return 0;
}

static void kernel_exit(void)
{
	kthread_stop(task);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
