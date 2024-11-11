// SPDX-License-Identifier: GPL-3.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/pid.h>


static int __init find_pidtest_init(void)
{
	int PID = 1;
	struct pid *pid;
	struct task_struct *task;
	bool has_task;

	printk("find_pidtest_init.\n");

	pid = find_get_pid(PID);
	if (!pid) {
		printk("Not exist PID %d\n", PID);
		return -1;
	}

	has_task = pid_has_task(pid, PIDTYPE_PID);
	if (has_task) {
		printk("PID %d has task.\n", PID);
	}

	task = pid_task(pid, PIDTYPE_PID);
	if (task) {
		printk("PID %d task name %s\n", PID, task->comm);
	}
	
	task = get_pid_task(pid, PIDTYPE_PID);
	if (task) {
		printk("PID %d task name %s\n", PID, task->comm);
	}
	return 0;
}

static void __exit find_pidtest_exit(void)
{
	printk("find_pidtest_exit.\n");
}

module_init(find_pidtest_init);
module_exit(find_pidtest_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
