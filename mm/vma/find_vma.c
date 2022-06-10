/**
 *	File ./listvma.c 
 *	Time 2021.11.03
 *	Author	Rong Tao <rongtao@cestc.cn>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/dcache.h> //for d_path()
#include <linux/version.h>
#include <asm/uaccess.h>

static pid_t pid = 0;
module_param(pid, int, 0644);

static struct task_struct* this_task(pid_t PID)
{
	struct pid *_pid;
	struct task_struct *task;

	if(pid <= 0) {
		return current;
	}
    _pid = find_get_pid(PID);
    if(!_pid) {
        printk("Not exist PID %d\n", PID);
        return current;
    }
    
	task = pid_task(_pid, PIDTYPE_TGID);
    if(!task) {
		return current;
    }
	return task;
}

static void list_myvma(void)
{
	struct task_struct *task = this_task(pid);
	struct mm_struct *mm = task->mm;
	struct vm_area_struct *vma;

	printk("list vma..\n");
	printk("task:%s pid:%d\n", task->comm, task->pid);
	
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 8, 0)
	down_read(&mm->mmap_lock);
#else
	down_read(&mm->mmap_sem);
#endif
	//vma is a linklist
	for(vma = mm->mmap; vma; vma = vma->vm_next)
	{
		/**
		 *	为了测试 find_vma 我强制加的搜索 vma
		 */
		unsigned long find_addr = (vma->vm_start + vma->vm_end)/2;
		struct vm_area_struct *_vma = find_vma(mm, find_addr);
		char filename[256] = {0};
		char *filep = NULL;

		if(!_vma) {
			printk(KERN_ERR "Can't find vma %ld\n", find_addr);
			continue;
		}
		if(_vma->vm_file) {
			filep = d_path(&_vma->vm_file->f_path, filename, 256);
		}
		//from the begining to the ending of a virtual memory area
		printk("0x%lx-0x%lx %s%s%s%s %s\n",
			_vma->vm_start, _vma->vm_end,
			(_vma->vm_flags & VM_READ)?"r":"-",
			(_vma->vm_flags & VM_WRITE)?"w":"-",
			(_vma->vm_flags & VM_EXEC)?"x":"-",
			(_vma->vm_flags & VM_SHARED)?"s":"p",
			_vma->vm_file?filep:"");
	}
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 8, 0)
	up_read(&mm->mmap_lock);
#else
	up_read(&mm->mmap_sem);
#endif
}

static int __init mymem_init(void)
{
	printk("mymem module is working..\n");

	list_myvma();
	return 0;
}

static void __exit mymem_exit(void)
{
	printk("mymem module is leaving..\n");
}

MODULE_LICENSE("GPL");
module_init(mymem_init);
module_exit(mymem_exit);
