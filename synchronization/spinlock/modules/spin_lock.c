/**
 *	File	spin_lock.c
 *	Time	2021.11.11
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

#define NR_KTHREAD 3
#define NR_COUNT   10000

struct task_struct *task[NR_KTHREAD];

static unsigned long my_sum = 0;
static spinlock_t my_spinlock;

int thread_function(void *data)
{
	int nr_inc = NR_COUNT;

	while (!kthread_should_stop()) {

		if (nr_inc <= 0) {
			msleep_interruptible(1000);
			printk("kthread sleep.\n");
			continue;
		}

		spin_lock(&my_spinlock);
		my_sum++;
		nr_inc--;
		if (!nr_inc) {
			spin_unlock(&my_spinlock);
			continue;
		}
		spin_unlock(&my_spinlock);

		schedule();
	}

	printk(KERN_INFO "thread done, sum = %ld\n", my_sum);
	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	spin_lock_init(&my_spinlock);

	for (itask = 0; itask < NR_KTHREAD; itask++)
		task[itask] = kthread_run(&thread_function, NULL, "rtoax-%d", itask);

	return 0;
}

static void kernel_exit(void)
{
	int itask;
	for (itask = 0; itask < NR_KTHREAD; itask++)
		kthread_stop(task[itask]);

	if (my_sum != NR_KTHREAD * NR_COUNT)
		printk(KERN_ERR "Exit, Wrong SUM value %ld, expect %ld\n",
			my_sum, NR_KTHREAD * NR_COUNT);
	else
		printk(KERN_INFO "Exit, SUM = %ld\n", my_sum);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
