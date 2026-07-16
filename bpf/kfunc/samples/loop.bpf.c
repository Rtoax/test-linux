/**
 * long bpf_loop(__u32 nr_loops, void *callback_fn, void *callback_ctx,
 *               __u64 flags);
 * BPF_FUNC_loop = 181;
 * typedef int (*callback_fn)(__u32 index, void *callback_ctx);
 *
 * linux >= v5.17
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_loop/
 */
#include "vmlinux.h"

struct iter_arg {
	int i;
};

static int iter_cb(__u32 idx, struct iter_arg *args)
{
	return 0;
}

void test(void)
{
	struct iter_arg arg = {
		.i = 1,
	};
	bpf_loop(100, iter_cb, (void *)&arg, 0);
}
