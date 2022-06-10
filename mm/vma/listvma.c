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
#include <linux/version.h>
#include <asm/uaccess.h>

static void list_myvma(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	printk("list vma..\n");
        //print the current process's name and pid
	printk("current:%s pid:%d\n", current->comm, current->pid);

#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 8, 0)
	down_read(&mm->mmap_lock);
#else
	down_read(&mm->mmap_sem);
#endif
	//vma is a linklist
	for(vma = mm->mmap; vma; vma = vma->vm_next)
	{
		//from the begining to the ending of a virtual memory area
		printk("0x%lx-0x%lx %s%s%s%s\n",
			vma->vm_start, vma->vm_end,
			(vma->vm_flags & VM_READ)?"r":"-",
			(vma->vm_flags & VM_WRITE)?"w":"-",
			(vma->vm_flags & VM_EXEC)?"x":"-",
			(vma->vm_flags & VM_SHARED)?"s":"p");
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
