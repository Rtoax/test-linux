#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/completion.h>


struct task_struct *tasks[2];
static DECLARE_COMPLETION(cpu_running);


static int thread1(void *data)
{
	const int ms = 1000;
	while (!kthread_should_stop()) {
		printk(KERN_INFO "Thread1: Sleep %d ms\n", ms);
		msleep(ms);
		complete(&cpu_running);
		schedule();
	}
	printk(KERN_INFO "Thread1: exit.\n");

	return 0;
}

static int thread2(void *data)
{
	printk(KERN_INFO "Thread2: waiting thread1 to done...\n");
	wait_for_completion(&cpu_running);
	printk(KERN_INFO "Thread2: thread1 completion.\n");

	while (!kthread_should_stop())
		schedule();

	printk(KERN_INFO "Thread2: exit.\n");
	return 0;
}

static int kernel_init(void)
{
	init_completion(&cpu_running);

	tasks[0] = kthread_run(&thread1, NULL, "rtoax-worker");
	tasks[1] = kthread_run(&thread2, NULL, "rtoax-waiter");

	return 0;
}

static void kernel_exit(void)
{
	int i;

	complete_all(&cpu_running);

	for (i = 0; i < 2; i++) {
		kthread_stop(tasks[i]);
	}
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
