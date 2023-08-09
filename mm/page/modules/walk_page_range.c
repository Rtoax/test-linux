/**
 *	test page walk
 *	
 *	Author	Rong Tao <rongtao@cestc.cn>
 *	Time	2021.11.05
 *
 *	2022-02-05 
 */

#include <linux/pagewalk.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/pid.h>

static pid_t pid = 0;
module_param(pid, int, 0644);

static int pte_hole(unsigned long start, unsigned long end,
		    __always_unused int depth, struct mm_walk *walk)
{
	printk("PTE: %lx-%lx.\n", start, end);
	return 0;
}

static const struct mm_walk_ops pagewalktest_ops = {
//	.pmd_entry	= pmd_range,
	.pte_hole	= pte_hole,
};

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

/**
 *	见内核同名函数
 */
static int walk_page_test(unsigned long start, unsigned long end,
			struct mm_walk *walk)
{
	struct vm_area_struct *vma = walk->vma;
	const struct mm_walk_ops *ops = walk->ops;

	if (ops->test_walk)
		return ops->test_walk(start, end, walk);

	/*
	 * vma(VM_PFNMAP) doesn't have any valid struct pages behind VM_PFNMAP
	 * range, so we don't walk over it as we do for normal vmas. However,
	 * Some callers are interested in handling hole range and they don't
	 * want to just ignore any single address range. Such users certainly
	 * define their ->pte_hole() callbacks, so let's delegate them to handle
	 * vma(VM_PFNMAP).
	 */
	if (vma->vm_flags & VM_PFNMAP) {
		int err = 1;
		if (ops->pte_hole)
			err = ops->pte_hole(start, end, -1, walk);
		return err ? err : 1;
	}
	return 0;
}

static int __walk_page_range(unsigned long start, unsigned long end,
			struct mm_walk *walk)
{
	int err = 0;
	struct vm_area_struct *vma = walk->vma;
	const struct mm_walk_ops *ops = walk->ops;

	if (vma && ops->pre_vma) {
		err = ops->pre_vma(start, end, walk);
		if (err)
			return err;
	}

	if (vma && is_vm_hugetlb_page(vma)) {
		if (ops->hugetlb_entry)
			err = walk_hugetlb_range(start, end, walk);
	} else
		err = walk_pgd_range(start, end, walk);
    /**
     *  调用
     */
	if (vma && ops->post_vma)
		ops->post_vma(walk);

	return err;
}

/**
 *	初始化函数
 *	见 `walk_page_range()`
 */
static int __init pagewalktest_init(void)
{
	struct task_struct *task = this_task(pid);
	struct mm_struct *mm = task->mm;
	int err = 0;
	unsigned long next, start, end;
	struct vm_area_struct *vma;

	struct mm_walk walk = {
		.ops = &pagewalktest_ops,
		.mm = mm,
		.private = NULL,
	};

	start = 0;
	end = 0xffffffffffffffff;

	printk("pagewalktest_init.\n");

	if (start >= end)
		return -EINVAL;

	if (!walk.mm)
		return -EINVAL;

	mmap_assert_locked(walk.mm);

	vma = find_vma(walk.mm, start);
	do {
		if (!vma) {
			walk.vma = NULL;
			next = end;
		} else if (start < vma->vm_start) {
			walk.vma = NULL;
			next = min(end, vma->vm_start);
		} else {
			walk.vma = vma;
			next = min(end, vma->vm_end);
			vma = vma->vm_next;

			err = walk_page_test(start, next, &walk);
			if (err > 0) {
				err = 0;
				continue;
			}
			if (err < 0)
				break;
		}
		if (walk.vma || walk.ops->pte_hole)
			err = __walk_page_range(start, next, &walk);
		if (err)
			break;
	} while (start = next, start < end);

#if 0
	struct task_struct *this_task = current;

	/**
	 *	Undefined, can't use in module/driver
	 */
	walk_page_range(this_task->mm, 0, 0, &pagewalktest_ops, NULL);
#endif
	return 0;
}

static void __exit pagewalktest_exit(void)
{
	printk("pagewalktest_exit.\n");
}

module_init(pagewalktest_init);
module_exit(pagewalktest_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
