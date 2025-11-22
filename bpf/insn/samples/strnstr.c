/**
 * int bpf_strnstr(const char *s1__ign, const char *s2__ign, size_t len)
 *
 * - https://docs.ebpf.io/linux/kfuncs/bpf_strnstr/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(strnstr)
{
	int strnstr_id;

	strnstr_id = btf_has_kfunc("bpf_strnstr");

	if (strnstr_id <= 0) {
		fprintf(stderr, "ERROR: not found strnstr kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 0);
	*insn++ = BPF_MOV64_IMM(BPF_REG_2, 0);
	*insn++ = BPF_MOV64_IMM(BPF_REG_3, 0); // len must be zero here
	*insn++ = BPF_CALL_KFUNC(0, strnstr_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
