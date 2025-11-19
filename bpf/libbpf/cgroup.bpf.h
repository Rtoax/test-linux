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
# if defined(SUPPORT_BPF_CGROUP_ACQUIRE)
		struct cgroup *cgrp2 = bpf_cgroup_acquire(cgrp);
		if (cgrp2) {
			bpf_cgroup_release(cgrp2);
		}
# endif
		bpf_cgroup_release(cgrp);
	}
#endif
#if defined(SUPPORT_BPF_CGROUP_ACQUIRE) && defined(ERROR)
	struct cgroup *cgrp2 = bpf_cgroup_acquire(0);
	if (cgrp2) {
		bpf_cgroup_release(cgrp2);
	}
#endif
	return level;
}

