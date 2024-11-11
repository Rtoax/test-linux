/**
 * File listtasks.c
 * Time 2021.11.03
 * Author Rong Tao <rtoax@foxmail.com> modify from Slava Imameev
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/init_task.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");

static const char *state_to_string(long state)
{
	switch (state) {
	case TASK_RUNNING: return "rinning";
	case TASK_INTERRUPTIBLE: return "irqable";
	case TASK_UNINTERRUPTIBLE: return "unirqable";
	case __TASK_STOPPED: return "stoped";
	case __TASK_TRACED: return "traced";
	case TASK_DEAD: return "dead";
	case TASK_WAKEKILL: return "wakekill";
	case TASK_WAKING: return "waking";
	case TASK_PARKED: return "parked";
	case TASK_NOLOAD: return "noload";
	default: return "UNKNOWN";
	}
}

static void list_from_task(struct task_struct *task)
{
	unsigned long count = 0;
	unsigned long cnt_uninterruptible = 0;
	unsigned long cnt_interruptible = 0;
	unsigned long cnt_running = 0;

	/**
	 * tasklist_lock is not exported anymore, use RCU as p->tasks
	 * is updated wth list_add_tail_rcu(), see copy_process(),
	 * you can use list_for_each_entry_rcu() instead the explicit
	 * RCU list traversing code below
	 */
	rcu_read_lock();
	struct task_struct* p = task;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 14, 0)
# define STATE state
#else
# define STATE __state
#endif
	printk(KERN_INFO "%-17s %-6s %-6s %-3s %-4s %-4s %-20s\n",
		"Name", "PID", "TGID", "Pri","PriS","PriN", "State");
	do {
		struct list_head *next;
		long state = p->STATE;
		printk(KERN_INFO "%-17s %-6d %-6d %-3d %-4d %-4d %-2ld(-%9s)\n",
			p->comm, p->pid, p->tgid,
			p->prio, p->static_prio, p->normal_prio,
			state, state_to_string(state));

		if (p->STATE == TASK_UNINTERRUPTIBLE)
			cnt_uninterruptible++;
		if (p->STATE == TASK_INTERRUPTIBLE)
			cnt_interruptible++;
		if (p->STATE == TASK_RUNNING)
			cnt_running++;
		count++;

		next = rcu_dereference(p->tasks.next);
		p = list_entry(next, struct task_struct, tasks);
	} while (p != task);

	rcu_read_unlock();

	printk("Total process number is %ld\n", count);
	printk("Uninterruptible %ld\n", cnt_uninterruptible);
	printk("  Interruptible %ld\n", cnt_interruptible);
	printk("        Running %ld\n", cnt_running);
}

static void list_tasks(void)
{
	list_from_task(&init_task);
}

static int __init listtask_init(void)
{
	printk(KERN_INFO "Hi from init\n");

	list_tasks();

	return -EINVAL;
}

module_init(listtask_init)
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
