#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/mmdebug.h>
#include <linux/printk.h>
#include <linux/version.h>
#include <asm/uaccess.h>

#ifndef CONFIG_DEBUG_VM
void dump_vma(const struct vm_area_struct *vma)
{
	pr_emerg("vma %px start %px end %px\n"
		"mm %px\n"
		"prot %lx anon_vma %px vm_ops %px\n"
		"pgoff %lx file %px private_data %px\n"
		"flags: %#lx(%pGv)\n",
		vma, (void *)vma->vm_start, (void *)vma->vm_end,
		vma->vm_mm,
		(unsigned long)pgprot_val(vma->vm_page_prot),
		vma->anon_vma, vma->vm_ops, vma->vm_pgoff,
		vma->vm_file, vma->vm_private_data,
		vma->vm_flags, &vma->vm_flags);
}
#endif

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

/**
 * commit 763ecb035029 ("mm: remove the vma linked list") remove linked list
 *
 * $ git describe 763ecb035029f500d7e6dc99acd1ad299b7726a1
 * v6.0-rc3-284-g763ecb035029
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
	MA_STATE(mas, &mm->mm_mt, 0, 0);
	mas_for_each(&mas, vma, ULONG_MAX)
#else
	for (vma = mm->mmap; vma; vma = vma->vm_next)
#endif
		dump_vma(vma);
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
	/* fake insmod failed. */
	return -EINVAL;
}

module_init(mymem_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
