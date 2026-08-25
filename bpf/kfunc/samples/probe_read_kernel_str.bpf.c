/**
 * static long (*const bpf_probe_read_kernel_str)(void *dst, __u32 size,
 *                                                const void *unsafe_ptr) = (void *)115;
 * BPF_FUNC_probe_read_kernel_str = (void *)115;
 * linux >= v5.5
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_probe_read_kernel_str/
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

void test(void *ctx)
{
	char dst[32];
	bpf_probe_read_kernel_str(dst, sizeof(dst), "Hello");
}
