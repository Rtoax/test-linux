/**
 * int bpf_iter_task_vma_new(struct bpf_iter_task_vma *it, struct task_struct *task, u64 addr);
 * struct vm_area_struct *bpf_iter_task_vma_next(struct bpf_iter_task_vma *it);
 * void bpf_iter_task_vma_destroy(struct bpf_iter_task_vma *it);
 *
 * Developing procedures:
 * 2. commit a9bfa6b3454d ("todo: bpf/insn/samples: call bpf_iter_task_vma_new with NULL args")
 * 1. commit 6a4323ae2d0a ("todo: bpf/insn/samples: test bpf_iter_task_vma_new()")
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

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 0);
	*insn++ = BPF_MOV64_IMM(BPF_REG_2, 0);
	*insn++ = BPF_MOV64_IMM(BPF_REG_3, 0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_iter_task_vma_new_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();
	// TODO

	*cnt = insn - insns_buf;
	return insns_buf;
}
