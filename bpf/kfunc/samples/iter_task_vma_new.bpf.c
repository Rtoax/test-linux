/**
 * int bpf_iter_task_vma_new(struct bpf_iter_task_vma *it, struct task_struct *task, u64 addr);
 * struct vm_area_struct *bpf_iter_task_vma_next(struct bpf_iter_task_vma *it);
 * void bpf_iter_task_vma_destroy(struct bpf_iter_task_vma *it);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_iter_task_vma_new/
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

void test(void)
{
	struct bpf_iter_task_vma vma_it;
	struct vm_area_struct *vma_ptr;
	struct task_struct *cur_task = bpf_get_current_task_btf();

	bpf_iter_task_vma_new(&vma_it, cur_task, 0);

	while ((vma_ptr = bpf_iter_task_vma_next(&vma_it)));

	bpf_iter_task_vma_destroy(&vma_it);
}
