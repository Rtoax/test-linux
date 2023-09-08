#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/version.h>


int init_test(void)
{
	struct task_struct *task;

	rcu_read_lock();
	for_each_process(task)
		printk(KERN_INFO "***RTOAX %s [%d] parent %s\n",
				task->comm, task->pid, task->parent->comm);
	rcu_read_unlock();
	/* Don't insmod success, only print */
	return -1;
}

void cleanup_test(void)
{
	return;
}

module_init(init_test);
module_exit(cleanup_test);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
