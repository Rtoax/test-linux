#pragma once
#include <sys/types.h>
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>

typedef struct bpf_insn *(*bpf_samples_get_insns_fn)(size_t *cnt);

#define BPF_INSN_SAMPLE_FUNC_NAME(helper)	bpf_insn_sample_##helper##_insns
#define BPF_INSN_SAMPLE_FUNC_PROTO(helper)	struct bpf_insn *BPF_INSN_SAMPLE_FUNC_NAME(helper)(size_t *cnt)

BPF_INSN_SAMPLE_FUNC_PROTO(trace_printk);
BPF_INSN_SAMPLE_FUNC_PROTO(strncmp);
BPF_INSN_SAMPLE_FUNC_PROTO(loop);
BPF_INSN_SAMPLE_FUNC_PROTO(cgroup_from_id);
BPF_INSN_SAMPLE_FUNC_PROTO(task_from_pid);
BPF_INSN_SAMPLE_FUNC_PROTO(cgrp_storage_get);
BPF_INSN_SAMPLE_FUNC_PROTO(get_func_ip);

void bpf_samples_insns_list(void);
bpf_samples_get_insns_fn bpf_samples_get_insns_from_string(const char *helper_str);
