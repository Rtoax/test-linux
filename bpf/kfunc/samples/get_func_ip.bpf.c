/**
 * u64 bpf_get_func_ip(void *ctx);
 * BPF_FUNC_get_func_ip = 173;
 *
 * Get address of the traced function (for tracing and kprobe programs).
 *
 * When called for kprobe program attached as uprobe it returns probe address
 * for both entry and return uprobe.
 *
 * Returns
 * Address of the traced function for kprobe. 0 for kprobes placed within the
 * function (not at the entry). Address of the probe for uprobe and return
 * uprobe.
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_func_ip/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_get_func_ip(0);
}
