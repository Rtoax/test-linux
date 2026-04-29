// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
/**
 * long bpf_get_stackid(void *ctx, struct bpf_map *map, u64 flags);
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	/* TODO */
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(get_stackid)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
