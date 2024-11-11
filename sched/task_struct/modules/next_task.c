// SPDX-License-Identifier: GPL-3.0
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/version.h>


static int init_test(void)
{
	struct task_struct *task = &init_task;

	rcu_read_lock();
	do {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
		if (task->__state == TASK_RUNNING)
#else
		if (task->state == TASK_RUNNING)
#endif
		printk(KERN_INFO "***RTOAX %s [%d] parent %s\n",
			task->comm, task->pid, task->parent->comm);
	} while ((task = next_task(task)) != &init_task);

	rcu_read_unlock();

	/* Don't insmod success, only print */
	return -1;
}

module_init(init_test);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
