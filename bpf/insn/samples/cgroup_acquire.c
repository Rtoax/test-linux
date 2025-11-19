/**
 * struct cgroup *bpf_cgroup_acquire(struct cgroup *cgrop);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_cgroup_acquire/
 */
#include <stdio.h>
#include <stdint.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(cgroup_acquire)
{
	int bpf_cgroup_acquire_id;
	int bpf_cgroup_release_id;

	bpf_cgroup_acquire_id = btf_has_kfunc("bpf_cgroup_acquire");
	bpf_cgroup_release_id = btf_has_kfunc("bpf_cgroup_release");

	if (bpf_cgroup_acquire_id <= 0 || bpf_cgroup_release_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_cgroup_acquire kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	/* bpf_prog_load(): 1ULL: EINVAL, 0ULL: EPERM */
	uint64_t cgroup = 0ULL;
	*insn++ = BPF_MOV64_IMM(BPF_REG_1, cgroup);
	*insn++ = BPF_CALL_KFUNC(0, bpf_cgroup_acquire_id);
	*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 2);
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_cgroup_release_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
