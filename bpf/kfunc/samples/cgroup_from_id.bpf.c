/**
 * struct cgroup *bpf_cgroup_from_id(u64 cgid);
 *
 * linux v6.2-5267-g332ea1f697be
 * commit 332ea1f697be ("bpf: Add bpf_cgroup_from_id() kfunc")
 *
 * BPF_PROG_TYPE_LSM
 * BPF_PROG_TYPE_PERF_EVENT  v6.12
 * BPF_PROG_TYPE_SCHED_CLS
 * BPF_PROG_TYPE_STRUCT_OPS
 * BPF_PROG_TYPE_TRACEPOINT  v6.12
 * BPF_PROG_TYPE_TRACING
 * BPF_PROG_TYPE_XDP
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_cgroup_from_id/
 */
#include "vmlinux.h"

void test(void)
{
	u64 cgrpid = bpf_get_current_cgroup_id();
	struct cgroup *cgrp = bpf_cgroup_from_id(cgrpid);
	if (cgrp) {
		bpf_cgroup_release(cgrp);
	}
}
