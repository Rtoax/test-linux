// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_CGROUP_SYSCTL
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
