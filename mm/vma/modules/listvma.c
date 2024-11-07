#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <asm/uaccess.h>


static void list_current_vma(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	printk("list vma..\n");
	printk("current:%s pid:%d\n", current->comm, current->pid);

#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 8, 0)
	down_read(&mm->mmap_lock);
#else
	down_read(&mm->mmap_sem);
#endif
/**
 * commit 763ecb035029 ("mm: remove the vma linked list") remove linked list
 *
 * $ git describe 763ecb035029f500d7e6dc99acd1ad299b7726a1
 * v6.0-rc3-284-g763ecb035029
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
	MA_STATE(mas, &mm->mm_mt, 0, 0);
	mas_for_each(&mas, vma, ULONG_MAX) {
#else
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
#endif
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
	list_current_vma();
	/* insmod failed on purpose */
	return -EINVAL;
}

module_init(mymem_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
