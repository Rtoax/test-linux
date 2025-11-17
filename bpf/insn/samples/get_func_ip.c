/**
 * u64 bpf_get_func_ip(void *ctx);
 * BPF_FUNC_get_func_ip = 173;
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_func_ip/
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_func_ip),
	BPF_EXIT_INSN(),
};

struct bpf_insn *get_func_ip_insns(size_t *cnt)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
