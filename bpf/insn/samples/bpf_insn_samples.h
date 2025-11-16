#pragma once
#include <sys/types.h>
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>

struct bpf_insn *trace_printk_insns(size_t *cnt);
