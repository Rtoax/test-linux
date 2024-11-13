/**
 * see also __sync_val_compare_and_swap()
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define NR_KTHREAD 3

struct task_struct *task[NR_KTHREAD];
struct task_struct *playtask;

static int thread_function(void *data)
{
	while (!kthread_should_stop()) {
		struct task_struct *task = current;

		/**
		 * cmpxchg(void *ptr, unsigned long old, unsigned long new) {
		 *   if (*ptr == old) {
		 *     *ptr = new;
		 *     return old;
		 *   }
		 *   return *ptr;
		 * }
		 */
		if (likely(cmpxchg(&playtask, task, NULL) == task)) {
			msleep_interruptible(100);
		} else {
			struct task_struct *t = READ_ONCE(playtask);
			printk(KERN_INFO "cmpxchg. task %s, playtask %s\n",
				task->comm, t ? t->comm : "NULL");
		}
		schedule();
		WRITE_ONCE(playtask, task);
	}
	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	WRITE_ONCE(playtask, NULL);

	for (itask = 0; itask < NR_KTHREAD; itask++)
		task[itask] = kthread_run(&thread_function, NULL, "rtoax-%d", itask);

	return 0;
}

static void kernel_exit(void)
{
	int itask;
	for (itask = 0; itask < NR_KTHREAD; itask++)
		kthread_stop(task[itask]);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
