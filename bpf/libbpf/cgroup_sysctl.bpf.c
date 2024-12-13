// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_CGROUP_SYSCTL
 *
 * cGroup sysctl programs are called when a process in the cGroup to which the
 * program is attached attempts to read or write a sysctl option in the proc
 * file system.
 *
 * cGroup sysctl programs are typically located in the cgroup/sysctl ELF
 * section. These programs can be used to inspect and filter sysctl usage.
 *
 * These programs must return one of the following return codes:
 *
 *  0 means "reject access to sysctl"
 *  1 means "proceed with access"
 *
 * If program returns 0 user space will get -1 from read(2) or write(2) and
 * errno will be set to EPERM.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

/* Max supported length of sysctl value string (pow2). */
#define MAX_VALUE_STR_LEN 0x40

SEC("cgroup/sysctl")
int sysctl_printk_display(struct bpf_sysctl *ctx)
{
	int ret;
	char name[MAX_VALUE_STR_LEN];
	char value[MAX_VALUE_STR_LEN];

	ret = bpf_sysctl_get_name(ctx, name, sizeof(name), 0);
	if (ret < 0)
		return 0;

	ret = bpf_sysctl_get_current_value(ctx, value, sizeof(value));
	if (ret < 0 || ret >= MAX_VALUE_STR_LEN)
		return 0;

	bpf_printk("%s = %s", name, value);

	return 0;
}

char _license[] SEC("license") = "GPL";
