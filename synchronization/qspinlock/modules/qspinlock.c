#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <asm-generic/qspinlock.h>

#include "mask.h"


#define NR_SPINNER 3
#define NR_PRINTER 1
#define NR_KTHREAD (NR_SPINNER + NR_PRINTER)
#define NR_COUNT   1000000

struct task_struct *task[NR_KTHREAD];

static unsigned long my_sum = 0;

#if 1
static struct qspinlock qspinlock = __ARCH_SPIN_LOCK_UNLOCKED;
#else
/* Wrong sum */
#define queued_spin_lock(a) do {} while (0)
#define queued_spin_unlock(a) do {} while (0)
#endif

int thread_function(void *data)
{
	int nr_inc = NR_COUNT;

	while (!kthread_should_stop()) {

		if (nr_inc <= 0) {
			msleep_interruptible(1000);
			continue;
		}

		queued_spin_lock(&qspinlock);
		my_sum++;
		nr_inc--;
		if (!nr_inc) {
			queued_spin_unlock(&qspinlock);
			continue;
		}
		queued_spin_unlock(&qspinlock);

		schedule();
	}

	printk(KERN_INFO "thread done, sum = %ld\n", my_sum);
	return 0;
}

int thread_printer(void *data)
{
	while (!kthread_should_stop()) {
		u32 val = atomic_read(&qspinlock.val);
		if (val)
			printk(KERN_INFO "qspinlock val = %s\n", binary32_unsafe(val));
		schedule();
	}

	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	/* Start printer first */
	for (itask = 0; itask < NR_PRINTER; itask++)
		task[itask] = kthread_run(&thread_printer, NULL, "rtoax-%d-printer", itask);

	for (itask = NR_PRINTER; itask < NR_KTHREAD; itask++)
		task[itask] = kthread_run(&thread_function, NULL, "rtoax-%d-spinner", itask);

	return 0;
}

static void kernel_exit(void)
{
	int itask;
	for (itask = 0; itask < NR_KTHREAD; itask++)
		kthread_stop(task[itask]);

	if (my_sum != NR_SPINNER * NR_COUNT)
		printk(KERN_ERR "Exit, Wrong SUM value %ld, expect %d\n",
			my_sum, NR_SPINNER * NR_COUNT);
	else
		printk(KERN_INFO "Exit, SUM = %ld\n", my_sum);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
