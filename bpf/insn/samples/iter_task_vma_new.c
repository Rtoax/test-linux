/**
 * int bpf_iter_task_vma_new(struct bpf_iter_task_vma *it, struct task_struct *task, u64 addr);
 * struct vm_area_struct *bpf_iter_task_vma_next(struct bpf_iter_task_vma *it);
 * void bpf_iter_task_vma_destroy(struct bpf_iter_task_vma *it);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_iter_task_vma_new/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(iter_task_vma_new)
{
	int bpf_iter_task_vma_new_id;
	int bpf_iter_task_vma_destroy_id;

	bpf_iter_task_vma_new_id = btf_has_kfunc("bpf_iter_task_vma_new");
	bpf_iter_task_vma_destroy_id = btf_has_kfunc("bpf_iter_task_vma_destroy");

	if (bpf_iter_task_vma_new_id <= 0 || bpf_iter_task_vma_destroy_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_iter_task_vma_new kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	// TODO

	*cnt = insn - insns_buf;
	return insns_buf;
}
