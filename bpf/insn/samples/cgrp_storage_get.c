/**
 * void *bpf_cgrp_storage_get(struct bpf_map *map, struct cgroup *cgroup, void *value, u64 flags);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_cgrp_storage_get/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_cgrp_storage_get),
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(cgrp_storage_get)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
