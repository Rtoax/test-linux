/**
 *	find pid namespace struct by PID
 *	
 *	Author	Rong Tao <rtoax@foxmail.com>
 *	Time	2022-03-24
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>

static int test_task_pid = 1;
module_param(test_task_pid, int, 0660);

static int __init find_pidtest_init(void)
{
	int PID = test_task_pid;
	bool has_task;
	struct pid *pid;
	struct task_struct *task, *child_reaper;
	struct pid_namespace *pid_ns;

	printk("find_pidtest_init.\n");

	pid = find_get_pid(PID);
	if(!pid) {
		printk("Not exist PID %d, level = %d\n", PID, pid->level);
		return -1;
	}

	has_task = pid_has_task(pid, PIDTYPE_PID);
	if(has_task) {
		printk("PID %d has task.\n", PID);
	}

	task = pid_task(pid, PIDTYPE_PID);
	if(task) {
		printk("PID %d task name %s\n", PID, task->comm);
	}
	
	task = get_pid_task(pid, PIDTYPE_PID);
	if(task) {
		printk("PID %d task name %s\n", PID, task->comm);
	}

	pid_ns = task_active_pid_ns(task);
	if (pid_ns) {
		child_reaper = pid_ns->child_reaper;
		printk("PID %d COMM %s pid_allocated = 0x%08x, level = %d, reaper pid = %d\n",
		 PID, task->comm, pid_ns->pid_allocated, pid_ns->level, child_reaper->pid);
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
