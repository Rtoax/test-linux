/**
 * int bpf_arena_reserve_pages(void *p__map, void *ptr__ign, u32 page_cnt);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_arena_reserve_pages/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(arena_reserve_pages)
{
	int bpf_arena_reserve_pages_id;
	int bpf_arena_free_pages_id;

	bpf_arena_reserve_pages_id =
		btf_has_kfunc("bpf_arena_reserve_pages", true);
	bpf_arena_free_pages_id = btf_has_kfunc("bpf_arena_free_pages", true);

	if (bpf_arena_reserve_pages_id <= 0 || bpf_arena_free_pages_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_arena_reserve_pages kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_MOV64_IMM(BPF_REG_1, 123);
	*insn++ = BPF_CALL_KFUNC(0, bpf_arena_reserve_pages_id);
	*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 2);
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	*insn++ = BPF_CALL_KFUNC(0, bpf_arena_free_pages_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
