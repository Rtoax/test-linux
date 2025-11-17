/**
 * int bpf_trace_printk(const char *fmt, int fmt_size, ...);
 */
#include "bpf_insn_samples.h"

static struct bpf_insn insns[] = {
	/* R10: frame pointer */
	BPF_MOV64_IMM(BPF_REG_1, 0x21),        /* '!' */
	BPF_STX_MEM(BPF_H, BPF_REG_10, BPF_REG_1, -4),
	BPF_MOV64_IMM(BPF_REG_1, 0x646c726f),   /* 'orld' */
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_1, -8),
	BPF_MOV64_IMM(BPF_REG_1, 0x57202c6f),   /* 'o, W' */
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_1, -12),
	BPF_MOV64_IMM(BPF_REG_1, 0x6c6c6548),   /* 'Hell' */
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_1, -16),
	BPF_MOV64_IMM(BPF_REG_1, 0),
	BPF_STX_MEM(BPF_B, BPF_REG_10, BPF_REG_1, -2),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -16),
	BPF_MOV64_IMM(BPF_REG_2, 0xf), /* fmt_size=15 */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 0, 0, BPF_FUNC_trace_printk),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};


struct bpf_insn *trace_printk_insns(size_t *cnt)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
