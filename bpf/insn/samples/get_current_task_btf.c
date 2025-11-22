/**
 * struct task_struct *bpf_get_current_task_btf(void);
 * BPF_FUNC_get_current_task_btf = 158;
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_current_task_btf/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_MOV64_IMM(BPF_REG_1, 0),
	BPF_MOV64_IMM(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_current_task_btf),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};


BPF_INSN_SAMPLE_FUNC_PROTO(get_current_task_btf)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
