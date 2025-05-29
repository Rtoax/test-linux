#pragma once
#include <bpf/bpf_helpers.h>

#define bpf_getcwd(buf, buf_len) __bpf_getcwd(buf, buf_len)

static __always_inline int __bpf_getcwd(char *buf, u32 buf_len)
{
#ifdef DEBUG
	buf[0] = 'N';
	buf[1] = '/';
	buf[2] = 'A';
	buf[3] = '\0';
#else
	struct task_struct *curtask;
	struct dentry *dentry;
	curtask = (void *)bpf_get_current_task();

	if (curtask) {
		dentry = curtask->fs->pwd.dentry;

		for (u32 i = 0; i < 10 && dentry; i++) {
			const unsigned char *name = dentry->d_name.name;

			/* TODO */
			(void)name;

			if (dentry == dentry->d_parent)
				break;
			dentry = dentry->d_parent;
		}
	}
#endif
	return 0;
}
