/**
 * struct task_struct *bpf_task_acquire(struct task_struct *p);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_task_acquire/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(task_acquire)
{
	int bpf_task_acquire_id;
	int bpf_task_release_id;

	bpf_task_acquire_id = btf_has_kfunc("bpf_task_acquire");
	bpf_task_release_id = btf_has_kfunc("bpf_task_release");

	if (bpf_task_acquire_id <= 0 || bpf_task_release_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_task_acquire kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_task_acquire_id);
	*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 2);
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_task_release_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
