/**
 * static long (*const bpf_probe_read_kernel_str)(void *dst, __u32 size,
 *                                                const void *unsafe_ptr);
 * BPF_FUNC_probe_read_kernel_str = (void *)115;
 * linux >= v5.5
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_probe_read_kernel_str/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	/* TODO */
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(probe_read_kernel_str)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
