// SPDX-License-Identifier: GPL-3.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/pid.h>

static int PID = 1;
module_param(PID, int, 0660);

static int __init find_pidtest_init(void)
{
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

	return -EINVAL;
}

module_init(find_pidtest_init);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
