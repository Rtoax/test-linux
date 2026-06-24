/**
 * int bpf_strnlen(const char *s__ign, size_t count);
 *
 * - https://docs.ebpf.io/linux/kfuncs/bpf_strnlen/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(strnlen)
{
	int btf_id = btf_has_kfunc(NULL, "bpf_strnlen", true);

	if (btf_id <= 0) {
		fprintf(stderr, "ERROR: not found strnlen kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 0);
	*insn++ = BPF_MOV64_IMM(BPF_REG_2, 0);
	*insn++ = BPF_CALL_KFUNC(0, btf_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
