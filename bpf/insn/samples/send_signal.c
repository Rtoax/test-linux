/**
 * static long (*const bpf_send_signal)(__u32 sig) = (void *)109;
 *
 * Program types:
 * - BPF_PROG_TYPE_KPROBE
 * - BPF_PROG_TYPE_LSM
 * - BPF_PROG_TYPE_PERF_EVENT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE
 * - BPF_PROG_TYPE_SYSCALL
 * - BPF_PROG_TYPE_TRACEPOINT
 * - BPF_PROG_TYPE_TRACING
 *
 * Refs:
 * - linux v5.2-rc1-220-g8b401f9ed244
 *   commit 8b401f9ed244 ("bpf: implement bpf_send_signal() helper")
 * - https://docs.ebpf.io/linux/helper-function/bpf_send_signal/
 */
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	BPF_MOV64_REG(BPF_REG_1, 2 /* SIGINT */),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_send_signal),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};

BPF_INSN_SAMPLE_FUNC_PROTO(send_signal)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
