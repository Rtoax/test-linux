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
	int count=0;
	printk("Printf process'message begin:\n");
	task = &init_task;
	
	list_for_each(pos,&task->tasks)
	{
		p = list_entry(pos,struct task_struct,tasks);
		count++;
		printk("\n\n");

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
			p->prio,p->static_prio,(p->parent)->pid,
			atomic_read((&(p->files)->count)),(p->fs)->umask);

		printk("Offset flags = %ld\n", offsetof(struct task_struct, flags));
		printk("Offset comm = %ld\n", offsetof(struct task_struct, comm));
		printk("Offset se.on_rq = %ld\n", offsetof(struct task_struct, se.on_rq));
		
		if((p->mm)!=NULL)
			printk("total_vm:%ld;",(p->mm)->total_vm);
	}
	
	printk("Total process number is %d\n",count);	

	return 0;
}

static void __exit pid_exit(void)
{
	printk("exiting...\n");
}

module_init(print_pid);
module_exit(pid_exit);
