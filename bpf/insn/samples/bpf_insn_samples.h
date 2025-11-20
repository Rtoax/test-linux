#pragma once
#include <sys/types.h>
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>
#include <linux/version.h>

typedef struct bpf_insn *(*bpf_samples_get_insns_fn)(size_t *cnt);

#define BPF_INSN_SAMPLE_FUNC_NAME(helper)	bpf_insn_sample_##helper##_insns
#define BPF_INSN_SAMPLE_FUNC_PROTO(helper)	struct bpf_insn *BPF_INSN_SAMPLE_FUNC_NAME(helper)(size_t *cnt)

#define BPF_INSN_SAMPLE(h)	BPF_INSN_SAMPLE_FUNC_PROTO(h);
#include "bpf_insn_defs.h"
#undef BPF_INSN_SAMPLE

void bpf_samples_insns_list(void);
bpf_samples_get_insns_fn bpf_samples_get_insns_from_string(const char *helper_str);
