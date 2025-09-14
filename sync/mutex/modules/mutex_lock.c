#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mutex.h>

#define NR_KTHREAD_CAL 3
#define NR_COUNT   10000

/* +1: a printer thread */
struct task_struct *task[NR_KTHREAD_CAL + 1];

static unsigned long my_sum = 0;
static DEFINE_MUTEX(my_mutexlock);

int cal_thread(void *data)
{
	int nr_inc = NR_COUNT;

	while (!kthread_should_stop()) {
		if (nr_inc <= 0) {
			msleep_interruptible(1000);
			printk("kthread sleep.\n");
			continue;
		}

		mutex_lock(&my_mutexlock);
		my_sum++;
		nr_inc--;
		if (!nr_inc) {
			mutex_unlock(&my_mutexlock);
			continue;
		}
		mutex_unlock(&my_mutexlock);

		schedule();
	}

	printk(KERN_INFO "thread done, sum = %ld\n", my_sum);
	return 0;
}

int print_thread(void *data)
{
	while (!kthread_should_stop()) {
		/**
		 * TODO: Use mutex_optimistic_spin()
		 */
		mutex_lock(&my_mutexlock);
		printk(KERN_INFO "SUM = %ld\n", my_sum);
		mutex_unlock(&my_mutexlock);
		msleep(1000);
		schedule();
	}
	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	task[NR_KTHREAD_CAL] = kthread_run(&print_thread, NULL, "rtoax-printer");

	for (itask = 0; itask < NR_KTHREAD_CAL; itask++)
		task[itask] = kthread_run(&cal_thread, NULL, "rtoax-%d", itask);

	return 0;
}

static void kernel_exit(void)
{
	int itask;
	for (itask = 0; itask < NR_KTHREAD_CAL; itask++)
		kthread_stop(task[itask]);
	kthread_stop(task[NR_KTHREAD_CAL]);

	if (my_sum != NR_KTHREAD_CAL * NR_COUNT)
		printk(KERN_ERR "Exit, Wrong SUM value %ld, expect %ld\n",
			my_sum, NR_KTHREAD_CAL * NR_COUNT);
	else
		printk(KERN_INFO "Exit, SUM = %ld\n", my_sum);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
