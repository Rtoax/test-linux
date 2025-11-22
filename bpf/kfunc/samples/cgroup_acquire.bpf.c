/**
 * struct cgroup *bpf_cgroup_acquire(struct cgroup *cgrp);
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_cgroup_acquire/
 */
#include "vmlinux.h"

void test(struct cgroup *cgroup)
{
	struct cgroup *cgrp = bpf_cgroup_acquire(cgroup);
	if (cgrp) {
		bpf_cgroup_release(cgrp);
	}
}
