#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 11, 0)
#include <linux/pgtable.h>
#endif
#include <asm/uaccess.h>

void dump_mm(const struct mm_struct *mm)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)
	pr_emerg("mm %px mmap %px seqnum %llu task_size %lu\n"
#ifdef CONFIG_MMU
/**
 * kernel commit 529ce23a764f ("mm: switch mm->get_unmapped_area() to a flag")
 * v6.9-rc4-205-g529ce23a764f
 */
# if LINUX_VERSION_CODE < KERNEL_VERSION(6, 9, 0)
		"get_unmapped_area %px\n"
# endif
#endif
		"mmap_base %lu mmap_legacy_base %lu highest_vm_end %lu\n"
		"pgd %px mm_users %d mm_count %d pgtables_bytes %lu map_count %d\n"
		"hiwater_rss %lx hiwater_vm %lx total_vm %lx locked_vm %lx\n"
		"pinned_vm %llx data_vm %lx exec_vm %lx stack_vm %lx\n"
		"start_code %lx end_code %lx start_data %lx end_data %lx\n"
		"start_brk %lx brk %lx start_stack %lx\n"
		"arg_start %lx arg_end %lx env_start %lx env_end %lx\n"
		"binfmt %px flags %lx \n"
#ifdef CONFIG_AIO
		"ioctx_table %px\n"
#endif
#ifdef CONFIG_MEMCG
		"owner %px "
#endif
		"exe_file %px\n"
#ifdef CONFIG_MMU_NOTIFIER
		"notifier_subscriptions %px\n"
#endif
#ifdef CONFIG_NUMA_BALANCING
		"numa_next_scan %lu numa_scan_offset %lu numa_scan_seq %d\n"
#endif
		"tlb_flush_pending %d\n"
		"def_flags: %#lx(%pGv)\n",

		mm,
/**
 * commit 763ecb035029 ("mm: remove the vma linked list") remove linked list
 * v6.0-rc3-284-g763ecb035029
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		NULL,
#else
		mm->mmap,
#endif
/* commit 7964cf8caa4d ("mm: remove vmacache") */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		0UL,
#else
		(long long) mm->vmacache_seqnum,
#endif
		mm->task_size,
#ifdef CONFIG_MMU
# if LINUX_VERSION_CODE < KERNEL_VERSION(6, 9, 0)
		mm->get_unmapped_area,
# endif
#endif
		mm->mmap_base, mm->mmap_legacy_base,
/* commit 763ecb035029 ("mm: remove the vma linked list") remove linked list */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		0UL,
#else
		mm->highest_vm_end,
#endif
		mm->pgd, atomic_read(&mm->mm_users),
		atomic_read(&mm->mm_count),
		mm_pgtables_bytes(mm),
		mm->map_count,
		mm->hiwater_rss, mm->hiwater_vm, mm->total_vm, mm->locked_vm,
		(u64)atomic64_read(&mm->pinned_vm),
		mm->data_vm, mm->exec_vm, mm->stack_vm,
		mm->start_code, mm->end_code, mm->start_data, mm->end_data,
		mm->start_brk, mm->brk, mm->start_stack,
		mm->arg_start, mm->arg_end, mm->env_start, mm->env_end,
		mm->binfmt, mm->flags,
#ifdef CONFIG_AIO
		mm->ioctx_table,
#endif
#ifdef CONFIG_MEMCG
		mm->owner,
#endif
		mm->exe_file,
#ifdef CONFIG_MMU_NOTIFIER
		mm->notifier_subscriptions,
#endif
#ifdef CONFIG_NUMA_BALANCING
		mm->numa_next_scan, mm->numa_scan_offset, mm->numa_scan_seq,
#endif
		atomic_read(&mm->tlb_flush_pending),
		mm->def_flags, &mm->def_flags
	);
#endif
}


static void dump_init_mm(void)
{
	/**
	 *	init_mm is not EXPORT_SYMBOL
	 */
	//dump_mm(&init_mm);
}

static int __init mymem_init(void)
{
	printk("mymem module is working..\n");

	dump_init_mm();

	/* insmod failed on purpose */
	return -EINVAL;
}

module_init(mymem_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
