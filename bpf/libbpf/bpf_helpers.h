#pragma once
#include <bpf/bpf_helpers.h>

#define bpf_getcwd(buf, buf_len) __bpf_getcwd(buf, buf_len)

/**
 * https://github.com/bpftrace/bpftrace/issues/3314
 * https://lore.kernel.org/lkml/tencent_97F8B56B340F51DB604B482FEBF012460505@qq.com/
 */
static __always_inline int __bpf_getcwd(char *buf, u32 buf_len)
{
#ifdef DEBUG
	buf[0] = 'N';
	buf[1] = '/';
	buf[2] = 'A';
	buf[3] = '\0';
#else
# pragma message "How to use bpf_d_path()"
# if 0
	struct task_struct *curtask = (void *)bpf_get_current_task();
	if (curtask) {
		struct fs_struct *fs;
		struct path pwd;
		bpf_probe_read_kernel(&fs, sizeof(fs), &curtask->fs);
		if (fs) {
			bpf_probe_read_kernel(&pwd, sizeof(pwd), &fs->pwd);
			bpf_d_path(&pwd, buf, buf_len);
		}
	}
# endif
#endif
	return 0;
}
