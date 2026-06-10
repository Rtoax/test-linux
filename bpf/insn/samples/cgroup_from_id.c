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
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(cgroup_from_id)
{
	int bpf_cgroup_from_id_id;
	int bpf_cgroup_release_id;

	bpf_cgroup_from_id_id = btf_has_kfunc(NULL, "bpf_cgroup_from_id", true);
	bpf_cgroup_release_id = btf_has_kfunc(NULL, "bpf_cgroup_release", true);

	if (bpf_cgroup_from_id_id <= 0 || bpf_cgroup_release_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_cgroup_from_id kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_cgroup_from_id_id);
	*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 2);
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_cgroup_release_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
