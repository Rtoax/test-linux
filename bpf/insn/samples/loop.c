/**
 * long bpf_loop(__u32 nr_loops, void *callback_fn, void *callback_ctx,
 *               __u64 flags);
 * BPF_FUNC_loop = 181;
 * typedef int (*callback_fn)(__u32 index, void *callback_ctx);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_loop/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_loop),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(loop)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
