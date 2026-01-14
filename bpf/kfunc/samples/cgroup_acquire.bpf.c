/**
 * struct cgroup *bpf_cgroup_acquire(struct cgroup *cgrp);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_cgroup_acquire/
 */
#include "vmlinux.h"

extern struct cgroup *bpf_cgroup_acquire(struct cgroup *cgrp) __weak __ksym;
extern void bpf_cgroup_release(struct cgroup *cgrp) __weak __ksym;

void test(struct cgroup *cgroup)
{
	struct cgroup *cgrp = bpf_cgroup_acquire(cgroup);
	if (cgrp) {
		bpf_cgroup_release(cgrp);
	}
}
