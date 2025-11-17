#pragma once
#include <bpf/bpf.h>
#include <linux/bpf.h>

/* Kfunc call */
#ifndef BPF_CALL_KFUNC
#define BPF_CALL_KFUNC(OFF, IMM)				\
	((struct bpf_insn) {					\
		.code  = BPF_JMP | BPF_CALL,			\
		.dst_reg = 0,					\
		.src_reg = BPF_PSEUDO_KFUNC_CALL,		\
		.off   = OFF,					\
		.imm   = IMM })
#endif
