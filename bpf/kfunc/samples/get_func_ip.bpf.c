/**
 * u64 bpf_get_func_ip(void *ctx);
 * BPF_FUNC_get_func_ip = 173;
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_func_ip/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_get_func_ip(0);
}
