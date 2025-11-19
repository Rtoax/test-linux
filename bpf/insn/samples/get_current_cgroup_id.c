/**
 * __u64 bpf_get_current_cgroup_id(void);
 * BPF_FUNC_get_current_cgroup_id = 80;
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_current_cgroup_id/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_current_cgroup_id),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};


BPF_INSN_SAMPLE_FUNC_PROTO(get_current_cgroup_id)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
