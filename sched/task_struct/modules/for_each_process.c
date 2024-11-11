// SPDX-License-Identifier: GPL-3.0
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/version.h>


static void print_task(struct task_struct *task)
{
	printk(KERN_INFO "***RTOAX %s [%d] parent %s\n",
		task->comm, task->pid, task->parent->comm);
}

static int init_test(void)
{
	struct task_struct *task, *thread;

	rcu_read_lock();
	for_each_process(task) {
		print_task(task);
		rcu_read_lock();
		for_each_thread(task, thread) {
			task_lock(thread);
			print_task(thread);
			task_unlock(thread);
		}
		rcu_read_unlock();
	}
	rcu_read_unlock();
	/* Don't insmod success, only print */
	return -1;
}

module_init(init_test);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
