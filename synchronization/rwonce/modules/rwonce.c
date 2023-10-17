#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <asm/barrier.h>
#include <asm-generic/rwonce.h>


struct task_struct *tasks[2];

static int x = 1;
static int a[2];

static int rwonce = 1;
module_param(rwonce, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(rwonce, "Switch off/on READ and WRITE _ONCE");

static int thread1(void *data)
{
	while (!kthread_should_stop()) {
		if (rwonce)
			WRITE_ONCE(x, x + 1);
		else
			x++;
		schedule();
	}
	printk(KERN_INFO "Thread1: exit.\n");
	return 0;
}

static int thread2(void *data)
{
	while (!kthread_should_stop()) {
		if (rwonce) {
			a[0] = READ_ONCE(x);
			a[1] = READ_ONCE(x);
		} else {
			a[0] = x;
			a[1] = x;
		}

		/* TODO: How to check rwonce? */
		if (a[0] > a[1])
			printk(KERN_ERR "a[0] should never bigger than a[1].\n");

		schedule();
	}

	printk(KERN_INFO "Thread2: exit.\n");
	return 0;
}

static int kernel_init(void)
{
	printk(KERN_INFO "rwonce test init with rwonce = %d.\n", rwonce);

	tasks[0] = kthread_run(&thread1, NULL, "rtoax-task1");
	tasks[1] = kthread_run(&thread2, NULL, "rtoax-task2");

	return 0;
}

static void kernel_exit(void)
{
	int i;

	for (i = 0; i < 2; i++) {
		kthread_stop(tasks[i]);
	}
	printk(KERN_INFO "rwonce test exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
