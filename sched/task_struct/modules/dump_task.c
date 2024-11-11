// SPDX-License-Identifier: GPL-3.0
#include <linux/kernel.h>
#include <linux/module.h>
#include <uapi/linux/sched.h>
#include <linux/init_task.h>
#include <linux/init.h>
#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/mm_types.h>
#include <linux/version.h>


static void dump_task(struct task_struct *p)
{
#if 1

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
# define Sfmt "%x"
#else
# define Sfmt "%lx"
#endif 

	printk("pid:%d; state:"Sfmt"; prio:%d; static_prio:%d; parent'pid:%d; count:%d; umask:%d;",
		p->pid,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
		p->__state,
#else
		p->state,
#endif
		p->prio, p->static_prio, (p->parent)->pid,
		atomic_read((&(p->files)->count)), (p->fs)->umask);
		
	if ((p->mm)!=NULL)
		printk("total_vm:%ld;", (p->mm)->total_vm);
#else
	/**
	 * linux-5.10.13 
	 * mm/oom_kill.c/dump_task()
	 * but when insmod will killed.
	 */
	pr_info("[%7d] %5d %5d %8lu %8lu %8ld %8lu         %5hd %s\n",
		task->pid, from_kuid(&init_user_ns, task_uid(task)),
		task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
		mm_pgtables_bytes(task->mm),
		get_mm_counter(task->mm, MM_SWAPENTS),
		task->signal->oom_score_adj, task->comm);
#endif
}

static int __init print_pid(void)
{
	struct task_struct *task, *p;
	struct list_head *pos;
	int count=0;

	printk("Printf process'message begin:\n");
	task = &init_task;

	pr_info("Tasks state (memory values in pages):\n");
	pr_info("[  pid  ]   uid  tgid total_vm      rss pgtables_bytes swapents oom_score_adj name\n");
	list_for_each(pos, &task->tasks) {
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		dump_task(p);
	}
	
	printk("Total process number is %d\n",count);	

	return -EINVAL;
}

module_init(print_pid);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
