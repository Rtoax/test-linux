#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>


/* TODO: load failed */
struct bpf_insn insns[] = {
	/**
	 * WARNING: ERROR: failed to load prog 'Permission denied'
	 * the s2 of bpf_strncmp() must be static/global variable, and
	 * can't be NULL.
	 *
	 * Bad code:
	 *
	 * SEC("kprobe/vfs_open")
	 * int BPF_KPROBE(vfs_open)
	 * {
	 * 	char s1[] = "test";
	 * 	char s2[] = "test";
	 * 	bpf_strncmp(s1, 4, s2);
	 * 	return 0;
	 * }
	 * 0000000000000000 <vfs_open>:
	 *        0:	b4 01 00 00 00 00 00 00	w1 = 0x0
	 *        1:	73 1a fc ff 00 00 00 00	*(u8 *)(r10 - 0x4) = w1
	 *        2:	b4 02 00 00 74 65 73 74	w2 = 0x74736574
	 *        3:	63 2a f8 ff 00 00 00 00	*(u32 *)(r10 - 0x8) = w2
	 *        4:	63 2a f0 ff 00 00 00 00	*(u32 *)(r10 - 0x10) = w2
	 *        5:	73 1a f4 ff 00 00 00 00	*(u8 *)(r10 - 0xc) = w1
	 *        6:	bf a1 00 00 00 00 00 00	r1 = r10
	 *        7:	07 01 00 00 f8 ff ff ff	r1 += -0x8
	 *        8:	bf a3 00 00 00 00 00 00	r3 = r10
	 *        9:	07 03 00 00 f0 ff ff ff	r3 += -0x10
	 *       10:	b4 02 00 00 04 00 00 00	w2 = 0x4
	 *       11:	85 00 00 00 b6 00 00 00	call 0xb6
	 *       12:	b4 00 00 00 00 00 00 00	w0 = 0x0
	 *       13:	95 00 00 00 00 00 00 00	exit
	 */
	BPF_MOV64_IMM(BPF_REG_1, 0x0),
	BPF_STX_MEM(BPF_B, BPF_REG_10, BPF_REG_1, -0x4),
	BPF_MOV64_IMM(BPF_REG_2, 0x74736574),
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_2, -0x8),
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_2, -0x10),
	BPF_STX_MEM(BPF_B, BPF_REG_10, BPF_REG_1, -0xc),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -0x8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, -0x10),
	BPF_MOV64_IMM(BPF_REG_2, 0x4),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_strncmp),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
};

struct bpf_insn *strncmp_insns(size_t *cnt)
{
	*cnt = sizeof(insns) / sizeof(struct bpf_insn);
	return insns;
}
