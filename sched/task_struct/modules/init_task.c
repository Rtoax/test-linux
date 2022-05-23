#include <linux/kernel.h>
#include <linux/module.h>
#include <uapi/linux/sched.h>
#include <linux/init_task.h>
#include <linux/init.h>
#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/mm_types.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");

static int __init print_pid(void)
{
	struct task_struct *task, *p;
	struct list_head *pos;
	unsigned long count = 0;
	unsigned long cnt_uninterruptible = 0;
	unsigned long cnt_interruptible = 0;
	unsigned long cnt_running = 0;

	printk("Printf process'message begin:\n");
	task = &init_task;
	
	list_for_each(pos,&task->tasks)
	{
		p = list_entry(pos,struct task_struct,tasks);
		count++;
		printk("\n\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
# define Sfmt "%x"
# define STATE __state
#else
# define Sfmt "%lx"
# define STATE state
#endif
		printk("pid:%d; state:"Sfmt"; prio:%d; static_prio:%d; parent'pid:%d; count:%d; umask:%d;",
			p->pid,
			p->STATE,
			p->prio,p->static_prio,(p->parent)->pid,
			atomic_read((&(p->files)->count)),(p->fs)->umask);
		
		if ((p->mm)!=NULL)
			printk("total_vm:%ld;",(p->mm)->total_vm);
		if (p->STATE == TASK_UNINTERRUPTIBLE)
			cnt_uninterruptible++;
		if (p->STATE == TASK_INTERRUPTIBLE)
			cnt_interruptible++;
		if (p->STATE == TASK_RUNNING)
			cnt_running++;
	}
	
	printk("Total process number is %ld\n", count);
	printk("Uninterruptible %ld\n", cnt_uninterruptible);
	printk("  Interruptible %ld\n", cnt_interruptible);
	printk("        Running %ld\n", cnt_running);

	return 0;
}

static void __exit pid_exit(void)
{
	printk("exiting...\n");
}

module_init(print_pid);
module_exit(pid_exit);
