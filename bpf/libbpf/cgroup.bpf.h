// SPDX-License-Identifier: GPL-3.0
#include "vmlinux.h"
#include <linux/version.h>


unsigned long cgroup_level(void)
{
	unsigned long level = 0;
	u64 cgrpid = bpf_get_current_cgroup_id();
#ifdef SUPPORT_BPF_CGROUP_FROM_ID
	struct cgroup *cgrp = bpf_cgroup_from_id(cgrpid);
	if (cgrp) {
		level = cgrp->level;
		bpf_cgroup_release(cgrp);
	}
#endif
	return level;
}
