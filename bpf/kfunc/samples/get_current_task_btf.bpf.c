/**
 * struct task_struct *bpf_get_current_task_btf(void);
 * BPF_FUNC_get_current_task_btf = 158;
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_current_task_btf/
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

void test(void)
{
	struct task_struct *cur_task = bpf_get_current_task_btf();
}
