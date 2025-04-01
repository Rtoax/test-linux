#pragma once
#include <bpf/bpf_helpers.h>

static __always_inline int bpf_getcwd(char *buf, u32 buf_len)
{
	u32 i;
	struct task_struct *curtask;
	struct dentry *dentry;

	curtask = (void *)bpf_get_current_task();
	dentry = curtask->fs->pwd.dentry;

	/**
	 * TODO
	 */

	#pragma unroll
	for (i = 0; i < 10 && dentry; i++) {
		const char *name = dentry->d_name.name;
		if (dentry == dentry->d_parent)
			break;
		dentry = dentry->d_parent;
	}
	return 0;
}
