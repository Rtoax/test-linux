#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *writer_task;
static struct task_struct *task[2];

int writer(void *data)
{
	while (!kthread_should_stop()) {
		smp_store_release(&writer_task, current);
		schedule();
	}
	return 0;
}

int reader(void *data)
{
	while (!kthread_should_stop()) {
		struct task_struct *writer = smp_load_acquire(&writer_task);
		printk(KERN_INFO "Writer %s\n", writer->comm);
		msleep(100);
		schedule();
	}
	return 0;
}

static int kernel_init(void)
{
	printk(KERN_INFO "kthread init.\n");
	task[0] = kthread_run(&writer, NULL, "rtoax-writer");
	task[1] = kthread_run(&reader, NULL, "rtoax-reader");
	return 0;
}

static void kernel_exit(void)
{
	kthread_stop(task[0]);
	kthread_stop(task[1]);
	printk(KERN_INFO "Exit\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
