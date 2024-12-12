// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_CGROUP_DEVICE
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

#define BPF_DEVCG_ACC_MKNOD	(1ULL << 0)
#define BPF_DEVCG_ACC_READ	(1ULL << 1)
#define BPF_DEVCG_ACC_WRITE	(1ULL << 2)

#define BPF_DEVCG_DEV_BLOCK	(1ULL << 0)
#define BPF_DEVCG_DEV_CHAR	(1ULL << 1)

SEC("cgroup/dev")
int bpf_prog1(struct bpf_cgroup_dev_ctx *ctx)
{
	short type = ctx->access_type & 0xFFFF;
	short access = ctx->access_type >> 16;
	char fmt[] = "  %d:%d    ";

	switch (type) {
	case BPF_DEVCG_DEV_BLOCK:
		fmt[0] = 'b';
		break;
	case BPF_DEVCG_DEV_CHAR:
		fmt[0] = 'c';
		break;
	default:
		fmt[0] = '?';
		break;
	}

	if (access & BPF_DEVCG_ACC_READ)
		fmt[8] = 'r';

	if (access & BPF_DEVCG_ACC_WRITE)
		fmt[9] = 'w';

	if (access & BPF_DEVCG_ACC_MKNOD)
		fmt[10] = 'm';

	bpf_trace_printk(fmt, sizeof(fmt), ctx->major, ctx->minor);

	/* Allow access to /dev/zero and /dev/random.
	 * Forbid everything else.
	 */
	if (ctx->major != 1 || type != BPF_DEVCG_DEV_CHAR)
		return 0;

	switch (ctx->minor) {
	case 5: /* 1:5 /dev/zero */
	case 9: /* 1:9 /dev/urandom */
		return 1;
	}

	return 0;
}

char _license[] SEC("license") = "GPL";
