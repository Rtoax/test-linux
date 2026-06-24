/**
 * static long (* const bpf_send_signal_thread)(__u32 sig) = (void *) 117;
 *
 * - linux v5.5-rc4-897-g8482941f0906
 *   commit 8482941f0906 ("bpf: Add bpf_send_signal_thread() helper")
 * - https://docs.ebpf.io/linux/helper-function/bpf_send_signal_thread/
 */
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_MOV64_REG(BPF_REG_1, 2 /* SIGINT */),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_send_signal_thread),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(send_signal_thread)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
