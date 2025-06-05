#pragma once
#include <bpf/bpf_helpers.h>

#define MAX_D_ENTRIES	33
#define bpf_getcwd(buf, buf_len) __bpf_getcwd(buf, buf_len)

/**
 * https://github.com/bpftrace/bpftrace/issues/3314
 * https://lore.kernel.org/lkml/tencent_97F8B56B340F51DB604B482FEBF012460505@qq.com/
 */
static __always_inline int __bpf_getcwd(char *buf, u32 buf_len)
{
	struct task_struct __attribute__((unused)) *curtask;
	curtask = (void *)bpf_get_current_task();
#if defined(SUPPORT_BPF_PATH_D_PATH)
# pragma message "use bpf_path_d_path()"
/**
 * bpf_path_d_path() BPF kfunc may only be called from BPF LSM programs.
 */
# if 0
	if (curtask) {
		struct fs_struct *fs;
		struct path pwd;
		bpf_probe_read_kernel(&fs, sizeof(fs), &curtask->fs);
		if (fs) {
			bpf_probe_read_kernel(&pwd, sizeof(pwd), &fs->pwd);
			bpf_path_d_path(&pwd, buf, buf_len);
		}
	}
# endif
#elif defined(SUPPORT_BPF_D_PATH)
# pragma message "use bpf_d_path(), please very strict use"
/**
 * see linux::kernel/trace/bpf_trace.c btf_allowlist_d_path, only few fentry
 * could use bpf_d_path().
 */
	if (curtask) {
		struct fs_struct *fs;
		struct path pwd;
		bpf_probe_read_kernel(&fs, sizeof(fs), &curtask->fs);
		if (fs) {
			bpf_probe_read_kernel(&pwd, sizeof(pwd), &fs->pwd);
			bpf_d_path(&pwd, buf, buf_len);
		}
	}
#elif defined(SUPPORT_BPF_SNPRINTF)
# pragma message "support bpf_snprintf()"
/**
 * linux 7b15523a989b ("bpf: Add a bpf_snprintf helper")
 * v5.12-rc4-1654-g7b15523a989b
 */
# if 0 /* TODO: failed */
	int i;
	struct dentry *dentry;
	char fname[64];
	if (curtask) {
		dentry = curtask->fs->pwd.dentry;
		for (i = 1; i < MAX_D_ENTRIES; i++) {
			bpf_probe_read_kernel(&fname, sizeof(fname), dentry->d_name.name);
			bpf_snprintf(buf, buf_len, "/%s", fname, sizeof(fname));

			if (dentry == dentry->d_parent)
				break;

			dentry = dentry->d_parent;
		}
	}
# else
	unsigned long long args[2] = {10,11};
	bpf_snprintf(buf, buf_len, "<%ld,%ld>", &args, sizeof(args));
# endif
#else
# pragma message "cwd=N/A"
	buf[0] = 'N';
	buf[1] = '/';
	buf[2] = 'A';
	buf[3] = '\0';
#endif
	return 0;
}
