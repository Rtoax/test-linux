/**
 * static long (*const bpf_perf_event_output)(void *ctx, void *map, __u64 flags,
 *                                            void *data, __u64 size);
 * BPF_FUNC_perf_event_output = (void *) 25;
 * linux >= v4.4
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_perf_event_output/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	/* TODO */
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(perf_event_output)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
