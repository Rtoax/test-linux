#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define NR_KTHREAD 3

struct task_struct *task[NR_KTHREAD];
char *THREAD_MESSAGE = "Hello from MyThread!";

static atomic_t my_count = ATOMIC_INIT(0);

int thread_function(void *data)
{
	u64 count = 0;
	printk(KERN_INFO "KThread entry %s\n", (char*) data);

	while (!kthread_should_stop()) {
		msleep_interruptible(100);
		printk(KERN_INFO "Count %lld, total %d\n", count++, atomic_read(&my_count));
		atomic_inc(&my_count);

		/* Condition is established if kthread_park() */
		if (kthread_should_park()) {
			printk(KERN_DEBUG "Parked\n");
			/* Wait kthread_unpark() or kthread_stop() */
			kthread_parkme();
			printk(KERN_DEBUG "Unparked\n");
		}
		schedule();
	}

	printk(KERN_INFO "MyThread says goodbye\n");
	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	for (itask = 0; itask < NR_KTHREAD; itask++)
		task[itask] = kthread_run(&thread_function, (void *)THREAD_MESSAGE, "rtoax-%d", itask);

	msleep(100);
	for (itask = 0; itask < NR_KTHREAD; itask++)
		kthread_park(task[itask]);

	msleep(100);
	for (itask = 0; itask < NR_KTHREAD; itask++)
		kthread_unpark(task[itask]);

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
