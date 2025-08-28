#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>
#include <linux/version.h>
#include "bpf_helpers.h"


#define DEBUGFS	"/sys/kernel/debug/tracing"

#ifndef offsetofend
#define offsetofend(TYPE, MEMBER) \
	(offsetof(TYPE, MEMBER)	+ sizeof((((TYPE *)0)->MEMBER)))
#endif

char bpf_log_buf[BPF_LOG_BUF_SIZE];

int main(void)
{
	int i, prog_fd;

	char license[] = "GPL";
	struct bpf_insn insns[] = {
		#if 1
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
		BPF_MOV64_IMM(BPF_REG_2, 15),
		BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0,0,0, BPF_FUNC_trace_printk),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		#elif 1
		/**
		 * TODO: ERROR: failed to load prog 'Permission denied'
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
		#elif 0
		{0xb4, 0x0, 0x1, 0x0000, 0x00},
		{0x73, 0x1, 0xa, 0xfcff, 0x00},
		{0xb4, 0x0, 0x2, 0x0000, 0x74657374},
		{0x63, 0x2, 0xa, 0xf0ff, 0x00},
		{0x73, 0x1, 0xa, 0xf4ff, 0x00},
		{0xbf, 0xa, 0x1, 0x0000, 0x00},
		{0x07, 0x0, 0x1, 0x0000, 0xf8ffffff},
		{0xbf, 0xa, 0x3, 0x0000, 0x00},
		{0x07, 0x0, 0x3, 0x0000, 0xf0ffffff},
		{0xb4, 0x0, 0x2, 0x0000, 0x04000000},
		{0x85, 0x0, 0x0, 0x0000, 0xb6000000},
		{0xb4, 0x0, 0x0, 0x0000, 0x00},
		{0x95, 0x0, 0x0, 0x0000, 0x00},
		#elif 0
		{0xb4, 0x0, 0x1, 0x0000, 0x00},
		{0x73, 0x1, 0xa, 0xfcff, 0x00},
		{0xb4, 0x0, 0x2, 0x0000, 0x74736574},
		{0x63, 0x2, 0xa, 0xf0ff, 0x00},
		{0x73, 0x1, 0xa, 0xf4ff, 0x00},
		{0xbf, 0xa, 0x1, 0x0000, 0x00},
		{0x07, 0x0, 0x1, 0x0000, 0xfffffff8},
		{0xbf, 0xa, 0x3, 0x0000, 0x00},
		{0x07, 0x0, 0x3, 0x0000, 0xfffffff0},
		{0xb4, 0x0, 0x2, 0x0000, 0x00000004},
		{0x85, 0x0, 0x0, 0x0000, 0x000000b6},
		{0xb4, 0x0, 0x0, 0x0000, 0x00},
		{0x95, 0x0, 0x0, 0x0000, 0x00},
		#elif 0
		{0xb4, 0x1, 0x0, 0x0000, 0x00},
		{0x73, 0xa, 0x1, 0xfcff, 0x00},
		{0xb4, 0x2, 0x0, 0x0000, 0x74736574},
		{0x63, 0xa, 0x2, 0xf0ff, 0x00},
		{0x73, 0xa, 0x1, 0xf4ff, 0x00},
		{0xbf, 0x1, 0xa, 0x0000, 0x00},
		{0x07, 0x1, 0x0, 0x0000, 0xfffffff8},
		{0xbf, 0x3, 0xa, 0x0000, 0x00},
		{0x07, 0x3, 0x0, 0x0000, 0xfffffff0},
		{0xb4, 0x2, 0x0, 0x0000, 0x00000004},
		{0x85, 0x0, 0x0, 0x0000, 0x000000b6},
		{0xb4, 0x0, 0x0, 0x0000, 0x00},
		{0x95, 0x0, 0x0, 0x0000, 0x00},
		#elif 0
		{0xb4, 0x0, 0x1, 0x0000, 0x00},
		{0x73, 0x1, 0xa, 0xfffc, 0x00},
		{0xb4, 0x0, 0x2, 0x0000, 0x74736574},
		{0x63, 0x2, 0xa, 0xfff0, 0x00},
		{0x73, 0x1, 0xa, 0xfff4, 0x00},
		{0xbf, 0xa, 0x1, 0x0000, 0x00},
		{0x07, 0x0, 0x1, 0x0000, 0xfffffff8},
		{0xbf, 0xa, 0x3, 0x0000, 0x00},
		{0x07, 0x0, 0x3, 0x0000, 0xfffffff0},
		{0xb4, 0x0, 0x2, 0x0000, 0x00000004},
		{0x85, 0x0, 0x0, 0x0000, 0x000000b6},
		{0xb4, 0x0, 0x0, 0x0000, 0x00},
		{0x95, 0x0, 0x0, 0x0000, 0x00},
		#endif
	};
	size_t insns_cnt = sizeof(insns) / sizeof(struct bpf_insn);
	union bpf_attr prog_load_attr = {
		.prog_type = BPF_PROG_TYPE_KPROBE,
		.insns = (long)insns,
		.insn_cnt = insns_cnt,
		.license = (long)license,
		.log_buf = (long)bpf_log_buf,
		.log_size = sizeof(bpf_log_buf),
		.log_level = 1,
	};

	prog_fd = bpf(BPF_PROG_LOAD, &prog_load_attr, sizeof(prog_load_attr));
	if (prog_fd < 0) {
		printf("ERROR: failed to load prog '%s'\n", strerror(errno));
		return 1;
	}

	for (i = 0; i < sizeof(bpf_log_buf); i++) {
		if (bpf_log_buf[i] == 0 && bpf_log_buf[i+1] == 0)
			break;
		printf("%c", bpf_log_buf[i]);
	}

#if defined(BCC)
	int probe_fd;
	/**
	 * bcc function bpf_attach_kprobe()
	 */
	probe_fd = bpf_attach_kprobe(prog_fd, BPF_PROBE_ENTRY, "hello_world", "do_nanosleep", 0, 0);
	if (prog_fd < 0) {
		printf("ERROR: failed to attach kprobe to do_nanosleep.\n");
		return 2;
	}

	fprintf(stdout, "Kprobe do_nanosleep(), test with 'sleep 0.1'.\n");
	system("cat " DEBUGFS "/trace_pipe");
	close(probe_fd);
	bpf_detach_kprobe("hello_world");
#else
	// TODO
	union bpf_attr prog_run_attr;
	size_t attr_sz = offsetofend(union bpf_attr, test);

	memset(&prog_run_attr, 0x0, sizeof(prog_run_attr));
	prog_run_attr.test.prog_fd = prog_fd;
	prog_run_attr.test.ctx_in = 0;

	int err = bpf(BPF_PROG_TEST_RUN, &prog_run_attr, attr_sz);
	if (err < 0 || (int)prog_run_attr.test.retval < 0) {
		if (err < 0)
			fprintf(stderr, "failed to execute loader prog, err = %d\n", err);
		else
			fprintf(stderr, "error returned by loader prog, retval = %d\n",
				prog_run_attr.test.retval);
	}
#endif
	close(prog_fd);
	return 0;
}
